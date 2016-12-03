#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <iostream>
#include <stdio.h>
#include <math.h>
/**
 * Graficos
 */
class Graphics {

    public:
        Graphics(int base, int lenght, float score);
        void boundaries(int b);
        void description();
        void graph(float c, float w, float e);
        void scorePrint();

    private:
        int base;
        int lenght;
        float score;
};
#endif
