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

    mLowPassBuff=0;
    mFreqBuf=new_fvec(1);
//    InitEngine();
    lastfreq=0;
    mDelayin[0]=0;
    mDelayin[1]=0;
    mDelayout[0]=0;
    mDelayout[1]=0;
    mPitchDetector=0;
    mDampingFactor=10.0;
    mCuttOfFreq=6000;
    mInputGain=1.0;
    mOutputGain=1.0;
    mSamplerate=44100;
    mBufferSize=512;
    mInputThreshold=0;

}

GSEngine::~GSEngine()
{
    StopEngine();
    for(int s=0;s<mSynths.size();s++)
        delete mSynths[s];
    if(mInBuf)
        delete [] mInBuf;
    mInBuf=0;

    if(mLowPassBuff)
        delete [] mLowPassBuff;
    del_fvec(mFreqBuf);
    if(mPitchDetector)
        del_aubio_pitch(mPitchDetector);

}

void GSEngine::InitEngine(uint32_t samplerate,uint32_t buffersize)
{

    mSamplerate=samplerate;
    mBufferSize=buffersize;
    std::cout<<"Samplerate "<<mSamplerate<<" Buffersize "<<mBufferSize<<std::endl;
    if(mPitchDetector)
        del_aubio_pitch(mPitchDetector);

    mPitchDetector=new_aubio_pitch("yinfft",2*mBufferSize,mBufferSize,mSamplerate);
    //aubio_pitchdetection_set_yinthresh(mPitchDetector,1);
    mInputMag=0;
    if(mInBuf)
        delete [] mInBuf;

    if(mLowPassBuff)
        delete [] mLowPassBuff;
    mInBuf=new float[mBufferSize];

    mLowPassBuff=new float[mBufferSize];
    for(int s=0;s<mSynths.size();s++)
    {
        SynthBase* synth=mSynths[s];
        synth->setBufferSize(buffersize);
        synth->setSamplerate(samplerate);
        synth->InitBaseSynth();
    }

}

void GSEngine::StartEngine()
{



}

void GSEngine::StopEngine()
{


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
//    synth->setSamplerate(mSamplerate);
//    synth->setBufferSize(mBufferSize);
//    synth->InitBaseSynth();
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

int GSEngine::process(const float **inputs, float **outputs, uint32_t frames)
{
    const float* in=inputs[0];
    float* out=outputs[0];

    mInstance->lowpassIn(frames,in);

    mInstance->rectifyIn(frames,mInstance->mLowPassBuff);

//    for(int i=0;i<frames;i++)
//    {
//        (mInstance->mInBuf)[i]=(in[i]+fabs(in[i]))/2;
//    }
    fvec_t Buf;

    //Buf.channels=1;



    memset(out,0,frames*sizeof(float));

    if(getMagnitude(frames,in)>=mInstance->mInputThreshold)
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
        for(uint32_t f=0;f<frames;f++)
            out[f]*=mInstance->mOutputGain;

    }
//    else
//        mInstance->sendFrequence(0);

    return 0;
}




float GSEngine::getMagnitude(uint32_t frames, const float *buffer)
{
    float mag=0;
    for(uint32_t i=0;i<frames;i++)
        mag+=fabs(buffer[i]);
    mag=mag/frames;
    return mag;
}

void GSEngine::rectifyIn(int frames, const float *in)
{
    for(int i=0;i<frames;i++)
    {
        mInBuf[i]=mInputGain*(in[i]+fabs(in[i]))/2;
    }
}

void GSEngine::lowpassIn(uint32_t frames, const float *in)
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


