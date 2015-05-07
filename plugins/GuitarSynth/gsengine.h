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

#include <aubio/aubio.h>
#include <aubio/pitch/pitch.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <DistrhoPlugin.hpp>
using namespace std;
class SynthBase;
class GSEngine
{

public:
    //Initialization
    GSEngine();
    void InitEngine(uint32_t samplerate, uint32_t buffersize);

    //Main process call
     int process(const float** inputs, float** outputs, uint32_t frames);

     //Get magnitude of signal to detect when to to trigger synths
     float getMagnitude(uint32_t frames, const float *buffer);

     //Add new synth
    void addSynth(SynthBase* synth);
    ~GSEngine();


    vector<SynthBase*> mSynths;
    float mInputThreshold;
private:
    //Rectify signal. This spreads the frequency range and helps the localization of low frequencies
    void rectifyIn(int frames,const float* in);

    //low pass at 6k to reduce artifacts from picking with plektrum
    void lowpassIn(uint32_t frames, const float *in);

    uint32_t mSamplerate;
    uint32_t mBufferSize;




    float* mInBuf;
    int mInBufCount;
    int mInBufSize;

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
