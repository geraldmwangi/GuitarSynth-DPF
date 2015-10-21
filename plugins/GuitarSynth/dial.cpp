#include "dial.h"



START_NAMESPACE_DGL
Dial::Dial(DGL::NanoWidget *parent,int rad): NanoWidget(parent)
{
    m_rad=rad;

//    fillColor(255,255,0);

}



void Dial::onNanoDisplay()
{
    const int x = getAbsoluteX();
    const int y = getAbsoluteY();

//    fillColor(255,0,0);
//    fill();
//    circle(50,50,50);
    fillColor(0,255,0);

    circle(x,y+50,m_rad);
    fill();

}


END_NAMESPACE_DGL
