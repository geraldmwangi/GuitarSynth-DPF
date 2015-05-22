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
#include "squaresynth.h"
#include <math.h>
#include <parameterupdatewave.h>
SquareSynth::SquareSynth(string name):
    SynthBase("SquareSynth"+name)
{
    addParameter(new ParameterUpdateWave(this,radius,kParameterIsAutomable,mName+" Radius",mName+"Radius","",ParameterRanges(0.1,0,1)));
}

void SquareSynth::InitSynth()
{


    int steps=floor(mWaveTableSize/4*radius);

    for(int i=0;i<steps;i++)
    {
        mWaveTable[i]=1.0f-sqrt(steps*steps-i*i)/steps;
        mWaveTable[i+mWaveTableSize/2]=-mWaveTable[i];
    }
    for(int i=steps;i<mWaveTableSize/2-steps;i++)
    {
        mWaveTable[i]=1;
        mWaveTable[i+mWaveTableSize/2]=-mWaveTable[i];
    }
    for(int i=mWaveTableSize/2-steps;i<mWaveTableSize/2;i++)
    {
        mWaveTable[i]=1.0f-sqrt(steps*steps-(-i+mWaveTableSize/2)*(-i+mWaveTableSize/2))/steps;
        mWaveTable[i+mWaveTableSize/2]=-mWaveTable[i];
    }






}

void SquareSynth::InitControls()
{
    radius=0;
//    addControl("Radius",radius,0,1,true);
}
