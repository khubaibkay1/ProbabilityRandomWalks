#pragma once
#include <random>
#include <string>
class point
{
private:
    long double x;
    long double y;
    std::default_random_engine* generator;

    std::uniform_real_distribution<long double>* rmover;
    std::uniform_real_distribution<long double>* angledecider;

public:
    point(long double x, long double y);
    point(std::default_random_engine& generator);
    void moventimes(int num);
    ~point();
    void move();
    std::string printdata();
    bool nearpoint(point x);
};

