# GuitarSynth
GuitarSynth is a set of wavetable synths controlled by a monophonic pitchdetector.
Actually it is not specific to guitars but can be used for any harmonic instrument when playing single notes.
This is a small petproject of mine to explore the possibilities of pitchdetection for Guitars.
It uses aubio for pitch detection, but that will change as I want to write my own detector.
Required:
libjack, aubio

Compile:

cd ./path/to/GuitarSynth-DPF

git submodule init

git submodule update 

make

That's it you should have an lv2/vst/standalone plugin called GuitarSynth.
Load the plugin in your favourite DAW. By default all gains are down, so no sound will come up.
Just turn up the gain of a synth and play (beware of the square!)
You mix the synths by turning up their individual gains.
Have fun

