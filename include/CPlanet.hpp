#ifndef CPLANET_HPP
#define CPLANET_HPP

#include "Vector.hpp"
#include <list>
#include <cmath>

#define G 66742800.0
#define MS 1.9890e+12

/** 
 * Represent a planet with a set of attributes 
*/
class CPlanet{
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
    double GetEnergy() {
        double E = 0.5 * Mass * (v.Magnitude() * v.Magnitude());
        double V = - G * Mass * MS / r.Magnitude();
        return E+V;
    }
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
    friend class CGrid;
};

extern CPlanet* P;

#endif