//
//  Header.h
//  MyClusterSimulator
//
//  Created by bbb on 16/5/10.
//  Copyright © 2016年 Mr.B. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include "Vector.h"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <unistd.h>

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






// 初始视角（ 视点在(+z, -y)处 ）
#define KK .000001
#define REST (700000000 * KK)
#define REST_Z (REST)
#define REST_Y (-REST)
#define OFFSET (200000 * KK)


using namespace std;


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



class CPlanet;
class CSolar;

/*****************************/
// CIntegrator
/****************************/
class CIntegrator{
protected:
    double DT;
public:
    virtual void Update(CSolar &S)=0;
    void SetDT(double dt){DT = dt;}
    double GetDT()const{return DT;}
};


/*****************************/
// CSI2
/****************************/
class CSI2:public CIntegrator{
public:
    virtual void Update(CSolar &S);
};

/*****************************/
// CSI4
/****************************/
class CSI4:public CIntegrator{
public:
    virtual void Update(CSolar &S);
};

/*****************************/
// CSI6
/****************************/
class CSI6:public CIntegrator{
public:
    virtual void Update(CSolar &S);
};

/*****************************/
// CAC
/****************************/
class CGrid:public CIntegrator{
public:
    CGrid();
    virtual void Update(CSolar &S);
private:
    list<CPlanet> Cell[N][N][N];
    double Phi[N+2][N+2][N+2];
    void FFT();
    void UpdateCells();
    
};

/*****************************/
// CPlanet
/****************************/
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

/*****************************/
// CSolar
/****************************/
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
    friend class CGrid;
};



extern CSolar Solar;
extern CPlanet* P;

/*****************************/
// CDisplay
/****************************/
class CDisplay{
public:
    static void display(void);
    static void reshape (int w, int h);
private:
    static GLdouble eyeX, eyeY, eyeZ;
    static GLdouble centerX, centerY, centerZ;
    static GLdouble upX, upY, upZ;
    static double g;
    static GLdouble poX;
    static GLdouble poY;
    static GLdouble poZ;
    
    friend class CControl;
    
};

/*****************************/
// CControl
/****************************/
class CControl{
public:

    static void UpdateState();
    static void keyboard(unsigned char key, int x, int y);
    static void init();
    static void initSolar();
    static void SetSolarManually();
    static void AddNewPlanet();
    static void AddRandomPlanet();
    static void Terminate();
    
private:
    
    static bool ShowRecord;
    static bool play;
    
    friend void init();
    friend class CDisplay;

};



#endif /* Header_h */
