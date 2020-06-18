#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <cmath>
#include <fstream>
#include <random>
#include <string>
#include "point.hpp"
// g++ point.cpp task5.cpp -o task5.exe
// #include <math.h>
int main()
{
    int simtimes = 100000;
    int steps;
    {

        std::ifstream file("steps.txt");
        std::string content;
        getline(file, content);
        steps = stoi(content);
        std::cout << steps;
    }

    srand(time(NULL));
    std::default_random_engine generator(rand());

    std::ofstream file("task5data.txt");
    if (file.is_open())
    {
        for (int i = 0; i < simtimes; i++)
        {
            point a(0, 0);
            a.moventimes(steps);

            file << a.printdata() + "\n";
        }

        // Write the data
        file.close();
    }
    return 0;
}