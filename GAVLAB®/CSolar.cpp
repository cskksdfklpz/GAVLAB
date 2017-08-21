//
//  CSolar.cpp
//  MyClusterSimulator
//
//  Created by bbb on 16/5/10.
//  Copyright © 2016年 Mr.B. All rights reserved.
//

#include "Header.h"
/*
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
    // Method
    bool AddPlanet(CPlanet &P);
    void GenerateRandomPlanet();
    void UpdateSolar();
    
public:
    vector<CPlanet> Stars;
    double CenterStarMass;
    CIntegrator* I;
    double t=0;
    
    
    friend class CIntegrator;
    friend class CSI2;
    friend class CSI4;
    friend class CSI6;
    friend class CSIOD;
};
 */


void CSolar::SetI(int command){
    switch (command) {
        case SI2:
            I = new CSI2;
            break;
        case SI4:
            I = new CSI4;
            break;
        case SI6:
            I = new CSI6;
            break;
        case Grid:
            I = new CGrid;
            break;
        default:
            break;
    }
    
}

bool CSolar::AddPlanet(CPlanet &P){
    Stars.push_back(P);
    return true;
}

int Number=1;

void CSolar::GenerateRandomPlanet(){
    srand((unsigned)time(0));
    char S[10];
    sprintf(S, "%d",Number++);
    string name=S;
    double mass=double(arc4random()%100+10);
    mass*=(ME/10);
    
    double radius=double(arc4random()%10+1);
    radius/=10.0;
    double x=double(arc4random()%20+1)*flag();
    double y=double(arc4random()%20+1)*flag();
    double z=double(arc4random()%20+1)*flag();
    x*=(0.1*RA);y*=(0.1*RA);z*=(0.1*RA);
    
    double vx=double(arc4random()%100+10)*flag();
    vx*=100;
    double vy=double(arc4random()%100+10)*flag();
    vy*=100;
    double vz=double(arc4random()%100+10)*flag();
    vz*=100;
    
    double r=double(arc4random()%100+1);
    r/=100.0;
    double b=double(arc4random()%100+1);
    b/=100.0;
    double g=double(arc4random()%100+1);
    g/=100.0;
    
    
    P = new CPlanet(name,mass,radius,x,y,z,vx,vy,vz,r,g,b);
    AddPlanet(*P);
}

void CSolar::UpdateSolar(){
    I->Update(*this);
    
    // check for collision
    vector<CPlanet>::iterator itri,itrj;
    for (itri=Stars.begin(); itri != Stars.end(); itri++) {
        if (itri->exist == false) {
            continue;
        }
        
        double R0=(itri->r^(itri->v/(itri->v.Magnitude()))).Magnitude();
        
        if (R0<E) {
            cout<<itri->Name<<" BOOM"<<endl;
            itri->exist=false;
        }
        
        
        for (itrj=Stars.begin(); itrj!=Stars.end(); itrj++) {
            if (itrj == itri || itrj->exist==false) {
                continue;
            }
            vector3d rij=itri->r-itrj->r;
            double R=rij.Magnitude();
            if(R < E){
                cout<<itri->Name<<" and "<<itrj->Name<<" BOOM!"<<endl;
                itri->v=(itri->Mass*itri->v+itrj->Mass*itrj->v)/(itri->Mass+itrj->Mass);
                itri->Mass+=itrj->Mass;
                itrj->exist=false;
                
            }
        }
    }
}

