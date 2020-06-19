#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <cmath>
#include <math.h> 
// #include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include "point.hpp"
const long double PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798;
void point::move()
{
    // To understand this please refer to README file
    long double valx = x;

    long double valy = y;
    long double oldx = x;
    long double oldy = y;
    long double r = validr.at((*rmover)(*generator));
    long double angle = validangle.at((*angledecider)(*generator));
    long double newx = x + r * std::cos(angle);
    long double newy = y + r * std::sin(angle);
    if (newx * newx + newy * newy <= 10000)
    {
        x = newx;
        y = newy;
        return;
    }
    while (true)
    {   
        long double xintersect;
        long double yintersect;
        long double x1;
        long double x2;
        long double y1;
        long double y2;
        long double gradient = (oldy - newy) / (oldx - newx);
        if (isinf(gradient) ) // vertical line.
        { 
            
            x1 = newx;
            x2 = newx;
            y1 = std::sqrt(-std::pow(x1,2)+10000);
            y2 = -std::sqrt(-std::pow(x2,2)+10000);
           
        }

        else if (gradient ==0) // horizontal line 
        {
           
            y1 = newy;
            y2 = newy;
            x1 = std::sqrt(-std::pow(y1,2)+10000);
            x2 = -std::sqrt(-std::pow(y2,2)+10000);
        }
        else
        {
            long double c = newy - gradient * newx;
            long double aquadratic = 1 + std::pow(gradient, 2);
            long double bquadratic = 2 * gradient * c;
            long double cquadratic = std::pow(c, 2) - 10000;
            long double squarerootpart = std::pow(bquadratic, 2) - 4 * aquadratic * cquadratic;

            squarerootpart = std::sqrt(squarerootpart);
            x1 = (-bquadratic + squarerootpart) / (2 * aquadratic);
            x2 = (-bquadratic - squarerootpart) / (2 * aquadratic);
            y1 = x1 * gradient * c;
            y2 = x2 * gradient * c;
        }
        
       
       
        if (std::pow(x1 - valx, 2) + std::pow(y1 - valy, 2) < std::pow(x2 - valx, 2) + std::pow(y2 - valy, 2))
        {
            xintersect = x1;
            yintersect = y1;
        }
        else
        {
            xintersect = x2;
            yintersect = y2;
        }
        long double g_normal = yintersect / xintersect;
        long double a_norm = -g_normal;
        long double b_norm = 1;
        long double n_vector_mag = std::sqrt(std::pow(a_norm, 2) + b_norm);
        long double perp_dist = (std::abs(a_norm * x + b_norm * y) * 2) / n_vector_mag;
        long double n_norm_a = a_norm / n_vector_mag;
        long double n_norm_b = b_norm / n_vector_mag;
        valx = n_norm_a * perp_dist + oldx;
        valy = n_norm_b * perp_dist + oldy;
        long double reflect_x = valx - xintersect;
        long double reflect_y = valy - yintersect;
        long double reflect_vect_mag = std::sqrt(std::pow(reflect_x, 2) + std::pow(reflect_y, 2));
        long double reflect_dist = std::sqrt(std::pow(oldx - xintersect, 2) + std::pow(oldy - yintersect, 2));
        valx = ((reflect_x / reflect_vect_mag) * (r - reflect_dist)) / (xintersect);
        valy = ((reflect_y / reflect_vect_mag) * (r - reflect_dist)) / (yintersect);
        if (std::pow(valx, 2) + std::pow(valy, 2) > 10000)
        {
            newx = valx;
            newy = valy;
        }
        else
        {
            x = valx;
            y = valy;
            return;
        }
    }
}
point::point(long double x, long double y) : x(x), y(y)
{

    // Get angle Probabilities
 {
        std::ifstream source("angleprobabilities.txt");

        for (std::string line; std::getline(source, line);) 
        {
            std::istringstream in(line); 
            float x;
            in >> x;
            validangleprob.push_back(x);
        }
    }
    angledecider = new std::discrete_distribution<int>(validangleprob.begin(), validangleprob.end());
    {
        std::ifstream source("anglevalues.txt");

        for (std::string line; std::getline(source, line);) 
        {
            std::istringstream in(line); 
            float x;
            in >> x;
            validangle.push_back(x);
        }
    }
    // Get r Probabilities
 {
        std::ifstream source("rprobabilities.txt");

        for (std::string line; std::getline(source, line);) 
        {
            std::istringstream in(line); 
            float x;
            in >> x;
            validrprob.push_back(x);
        }
    }
    rmover = new std::discrete_distribution<int>(validrprob.begin(), validrprob.end());
    {
        std::ifstream source("rvalues.txt");

        for (std::string line; std::getline(source, line);) 
        {
            std::istringstream in(line); 
            float x;
            in >> x;
            validr.push_back(x);
        }
    }
   
   
    generator = new std::default_random_engine(rand());
    // std::uniform_real_distribution<long double> x(0,1);
    // rmover=x;
}

point::~point()
{
}

std::string point::printdata()
{
    return std::to_string(x) + "," + std::to_string(y);
}

void point::moventimes(int num)
{
    for (int i = 0; i < num; i++)
    {
        this->move();
    }
}
bool point::nearpoint(point other)
{
    if (std::pow(other.x - x, 2) + std::pow(other.y - y, 2) <= 1)
    {
        return true;
    }
    return false;
}