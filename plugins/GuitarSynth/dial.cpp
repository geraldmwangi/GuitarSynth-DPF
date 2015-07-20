#include "dial.h"



START_NAMESPACE_DGL
Dial::Dial(DGL::NanoWidget *parent): UIWidget(parent)
{
    this->setAbsolutePos(200,100);
    this->setHeight(100);
    this->setWidth(100);
//    fillColor(255,255,0);

}

void Dial::onNanoDisplay()
{

    fillColor(255,0,0);
    fill();
    circle(50,50,50);
    fillColor(0,255,0);
    fill();
    circle(50,50,20);

}


END_NAMESPACE_DGL
