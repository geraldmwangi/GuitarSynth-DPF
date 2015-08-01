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
#include <gsengine.h>
#include <math.h>
#include <iostream>
SynthBase::SynthBase(string name):
    ParameteredObject(name,name,string("Synth"))
{


    //InitBaseSynth();
    mSamplerate=0;
    mBufferSize=0;
    mWaveTable=0;
 
    mOutBuffer=0;
    mPeakBuffer=0;
    mPeakBuffer1=0;
    transposefactor=0;
    curFreq=BASE_FREQ;
    curTablePos=0;
    phase=0;
    ampl=0;
    addParameter(transposefactor,kParameterIsAutomable,mName+" Transpose",mName+"Tr",
                 "",ParameterRanges(0.1,-1,1));
    addParameter(phase,kParameterIsAutomable,mName+" Phase",mName+"Ph",
                 "",ParameterRanges(0.1,-1,1));
    addParameter(ampl,kParameterIsAutomable,mName+" Gain",mName+"Gain",
                 "",ParameterRanges(0.1,0,1));
    addParameter(mConvolveIn,kParameterIsAutomable,mName+" Overlay Input",mName+"OvIn",
                 "",ParameterRanges(0.1,0,1));
//    addParameter(freqcuttoff,kParameterIsAutomable,mName+" Bandpass Cuttoff",mName+"BandCut",
//                 "",ParameterRanges(0.01,0,0.25));
//    addParameter(freqband,kParameterIsAutomable,mName+" Bandpass width",mName+"BandWidth",
//                 "",ParameterRanges(0.01,0,0.25));
//    addParameter(peakgain,kParameterIsAutomable,mName+" Bandpass peak gain",mName+"BandPeakGain",
//                 "",ParameterRanges(0.1,-20.0,20.0));
}

SynthBase::~SynthBase()
{
    if(mWaveTable)
        delete [] mWaveTable;

    if(mOutBuffer)
        delete [] mOutBuffer;
    if(mPeakBuffer)
        delete [] mPeakBuffer;

    if(mPeakBuffer1)
        delete [] mPeakBuffer1;


}

void SynthBase::InitBaseSynth()
{
    mWaveTableSize=mSamplerate/BASE_FREQ;
    if(mWaveTableSize!=0)
    {
        if(mWaveTable)
            delete [] mWaveTable;
        mWaveTable=new float[mWaveTableSize];

    }

    if(mOutBuffer)
        delete [] mOutBuffer;
    mOutBuffer=new float[mBufferSize];
    if(mPeakBuffer)
        delete [] mPeakBuffer;
    mPeakBuffer=new float[mBufferSize];
    if(mPeakBuffer1)
        delete [] mPeakBuffer1;
    mPeakBuffer1=new float[mBufferSize];

    memset(mWaveTable,0,mWaveTableSize*sizeof(float));
    mDelayIn[0]=0;
    mDelayIn[1]=0;
    mDelayOut[0]=0;
    mDelayOut[1]=0;
    InitControls();
    InitSynth();






}



//set the samplerate
void SynthBase::setSamplerate(int sr)
{
    mSamplerate=sr;
}
    //set the buffersize
void SynthBase::setBufferSize(int bs)
{
    mBufferSize=bs;
}
//process: process function of synth
void SynthBase::process(int frames, float *buffer, float freq,const float *inbuf)
{

    //compute current frequency and phase
    curFreq=freq*pow(2.0,transposefactor);
    float ph=phase*mWaveTableSize/2.0f;
    for(int i=0;i<frames;i++)
    {
        //shift wavetable position
        curTablePos+=curFreq/BASE_FREQ;

        //Are we at/over the end of the table
        if(curTablePos>=mWaveTableSize)
        {
            curTablePos-=(mWaveTableSize);

        }

        //shift by phase
        float tablepos=(((curTablePos+ph)>=mWaveTableSize)?(curTablePos+ph-mWaveTableSize):(curTablePos+ph));
        tablepos=((tablepos<0)?(mWaveTableSize+tablepos):tablepos);

        //linear interpolation
        int intPos=floor(tablepos);
        float delta=tablepos-intPos;
        mOutBuffer[i]=ampl*(mWaveTable[intPos]+delta*(mWaveTable[(intPos+1)%mWaveTableSize]-mWaveTable[intPos]));
//                +0.5*delta*delta*(mWaveTable[(intPos==0)?(mWaveTableSize-1):(intPos-1)]+mWaveTable[(intPos+1)%mWaveTableSize]-2*mWaveTable[intPos]));
//        bandpass(frames,buffer);


    }
//    bandpass(frames,mBandPassBuffer);
//    peakpass(frames);
    for(int i=0;i<frames;i++)
        buffer[i]+=mOutBuffer[i]*(mConvolveIn*(inbuf[i]-1.0)+1.0);





}
void SynthBase::peakpass(int frames)
{
    float d=-std::cos(3.14*freqcuttoff);
    float v0=pow(10.0,peakgain/20.0);
    float h0=v0-1.0;
    float aB=(std::tan(3.14*freqband)-1.0)/(std::tan(3.14*freqband)+1.0);
    if(mAb!=aB)
    {
        std::cout<<"ab: "<<aB<<endl;
        std::cout.flush();
        mAb=aB;
    }
    for(int i=0;i<frames;i++)
    {
        mPeakBuffer1[i]=-aB*mOutBuffer[i]+d*(1.0-aB)*mDelayIn[0]+mDelayIn[1]
                -d*(1.0-aB)*mDelayOut[0]+aB*mDelayOut[1];
        mPeakBuffer[i]=h0/2.0*(mOutBuffer[i]-mPeakBuffer1[i])+mOutBuffer[i];
       if(i>0)
       {
           mDelayIn[0]=mOutBuffer[i-1];
           mDelayOut[0]=mPeakBuffer1[i-1];
       }
       if(i>1)
       {
           mDelayIn[1]=mOutBuffer[i-2];
           mDelayOut[1]=mPeakBuffer1[i-2];
       }
    }
}

//updateWaveTable: update the wavetable when parameters are changed.
//Use only for parameters that define the form of the wavetable
void SynthBase::updateWaveTable()
{
    InitSynth();
}
//InitControls: Use this to initialize the parameters of the synths
void SynthBase::InitControls()
{
}
