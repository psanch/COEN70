//
//  lunarlander.cpp
//  
//
//  Created by Pedro Sanchez on 1/27/17.

#ifndef lunarlander_hpp
#define lunarlander_hpp

class lunarlander{
    
    double flowRate;
    double speed;
    double altitude;
    double fuel;
    static const int mass = 900;
    static const int maxFlow = 10;
    static const int maxThrust = 5000;
    
public:
    
    lunarlander();
    double getFlowRate() const {return flowRate;};
    double getVelocity() const {return speed;};
    double getAltitude() const {return altitude;};
    double getFuel() const {return fuel;};
    double getMass() const {return (fuel + mass);};
    int getMaxFuelRate() const {return maxFlow;};
    int getMaxThrust() const {return maxThrust;};
    
    void setFlowRate(double newRate);
    void timePassage(double seconds);
    
};

#endif /* lunarlander_hpp */
#include <assert.h>


lunarlander::lunarlander(){ //constructor initializes defaults
    
    flowRate = 0;
    speed = 0;
    altitude = 1000;
    fuel = 1700;
    
}

void lunarlander::setFlowRate(double newRate){
    
    assert(newRate >= 0 && newRate <= 1);
    
    flowRate = newRate;
    
    return;
}

void lunarlander::timePassage(double seconds){
    
    assert (seconds >= 0);
    
    
    double t = seconds;  //tmp variables to calculate physical changes
    double thrust;
    double tmass;
    double velchange;
    double altchange;
    double fchange;
    
    if(fuel == 0 && flowRate != 0) //preliminary checks
        flowRate = 0;
    
    thrust = getFlowRate() * getMaxThrust(); //physics
    
    tmass = getMass() + getFuel();
    
    velchange = t * ((thrust/(tmass))-1.62);
    speed += velchange;
    
    altchange = t * getVelocity();
    altitude += altchange;
    
    fchange = t * (flowRate * maxFlow);
    fuel -= fchange;
    
    if (altitude < 0){//final checks
        altitude = 0;
        speed = 0;
    } //The eagle has landed!
    
    if (getFuel() < 0)
        fuel = 0; //The eagle has ran out of fuel!
    
}
