//
//  CStar.cpp
//  MyClusterSimulator
//
//  Created by bbb on 16/5/10.
//  Copyright © 2016年 Mr.B. All rights reserved.
//

#include "Header.h"
/*
class CPlanet
{
public:
    // Constructor
    CPlanet(string name,
            double mass,
            double radius,
            double x,double y,double z,
            double vx,double vy,double vz,
            double Red,double Green,double Blue);
    // Set the attribute
    void SetR(double a,double b,double c){r=vector3d(a,b,c);}
    void SetV(double a,double b,double c){v=vector3d(a,b,c);}
    // Get the attribute
    inline const vector3d& GetR()const{return r;}
    inline const vector3d& GetV()const{return v;}
    inline const double X()const{return r.X();}
    inline const double Y()const{return r.Y();}
    inline const double Z()const{return r.Z();}
    double GetMass()const{return Mass;}
    inline string GetName()const{return Name;}
    inline const double Red()const{return Color.X();}
    inline const double Green()const{return Color.Y();}
    inline const double Blue()const{return Color.Z();}
    inline const bool Exist()const{return exist;}
    inline const double GetRadius()const{return Radius;}
    // update
    void Updatetr(double DT);
    // tragetory
    list<vector3d> trail;
    
private:
    double Mass;
    string Name;
    double Radius;
    vector3d r;
    vector3d v;
    vector3d Color;
    bool exist;
    
    friend class CSolar;
    friend class CIntegrator;
    friend class CSI2;
    friend class CSI4;
    friend class CSI6;
    friend class CSIOD;
};
 */

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
    
}






