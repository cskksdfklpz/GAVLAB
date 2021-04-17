#include "CSolar.hpp"

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

double CSolar::GetTotalEnergy() {
    double Energy = 0;
    for (auto& star: Stars) {
        if (star.exist == true) Energy += star.GetEnergy();
    }

    for (int i=0; i < Stars.size(); i++) {
        for (int j=i+1; j < Stars.size(); j++) {
            auto& s1 = Stars[i];
            auto& s2 = Stars[j];
            if (s1.exist == true && s2.exist == true) {
                double V = -G * s1.GetMass() * s2.GetMass() / (s1.GetR()-s2.GetR()).Magnitude();
                Energy += V;
            }
        }
    }

    return Energy;

}