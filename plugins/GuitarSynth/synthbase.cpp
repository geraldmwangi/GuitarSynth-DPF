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

SynthBase::SynthBase(string name)
{


    //InitBaseSynth();
    mSamplerate=0;
    mBufferSize=0;
    mWaveTable=0;
    mWindow=0;

    transposefactor=1;
    curFreq=BASE_FREQ;
    curTablePos=0;
    phase=0;
    ampl=0;
}

SynthBase::~SynthBase()
{
    if(mWaveTable)
        delete [] mWaveTable;
    if(mWindow)
        delete [] mWindow;

}

void SynthBase::InitBaseSynth()
{
    mWaveTableSize=mSamplerate/BASE_FREQ;
    if(mWaveTableSize!=0)
    {
        mWaveTable=new float[mWaveTableSize];

    }
    if(mBufferSize!=0)
        mWindow=new float[mBufferSize];
    //Blackman-Harris see wikipedia
    float a=0.5;
    for(int i=0;i<mBufferSize;i++)
    {
        mWindow[i]=(1-a)/2-1/2*cos(2*M_PI*i/(mBufferSize-1))
                +a/2*cos(4*M_PI*i/(mBufferSize-1));
    }


    memset(mWaveTable,0,mWaveTableSize*sizeof(float));

    InitControls();
    InitSynth();






}




void SynthBase::setSamplerate(int sr)
{
    mSamplerate=sr;
}

void SynthBase::setBufferSize(int bs)
{
    mBufferSize=bs;
}

void SynthBase::process(int frames, float *buffer, float freq)
{


    curFreq=freq*transposefactor;
    float ph=phase*mWaveTableSize/2;
    for(int i=0;i<frames;i++)
    {
        curTablePos+=curFreq/BASE_FREQ;

        if(curTablePos>=mWaveTableSize)
        {
            curTablePos-=(mWaveTableSize);

        }


        float tablepos=(((curTablePos+ph)>=mWaveTableSize)?(curTablePos+ph-mWaveTableSize):(curTablePos+ph));
        tablepos=((tablepos<0)?(mWaveTableSize+tablepos):tablepos);

        int intPos=floor(tablepos);
        float delta=tablepos-intPos;
        buffer[i]+=ampl*(mWaveTable[intPos]+delta*(mWaveTable[(intPos+1)%mWaveTableSize]-mWaveTable[intPos]));
//                +0.5*delta*delta*(mWaveTable[(intPos==0)?(mWaveTableSize-1):(intPos-1)]+mWaveTable[(intPos+1)%mWaveTableSize]-2*mWaveTable[intPos]));


    }



}

void SynthBase::updateWaveTable()
{
    InitSynth();
}

void SynthBase::InitControls()
{
}
