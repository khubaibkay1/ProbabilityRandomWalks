#include "twopointmeet.hpp"


twopointmeet::twopointmeet(){
    
}
int twopointmeet::RunSimulation(std::default_random_engine generator){
    point a(generator);
    point b(generator);
    int steps=0;
    bool amove=true;
    while (!a.nearpoint(b)){
        if (amove){
            a.move();
        }
        else{
            b.move();
        }
        amove=!amove;
        steps++;
    }
    return steps;
}

twopointmeet::~twopointmeet(){

}