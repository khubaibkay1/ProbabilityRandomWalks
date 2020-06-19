#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <cmath>
// #include <fstream>
#include <random>
#include <string>
#include "point.hpp"
const long double PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798;
void point::move()
{
    long double valx = x;

    long double valy = y;
    long double oldx = x;
    long double oldy = y;
    long double r = (*rmover)(*generator);
    long double angle = (*angledecider)(*generator);
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
        //find point of intersection with circle
        long double gradient = (oldy - newy) / (oldx - newx);
        long double c = newy - gradient * newx;
        long double aquadratic = 1 + std::pow(gradient, 2);
        long double bquadratic = 2 * gradient * c;
        long double cquadratic = std::pow(c, 2) - 10000;
        long double squarerootpart = std::pow(bquadratic, 2) - 4 * aquadratic * cquadratic;
 
        squarerootpart = std::sqrt(squarerootpart);
        long double x1 = (-bquadratic + squarerootpart) / (2 * aquadratic);
        long double x2 = (-bquadratic - squarerootpart) / (2 * aquadratic);
        long double y1 = x1 * gradient * c;
        long double y2 = x2 * gradient * c;
        long double xintersect;
        long double yintersect;
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
        // Gradient of the Normal  at the intersect
        
        long double g_normal = yintersect / xintersect;
        long double a_norm = -g_normal;
        long double b_norm = 1;
        long double n_vector_mag = std::sqrt(std::pow(a_norm, 2) + b_norm);
        
        // Perpendicular dist from Old point to the normal
        long double perp_dist = (std::abs(a_norm * x + b_norm * y) * 2) / n_vector_mag;
        long double n_norm_a = a_norm / n_vector_mag;
        long double n_norm_b = b_norm / n_vector_mag;
        valx = n_norm_a * perp_dist + oldx;
        valy = n_norm_b * perp_dist + oldy;
        // Vector from intersection pt to the reflected pt
        long double reflect_x = valx - xintersect;
        long double reflect_y = valy - yintersect;
        long double reflect_vect_mag = std::sqrt(std::pow(reflect_x, 2) + std::pow(reflect_y, 2));
        long double reflect_dist = std::sqrt(std::pow(oldx - xintersect, 2) + std::pow(oldy - yintersect, 2));
        // Reflected point
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
    rmover = new std::uniform_real_distribution<long double>(0, 1);
    generator = new std::default_random_engine(rand());
    angledecider = new std::uniform_real_distribution<long double>(0, 2 * PI);
 
}

point::~point()
{
 
}
point::point(std::default_random_engine &generator)
{

    rmover = new std::uniform_real_distribution<long double>(0, 1);
    angledecider = new std::uniform_real_distribution<long double>(0, 2 * PI);
    
    std::uniform_real_distribution<long double> distribution(0.0, 100);
    long double radius = distribution(generator);
    long double angle = (*angledecider)(generator);
    x = radius * std::cos(angle);
    y = radius * std::sin(angle);
    this->generator = new std::default_random_engine(rand());
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
bool point::nearpoint(point other){
    if (std::pow(other.x -x,2)+std::pow(other.y -y,2)<=1){
        return true;
    }
    return false;
}