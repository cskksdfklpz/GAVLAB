//
//  CSI2.cpp
//  MyClusterSimulator
//
//  Created by bbb on 16/5/17.
//  Copyright © 2016年 Mr.B. All rights reserved.
//

#include "Header.h"

/*
 class CIntegrator{
 protected:
 double DT;
 public:
 virtual void Update(CSolar &S);
 void SetDT(double dt){DT = dt;}
 double GetDT()const{return DT;}
 };
 */


/*
class CSI2:public CIntegrator{
public:
    void Update(CSolar &S);
};
 */


void CSI2::Update(CSolar &S){
    
    vector<CPlanet>::iterator itri,itrj;
    for (itri = S.Stars.begin(); itri != S.Stars.end(); itri++) {
        if (itri->Exist() == false) {
            continue;
        }
        vector3d r_;
        r_ = itri->r+0.5*DT*(itri->v);
        vector3d v_=itri->v;
        // calculate center gravity
        double R_ = r_.Magnitude();
        v_ -=DT*G*S.GetMass()*r_/(R_*R_*R_);
        
        for (itrj = S.Stars.begin(); itrj != S.Stars.end(); itrj++) {
            if(itri == itrj || itrj->Exist() == false) continue;
            vector3d rij = r_ - itrj->r;
            double R = rij.Magnitude();
            v_ -= DT*G*itrj->GetMass()*rij/(R*R*R);
        }
        
        itri->v = v_;
        itri->r +=0.5*DT*v_;
        
        itri->Updatetr(DT);
        
    }
    
    S.t+=DT;
}


































