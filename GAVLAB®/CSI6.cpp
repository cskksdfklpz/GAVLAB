//
//  CSI6.cpp
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
    virtual void Update(CSolar &S)=0;
    void SetDT(double dt){DT = dt;}
    double GetDT()const{return DT;}
};

class CSI6:public CIntegrator{
public:
    virtual void Update(CSolar &S);
};
 */

void CSI6::Update(CSolar &S){

    double c[11];
    double d[11];
    d[1]=d[3]=d[7]=d[9]=-0.293667939522341;
    d[2]=d[8]=-1.99977809735512;
    d[4]=d[6]=0.337335879044682;
    d[5]=2.29714181079093;
    d[0]=d[10]=0;
    c[0]=0;
    c[1]=0.5*d[1];
    c[10]=0.5*d[9];
    for (int i=2; i<10; i++) {
        c[i]=(d[i-1]+d[i])/2.0;
    }
    vector<CPlanet>::iterator itri,itrj;
    for (itri = S.Stars.begin(); itri != S.Stars.end(); itri++) {
        vector3d r_[11],v_[11];
        r_[0]=itri->r;
        v_[0]=itri->v;
        for (int i=1; i<=10; i++) {
            r_[i]=r_[i-1] + DT*c[i]*v_[i-1];
            
            // Center gravity
            double r=r_[i].Magnitude();
            v_[i] = v_[i-1]-G*DT*d[i]*S.GetMass()*r_[i]/(r*r*r);
            if(i == 10) continue;
            // gravity between stars
            for (itrj = S.Stars.begin();itrj!= S.Stars.end(); itrj++) {
                if (itri == itrj) continue;
                vector3d rij = r_[i]-itrj->r;
                double R = rij.Magnitude();
                v_[i]-= DT*d[i]*G*itrj->GetMass()*rij/(R*R*R);
            }
        }
        
        itri->r = r_[10];
        itri->v = v_[10];
        itri->Updatetr(DT);
        
    }
    
    S.t+=DT;
    
}
