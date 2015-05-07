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


//Constructor

GSEngine::GSEngine()
{

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
    mSamplerate=44100;
    mBufferSize=512;
    mInputThreshold=0;
    mInBufSize=0;

}
//Destructor
GSEngine::~GSEngine()
{
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
//Initialization
void GSEngine::InitEngine(uint32_t samplerate,uint32_t buffersize)
{

    mSamplerate=samplerate;
    mBufferSize=buffersize;

    if(mPitchDetector)
        del_aubio_pitch(mPitchDetector);
    //Buffersize for analysis needs to be large enough to estimate low frequencies
    mInBufSize=mBufferSize*3;

    mPitchDetector=new_aubio_pitch("yinfft",mInBufSize,mBufferSize,mSamplerate);


    if(mInBuf)
        delete [] mInBuf;

    if(mLowPassBuff)
        delete [] mLowPassBuff;

    mInBuf=new float[mInBufSize];
    memset(mInBuf,0,mInBufSize*sizeof(float));
    mInBufCount=0;
    mLowPassBuff=new float[mBufferSize];

    //Initialization of the synths
    for(int s=0;s<mSynths.size();s++)
    {
        SynthBase* synth=mSynths[s];
        synth->setBufferSize(buffersize);
        synth->setSamplerate(samplerate);
        synth->InitBaseSynth();
    }

}
//Add new synth
void GSEngine::addSynth(SynthBase *synth)
{

    mSynths.push_back(synth);


}






//Main process call
int GSEngine::process(const float **inputs, float **outputs, uint32_t frames)
{
    const float* in=inputs[0];
    float* out=outputs[0];

    lowpassIn(frames,in);

    rectifyIn(frames,mLowPassBuff);


    fvec_t Buf;




    for(int i=0;i<frames;i++)
        out[i]=0.0f;


    if(getMagnitude(frames,in)>=mInputThreshold)
    {
        if(mInBufCount==0)
        {
            Buf.data=mInBuf;
            Buf.length=mInBufSize;



            aubio_pitch_do(mPitchDetector,&Buf,mFreqBuf);
        }
        float freq;
        freq=mFreqBuf->data[0];

        freq=floor(freq);
        if(freq<0)
            freq=0;
        for(int i=0;i<mSynths.size();i++)
        {
            mSynths[i]->process(frames,out,freq);

        }
//        for(uint32_t f=0;f<frames;f++)
//            out[f]*=in[f];

    }




    return 0;
}



//Get magnitude of signal to detect when to to trigger synths
float GSEngine::getMagnitude(uint32_t frames, const float *buffer)
{
    float mag=0;
    for(uint32_t i=0;i<frames;i++)
        mag+=fabs(buffer[i]);
    mag=mag/frames;
    return mag;
}
//Rectify signal. This spreads the frequency range and helps the localization of low frequencies
void GSEngine::rectifyIn(int frames, const float *in)
{
    for(int i=0;i<frames;i++)
    {
        mInBuf[mInBufCount]=(in[i]+fabs(in[i]))/2.0;
        mInBufCount=(mInBufCount==mInBufSize-1)?0:(mInBufCount+1);

    }
}
//low pass at 6k to reduce artifacts from picking with plektrum
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


