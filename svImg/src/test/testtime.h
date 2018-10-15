#ifndef TESTTIME_H
#define TESTTIME_H

#include "color.h"
#include "shape.h"
#include "muti_shape.h"

class TestTime
{
public:
    TestTime();

    Color draw(double x, double y, int time = 1);

private:
        tyw::Circle circle001,circle002,circle003,circle004,circle005;
        Color color;

};

#endif // TESTTIME_H
