//
//  CAC.cpp
//  GAVLAB
//
//  Created by bbb on 16/5/24.
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
 

class CGrid:public CIntegrator{
public:
    CGrid();
    virtual void Update(CSolar &S);
private:
    list<CPlanet> Cell[64][64][64];
    double Phi[64][64][64];
    void FFT();
    void UpdateCells();
    
};
 
 */

CGrid::CGrid(){
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
                Cell[i][j][k].clear();
                Phi[i][j][k]=0;
            }
        }
    }
}

void CGrid::Update(CSolar &S){
    // Update the cells according to the position of planets
    UpdateCells();
    // using FFT to calculate potential distribution
    FFT();
    
    for (int i=0; i<64; i++) {
        for (int j=0; j<64; j++) {
            for (int k=0; k<64; k++) {
                list<CPlanet>::iterator itr;
                for (itr = Cell[i][j][k].begin(); itr != Cell[i][j][k].end(); itr++){
                    double vx=(Phi[i+1][j][k]-Phi[i][j][k])
                    ,vy=(Phi[i][j+1][k]-Phi[i][j][k]),
                    vz=(Phi[i][j][k+1]-Phi[i][j][k]);
                    
                    itr->v+=vector3d(vx,vy,vz);
                    itr->r+=DT*itr->v;
                    itr->Updatetr(DT);
                
                }
            }
        }
    }
    
    S.t+=DT;
    
}

void CGrid::UpdateCells(){
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
                list<CPlanet>::iterator itr;
                for (itr = Cell[i][j][k].begin(); itr != Cell[i][j][k].end(); itr++) {
                    // calculate the index in the grid
                    int x=itr->X()/DELDA,y=itr->Y()/DELDA,z=itr->Z()/DELDA;
                    if (x != i || y != j || z != k) {
                        // if the planet is out of the cell,erase it
                        Cell[i][j][k].erase(itr);
                        // and put it into right place
                        Cell[x][y][z].push_back(*itr);
                    }
                }
            }
        }
    }
}

void CGrid::FFT(){
    //
}




