/*
This file is part of GuitarSynth2.

    GuitarSynth2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GuitarSynth2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GuitarSynth2.  If not, see <http://www.gnu.org/licenses/>.
    */
#include "synthbase.h"

#include <iostream>
#include <math.h>
#include "gsengine.h"


GSEngine* GSEngine::mInstance=0;

GSEngine::GSEngine()
{
    mInstance=this;
    mInBuf=0;
    mOutBuf=0;
    mLowPassBuff=0;
    mFreqBuf=new_fvec(1);
    InitNetwork();
    lastfreq=0;
    mDelayin[0]=0;
    mDelayin[1]=0;
    mDelayout[0]=0;
    mDelayout[1]=0;

    mDampingFactor=10.0;
    mCuttOfFreq=6000;


}

GSEngine::~GSEngine()
{
    StopEngine();
    if(mInBuf)
        delete [] mInBuf;
    mInBuf=0;
    if(mOutBuf)
        delete [] mOutBuf;
    mOutBuf=0;
    if(mLowPassBuff)
        delete [] mLowPassBuff;
    del_fvec(mFreqBuf);

}

void GSEngine::InitNetwork()
{
    mClient=jack_client_open("GuitarSynth",JackNullOption,0);

    if(mClient==0)
        this->errorMessage("Could not initialize Jack");

    if(jack_set_process_callback(mClient,GSEngine::process,0)!=0)
        this->errorMessage("Could not set Jack Process callback");

    mInput_port=jack_port_register (mClient, "input", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    mOutput_port=jack_port_register (mClient, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);


    mMidiOut=jack_port_register(mClient,"midiout",JACK_DEFAULT_MIDI_TYPE,JackPortIsOutput,0);
    mSamplerate=jack_get_sample_rate(mClient);
    mBufferSize=jack_get_buffer_size(mClient);
    std::cout<<"Samplerate "<<mSamplerate<<" Buffersize "<<mBufferSize<<std::endl;


    mPitchDetector=new_aubio_pitch("yinfft",2*mBufferSize,mBufferSize,mSamplerate);
    //aubio_pitchdetection_set_yinthresh(mPitchDetector,1);
    mInputMag=0;
    mInBuf=new float[mBufferSize];
    mOutBuf=new float[mBufferSize];
    mLowPassBuff=new float[mBufferSize];

}

void GSEngine::StartEngine()
{

    jack_activate(mClient);

}

void GSEngine::StopEngine()
{
    jack_deactivate(mClient);

}





void GSEngine::setInputGain(int val)
{
    mInputGain=((float)val/100.0f);


}

void GSEngine::setOutputGain(int val)
{
    mOutputGain=((float)val/100.0f);

}

void GSEngine::addSynth(SynthBase *synth)
{
    synth->setSamplerate(mSamplerate);
    synth->setBufferSize(mBufferSize);
    synth->InitBaseSynth();
    mSynths.push_back(synth);


}



void GSEngine::errorMessage(std::string err)
{
#warning implement!
}

GSEngine * GSEngine::getInstance()
{
    if(mInstance==0)
        mInstance=new GSEngine();
    return mInstance;
}

int GSEngine::process(jack_nframes_t frames, void *arg)
{
    jack_default_audio_sample_t* in=(jack_default_audio_sample_t*)jack_port_get_buffer(mInstance->mInput_port,frames);
    jack_default_audio_sample_t* out=(jack_default_audio_sample_t*)jack_port_get_buffer(mInstance->mOutput_port,frames);


    mInstance->lowpassIn(frames,in);

    mInstance->rectifyIn(frames,mInstance->mLowPassBuff);

//    for(int i=0;i<frames;i++)
//    {
//        (mInstance->mInBuf)[i]=(in[i]+fabs(in[i]))/2;
//    }
    fvec_t Buf;

    //Buf.channels=1;



    memset(out,0,frames*sizeof(jack_default_audio_sample_t));

    if(getMagnitude(frames,in)>1)
    {
        Buf.data=mInstance->mInBuf;
        Buf.length=frames;
        float freq;

        aubio_pitch_do(mInstance->mPitchDetector,&Buf,mInstance->mFreqBuf);
        freq=mInstance->mFreqBuf->data[0];

        freq=floor(freq);
        if(freq<0)
            freq=0;
        for(int i=0;i<mInstance->mSynths.size();i++)
        {
            mInstance->mSynths[i]->process(frames,out,freq);

        }
        for(jack_nframes_t f=0;f<frames;f++)
            out[f]*=mInstance->mOutputGain;
        mInstance->sendFrequence(freq);
    }
//    else
//        mInstance->sendFrequence(0);

    return 0;
}



float GSEngine::getMagnitude(jack_nframes_t frames, float *buffer)
{
    float mag=0;
    for(jack_nframes_t i=0;i<frames;i++)
        mag+=buffer[i]*buffer[i];
    mag=sqrt(mag);
    return mag;
}

void GSEngine::rectifyIn(int frames,float *in)
{
    for(int i=0;i<frames;i++)
    {
        mInBuf[i]=mInputGain*(in[i]+fabs(in[i]))/2;
    }
}

void GSEngine::lowpassIn(int frames, jack_default_audio_sample_t *in)
{
    float C=1.0/tan(3.14*mCuttOfFreq/mSamplerate);
    float b0=1.0/(1.0+2.0*mDampingFactor*C+C*C);
    float b1=2*b0;
    float b2=b0;
    float a1=2*b0*(1-C*C);
    float a2=b0*(1-2*mDampingFactor*C+C*C);
    for(int f=0;f<frames;f++)
    {
        mLowPassBuff[f]=b0*in[f]+b1*mDelayin[0]+b2*mDelayin[1]
                -a1*mDelayout[0]-a2*mDelayout[1];
        if(f>0)
        {
            mDelayin[0]=in[f-1];
            mDelayout[0]=mLowPassBuff[f-1];
        }
        if(f>1)
        {
            mDelayin[1]=in[f-2];
            mDelayout[1]=mLowPassBuff[f-2];
        }
    }
}


