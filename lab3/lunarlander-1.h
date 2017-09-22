//
//  lunarlander.hpp
//  
//
//  Created by Pedro Sanchez on 1/27/17.
//
//

#ifndef lunarlander_hpp
#define lunarlander_hpp

class lunarlander{
    
    double flowRate;
    double speed;
    double altitude;
    double fuel;
    static const int mass = 900; //given defaults
    static const int maxFlow = 10;
    static const int maxThrust = 5000;
    
public:
    
    lunarlander(); //Constructor
    //Pre: header file included
    //Post:flowRate = 0; speed = 0; altitude = 1000; fuel = 1700;
    //(O): constant
    double getFlowRate() const {return flowRate;}; //returns flowRate
    //Pre: initialized lunarlander obj
    //Post: returns flowRate
    //(O): constant
    double getVelocity() const {return speed;}; //returns speed
    //Pre: initialized lunarlander obj
    //Post: returns speed
    //(O): constant
    double getAltitude() const {return altitude;}; //returns altitude
    //Pre: initialized lunarlander obj
    //Post: returns altitude
    //(O): constant
    double getFuel() const {return fuel;}; //returns fuel
    //Pre: initialized lunarlander obj
    //Post: returns fuel
    //(O): constant
    double getMass() const {return (fuel + mass);}; //returns mass calculation ** MIGHT NEED ASSERT HERE
    //Pre: initialized lunarlander obj
    //Post: Total mass (fuel + mass) returned
    //(O): constant
    int getMaxFuelRate() const {return maxFlow;}; //returns maxFlow
    //Pre: initialized lunarlander obj
    //Post:constant provided
    //(O): constant
    int getMaxThrust() const {return maxThrust;}; //returns maxThrust
    //Pre: initialized lunarlander obj
    //Post: constant provided
    //(O): constant
    void setFlowRate(double newRate);
    //Pre: initialized lunarlander obj, double (0 <= newRate <= 1)  passed as argument
    //Post: flowRate = newRate
    //(O): constant
    void timePassage(double seconds);
    //Pre: initialized lunarlander obj, double (NOTE: prefer small, for accuracy) passed as argument
    //Post: All non-constant member variables (flowRate, speed, altitude, fuel) physically simulated using physics equation for time = seconds.
    //(O): constant
};

#endif /* lunarlander_hpp */

