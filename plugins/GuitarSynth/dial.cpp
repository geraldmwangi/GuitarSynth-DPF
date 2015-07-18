#include "dial.h"



START_NAMESPACE_DGL
Dial::Dial(DGL::NanoWidget *parent): UIWidget(parent)
{
    this->setAbsolutePos(100,100);
    this->setHeight(100);
    this->setWidth(100);
//    fillColor(255,255,0);

}

void Dial::onNanoDisplay()
{
    rect(0,0,20,10);
    fillColor(255,0,0);
    fill();
}


END_NAMESPACE_DGL
