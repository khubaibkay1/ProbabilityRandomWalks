#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <cmath>
#include <fstream>
#include <random>
#include <string>
#include "point.hpp"
#include "twopointmeet.hpp"
// #include <math.h>
int main()
{
    int simtimes = 10000;
    int steps = 10000;
    srand(time(NULL));
    std::default_random_engine generator(rand());
    
    std::ofstream file("simdata.txt");
    if (file.is_open())
    {
        for (int i = 0; i < simtimes; i++)
        {
            point a(0,0);
            a.moventimes(steps);
            
        file << a.printdata() + "\n";
        }

        // Write the data
        file.close();
    }
    return 0;
}