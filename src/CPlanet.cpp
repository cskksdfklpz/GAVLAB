#include "CPlanet.hpp"

CPlanet::CPlanet(string name,
                 double mass,
                 double radius,
                 double x,double y,double z,
                 double vx,double vy,double vz,
                 double Red,double Green,double Blue):
Name(name), Mass(mass),Radius(radius),r(vector3d(x,y,z)),v(vector3d(vx,vy,vz))
,Color(vector3d(Red,Green,Blue)){
    
    exist=true;
    
}

void CPlanet::Updatetr(double DT){

    trail.push_back(r);
    if (trail.size() >= 10000) trail.pop_front();
    
}
