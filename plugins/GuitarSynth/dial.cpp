#include "dial.h"



START_NAMESPACE_DGL
Dial::Dial(DGL::NanoWidget *parent,int rad): UIWidget(parent)
{
    m_rad=rad;

//    fillColor(255,255,0);

}



void Dial::onNanoDisplay()
{

//    fillColor(255,0,0);
//    fill();
//    circle(50,50,50);
    fillColor(0,255,0);

    circle(0,50,m_rad);
    fill();

}


END_NAMESPACE_DGL
