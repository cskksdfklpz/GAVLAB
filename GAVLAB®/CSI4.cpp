//
//  CSI4.cpp
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

class CSI4:public CIntegrator{
public:
    virtual void Update(CSolar &S);
};
 */

void CSI4::Update(CSolar &S){
    
    double c[5]={0,0.67560359597,-0.1756035979,-0.1756035979,0.67560359597};
    double d[5]={0,1.3512071919596577,-1.70241438391932,1.3512071919596577,0};
    
    vector<CPlanet>::iterator itri,itrj;
    for (itri = S.Stars.begin(); itri != S.Stars.end(); itri++) {
        if (itri->exist==false) {
            continue;
        }
        vector3d r_[5],v_[5];
        r_[0]=itri->r;
        v_[0]=itri->v;
        for (int i=1; i<=4; i++) {
            r_[i]=r_[i-1] + DT*c[i]*v_[i-1];
            
            // Center gravity
            double r=r_[i].Magnitude();
            v_[i] = v_[i-1]-G*DT*d[i]*S.GetMass()*r_[i]/(r*r*r);
            if(i == 4) continue;
            
            // gravity between stars
            for (itrj = S.Stars.begin();itrj!= S.Stars.end(); itrj++) {
                if (itri == itrj) continue;
                if (itrj->exist==false) {
                    continue;
                }
                vector3d rij = r_[i]-itrj->r;
                double R = rij.Magnitude();
                v_[i]-= DT*d[i]*G*itrj->GetMass()*rij/(R*R*R);
            }
            
        }
        
        itri->r = r_[4];
        itri->v = v_[4];
        itri->Updatetr(DT);
        
    }

    S.t+=DT;
    
}
