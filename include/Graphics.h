#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <iostream>
#include <stdio.h>
/**
 * Graficos
 */
class Graphics {

    public:
        Graphics(int base, int lenght);
        void percentage(int i);
        void boundaries(int b);
        void description();
        void graph(int c, int w, int e);

    private:
        int base;
        int lenght;
};
#endif
