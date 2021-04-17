#include "CIntegrator.hpp"
#include "CPlanet.hpp"
#include "CSolar.hpp"

#include <vector>

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