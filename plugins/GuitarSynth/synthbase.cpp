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

SynthBase::SynthBase(string name):
    ParameteredObject(name,name,string("Synth"))
{


    //InitBaseSynth();
    mSamplerate=0;
    mBufferSize=0;
    mWaveTable=0;
 
    mOutBuffer=0;
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
}

SynthBase::~SynthBase()
{
    if(mWaveTable)
        delete [] mWaveTable;

    if(mOutBuffer)
        delete [] mOutBuffer;

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
void SynthBase::process(int frames, float *buffer, float freq)
{

    //compute current frequency and phase
    curFreq=freq*pow(2.0,transposefactor);
    float ph=phase*mWaveTableSize/2;
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
        buffer[i]+=ampl*(mWaveTable[intPos]+delta*(mWaveTable[(intPos+1)%mWaveTableSize]-mWaveTable[intPos]));
//                +0.5*delta*delta*(mWaveTable[(intPos==0)?(mWaveTableSize-1):(intPos-1)]+mWaveTable[(intPos+1)%mWaveTableSize]-2*mWaveTable[intPos]));
//        bandpass(frames,buffer);


    }



}
void SynthBase::bandpass(int frames, float *buffer)
{
    float c=std::tan(3.14*freqband/mSamplerate);
    float d=std::tan(3.14*freqcuttoff/mSamplerate);
    for(int i=0;i<frames;i++)
    {
       buffer[i]=-c*mOutBuffer[i]+d*(1-c)*mDelayIn[0]+mDelayIn[1]
               +d*(1-c)*mDelayOut[0]-c*mDelayOut[1];
       if(i>0)
       {
           mDelayIn[0]=mOutBuffer[i-1];
           mDelayOut[0]=buffer[i-1];
       }
       if(i>1)
       {
           mDelayIn[1]=mOutBuffer[i-2];
           mDelayOut[1]=buffer[i-2];
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
