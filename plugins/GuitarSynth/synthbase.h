#ifndef SYNTHBASE_H
#define SYNTHBASE_H
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

#include <gsengine.h>
#include <string>
#define BASE_FREQ 80.0f
using namespace std;


class SynthBase:public ParameteredObject
{

public:
    explicit SynthBase(string name);
    //set the samplerate
    void setSamplerate(int sr);
    //set the buffersize
    void setBufferSize(int bs);
    ~SynthBase();

    //InitBaseSynth: Init the synth, set the wavetable size
    void InitBaseSynth();

    //InitSynth: virtual function. Use this to initialize the wavetable
    virtual void InitSynth()=0;

//    InitControls: Use this to initialize the parameters of the synths
    virtual void InitControls();

    //process: process function of synth
    void process(int frames, float* buffer,float freq);


    //updateWaveTable: update the wavetable when parameters are changed.
    //Use only for parameters that define the form of the wavetable
    void updateWaveTable();



    float freqband;
    float freqcuttoff;

    float phase;
    float ampl;
    float transposefactor;
protected:
    void bandpass(int frames, float* buffer);
    float mDelayIn[2];
    float mDelayOut[2];
    float curFreq;
    float curTablePos;
    float* mWaveTable;

    float* mOutBuffer;

    int mWaveTableSize;
    int mBufferSize;
    int mSamplerate;
    string mSynthname;





};

#endif // SYNTHBASE_H
