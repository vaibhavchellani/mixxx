/***************************************************************************
                          enginepregain.cpp  -  description
                             -------------------
    copyright            : (C) 2002 by Tue and Ken Haste Andersen
    email                :
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "enginepregain.h"
#include "controllogpotmeter.h"
#include "controlengine.h"

/*----------------------------------------------------------------
  A pregaincontrol is ... a pregain.
  ----------------------------------------------------------------*/
EnginePregain::EnginePregain(const char *group)
{
    ControlLogpotmeter *p = new ControlLogpotmeter(ConfigKey(group, "pregain"), 4.);
    potmeterPregain = new ControlEngine(p);
    buffer = new CSAMPLE[MAX_BUFFER_LEN];
}

EnginePregain::~EnginePregain()
{
    delete potmeterPregain;
    delete [] buffer;
}

CSAMPLE *EnginePregain::process(const CSAMPLE *source, const int buffer_size)
{
    double gain=potmeterPregain->get();
    //qDebug("gain %f",potmeterPregain->get());

    if (gain == 1.)
    {
        memcpy(buffer, source, sizeof(CSAMPLE) * buffer_size);
        return buffer;
    }
    
    for (int i=0; i<buffer_size; i++)
        buffer[i] = source[i]*gain;

    return buffer;
}
