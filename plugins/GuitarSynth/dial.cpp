#include "dial.h"


START_NAMESPACE_DISTRHO

Dial::Dial(DGL::Window *parent): UIWidget(parent)
{
    this->setAbsolutePos(100,100);
    this->setHeight(10);
    this->setWidth(10);
    fillColor(255,0,0);

}

void Dial::onNanoDisplay()
{
    fillColor(255,0,0);
}

END_NAMESPACE_DISTRHO
