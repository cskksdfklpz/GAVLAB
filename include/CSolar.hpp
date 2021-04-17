#ifndef CSOLAR_HPP
#define CSOLAR_HPP

#include "CIntegrator.hpp"
#include "Vector.hpp"
#include "CPlanet.hpp"
#include <vector>

#define G 66742800.0
#define SI2 -2
#define SI4 -4
#define SI6 -6
#define Grid -10
#define MS 1.9890e+12
#define ME 5980000.0
#define RA 149597870000.0
#define YEAR 31536000.0
#define DAY 86400
#define E 1e10
#define SCALE 1e11
#define DELDA 111
#define N 64

// randomly generate a flag = 1 or -1
inline int flag(){
    srand(unsigned(time(0)));
    int f;
    int n=arc4random()%100+1;
    if (n%2 == 0) {
        f=1;
    }
    else
        f=-1;
    return f;
}

/** 
 * A solar system containing a central body with a
 * a number of planet objects, assuming the central body
 * is fixed.
*/
class CSolar{
public:
    CSolar(double mass):CenterStarMass(mass){ }
    CSolar(){}
    // Set the attribute
    void SetMass(double mass){CenterStarMass=mass;}
    void SetI(int command);
    void SetStep(double DT_){I->SetDT(DT_);}
    // Get the attribute
    double GetMass()const {return CenterStarMass;}
    double GetT()const{return t;}
    double GetStep()const{return I->GetDT();}
    // Method
    bool AddPlanet(CPlanet &P);
    void GenerateRandomPlanet();
    void UpdateSolar();
    double GetTotalEnergy();
public:
    vector<CPlanet> Stars;
    double CenterStarMass;
    CIntegrator* I;
    double t=0;
    
    
    friend class CIntegrator;
    friend class CSI2;
    friend class CSI4;
    friend class CSI6;
    friend class CGrid;
};

extern CSolar Solar;

#endif