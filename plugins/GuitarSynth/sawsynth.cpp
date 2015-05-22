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
#include "sawsynth.h"

SawSynth::SawSynth(string name):
    SynthBase("SawSynth"+name)
{
}

void SawSynth::InitSynth()
{
    for(int i=0;i<mWaveTableSize;i++)
        mWaveTable[i]=((float)i)/mWaveTableSize;
}
