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

#include <jack/jack.h>
#include <jack/midiport.h>
#include <aubio/aubio.h>
#include <aubio/pitch/pitch.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
using namespace std;
class SynthBase;
class GSEngine
{

public:
    static void errorMessage(string err);
    GSEngine();
    void InitNetwork();
    void StartEngine();
    void StopEngine();

    static int process(jack_nframes_t frames,void* arg);
    static float getMagnitude(jack_nframes_t frames,float* buffer);

    static GSEngine *getInstance();

    void sendFrequence(float val);


    void addSynth(SynthBase* synth);
    ~GSEngine();




    static GSEngine* mInstance;


    void setInputGain(int val);
    void setOutputGain(int val);
private:

    float mInputGain;
    float mOutputGain;
    float mInputMag;
    vector<SynthBase*> mSynths;
    jack_nframes_t mSamplerate;
    jack_nframes_t mBufferSize;


    void rectifyIn(int frames,float* in);
    void lowpassIn(int frames,jack_default_audio_sample_t* in);

    float* mInBuf;
    float* mOutBuf;
    jack_port_t *mInput_port;
    jack_port_t *mOutput_port;
    fvec_t* mFreqBuf;
    jack_port_t *mMidiOut;
    jack_client_t *mClient;
    aubio_pitch_t* mPitchDetector;
    float lastfreq;

    float mDelayin[2];
    float mDelayout[2];
    float mCuttOfFreq;
    float mDampingFactor;
    jack_default_audio_sample_t* mLowPassBuff;




};

#endif // GSENGINE_H
