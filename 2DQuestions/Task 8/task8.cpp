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

// g++ point.cpp task8.cpp twopointmeet.cpp -o task8.exe
int main()
{
    int simtimes = 100;
    srand(time(NULL));
    std::default_random_engine generator(rand());
    

    twopointmeet a = twopointmeet();
    std::cout << a.RunSimulation(generator);
     
    std::ofstream file("task8.txt");
    
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