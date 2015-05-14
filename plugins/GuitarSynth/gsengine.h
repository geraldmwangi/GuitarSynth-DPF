#ifndef GSENGINE_H
#define GSENGINE_H
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

#include <parameteredobject.h>
#include <aubio/aubio.h>
#include <aubio/pitch/pitch.h>
#include <vector>
//#include <string>
#include <stdio.h>
//#include <string.h>

using namespace std;
class SynthBase;
class GSEngine:public ParameteredObject
{

public:

    explicit GSEngine();
    void InitEngine(uint32_t samplerate, uint32_t buffersize);
    void StartEngine();
    void StopEngine();

     int process(const float** inputs, float** outputs, uint32_t frames);
     float getMagnitude(uint32_t frames, const float *buffer);





    void addSynth(SynthBase* synth);
    ~GSEngine();







    void setInputGain(int val);
    void setOutputGain(int val);
    vector<SynthBase*> mSynths;
    float mInputThreshold;
private:

    float mInputGain;
    float mOutputGain;
    float mInputMag;

    uint32_t mSamplerate;
    uint32_t mBufferSize;


    void rectifyIn(int frames,const float* in);
    void lowpassIn(uint32_t frames, const float *in);

    float* mInBuf;


    fvec_t* mFreqBuf;

    aubio_pitch_t* mPitchDetector;
    float lastfreq;

    float mDelayin[2];
    float mDelayout[2];
    float mCuttOfFreq;
    float mDampingFactor;
    float* mLowPassBuff;




};

#endif // GSENGINE_H
