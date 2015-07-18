#include "dial.h"




Dial::Dial(DGL::Window &parent): UIWidget(parent)
{
    this->setAbsolutePos(100,100);
    this->setHeight(100);
    this->setWidth(100);
    fillColor(255,0,0);

}

void Dial::onNanoDisplay()
{
    fillColor(255,255,255,0);
}


