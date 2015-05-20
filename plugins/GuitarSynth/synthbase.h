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
#define BASE_FREQ 180.0f
using namespace std;


class SynthBase:public ParameteredObject
{

public:
    explicit SynthBase(string name);
    void setSamplerate(int sr);
    void setBufferSize(int bs);
    ~SynthBase();

    void InitBaseSynth();
    virtual void InitSynth()=0;
    virtual void InitControls();


    void process(int frames, float* buffer,float freq);






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
    float* mWindow;

    float* mOutBuffer;

    int mWaveTableSize;
    int mBufferSize;
    int mSamplerate;
    string mSynthname;





};



#endif // SYNTHBASE_H
