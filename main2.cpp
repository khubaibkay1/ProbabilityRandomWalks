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
    srand(time(NULL));
    std::default_random_engine generator(rand());
    

    twopointmeet a = twopointmeet();
    std::cout << a.RunSimulation(generator);
     
    std::ofstream file("simdata.txt");
    
    if (file.is_open())
    {
        for (int i = 0; i < simtimes; i++)
        {
            int val = a.RunSimulation(generator);
            file << std::to_string(val) + "\n";
            if (i%1000==0){
                std::cout << i << "\n";
            }
        }

        // Write the data
        file.close();
    }
    else
    {
        std::cout <<"sad";
    }
    
    return 0;
}