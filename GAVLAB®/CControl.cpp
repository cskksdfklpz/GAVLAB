//
//  CControl.cpp
//  GAVLAB
//
//  Created by bbb on 16/5/26.
//  Copyright © 2016年 Mr.B. All rights reserved.
//

#include "Header.h"
/*
class CControl{
public:
    void display(void);
    void reshape (int w, int h);
    void UpdateState();
    void keyboard(unsigned char key, int x, int y);
private:
    // lookAt参数
    GLdouble eyeX = 2.8, eyeY = 1.4, eyeZ= 2.4;
    GLdouble centerX= 0, centerY= 0, centerZ= 0;
    GLdouble upX= 0, upY= 0, upZ= 1;
    double g=1.;
    GLdouble poX = 0.0f;
    GLdouble poY = 0.0f;
    GLdouble poZ = 0.0f;
    CSolar Solar;
    CPlanet* P;
    bool ShowRecord=false;
    bool play=true;
    
};
 */




bool CControl::ShowRecord=false;
bool CControl::play=true;


void CControl::keyboard(unsigned char key, int x, int y){
    
    switch (key)    {
        case '+': CDisplay::g*=10; break;
        case '-': CDisplay::g/=10.0; break;
        case 'w': CDisplay::eyeY += CDisplay::g*OFFSET; break;
        case 'x': CDisplay::eyeY -= CDisplay::g*OFFSET; break;
        case 'a': CDisplay::eyeX -= CDisplay::g*OFFSET; break;
        case 'd': CDisplay::eyeX += CDisplay::g*OFFSET; break;
        case 's': CDisplay::eyeZ -= CDisplay::g*OFFSET; break;
        case 'S': CDisplay::eyeZ += CDisplay::g*OFFSET; break;
        case 'l': CDisplay::centerX -= 0.5*CDisplay::g*OFFSET; break;
        case 'j': CDisplay::centerX += 0.5*CDisplay::g*OFFSET; break;
        case 'i': CDisplay::centerY += CDisplay::g*OFFSET; break;
        case 'k': CDisplay::centerY -= CDisplay::g*OFFSET; break;
        case 'r':
            CDisplay::eyeX = 2.8; CDisplay::eyeY = 1.4; CDisplay::eyeZ= 2.4;
            CDisplay::centerX= 0; CDisplay::centerY= 0; CDisplay::centerZ= 0;
            CDisplay::upX= 0; CDisplay::upY= 0; CDisplay::upZ= 1;
            break;
        case 27: Terminate(); break;
        case ' ':play = !play;break;
        default: break;
    }
    if(ShowRecord == true){
        printf("LookAt:(%lf,%lf,%lf)\n",CDisplay::eyeX,CDisplay::eyeY,CDisplay::eyeZ);
    }
    
}

void CControl::UpdateState(){
    if(play)
        Solar.UpdateSolar();
    glutPostRedisplay();
    
}

void CControl::init(){
    Solar.Stars.clear();
    printf("---------------------------------------------\n");
    printf(">>Welcome to my Gravitational Laboratory!\n");
    usleep(1000000);
    printf(">>In this program you can enjoy yourself in the word of gravity\n");
    usleep(1000000);
    printf(">>So want do you want to do?\n");
    usleep(1000000);
    printf(">>A:Show we the real solar system!\n");
    printf(">>B:I want to set my solar system manually\n");
    printf(">>C:Generate some planet randomly!\n");
    printf(">>");
    string command;
    cin>>command;
    switch (command[0]) {
        case 'A':
            CControl::initSolar();
            break;
        case 'B':
            CControl::SetSolarManually();
            break;
        case 'C':
            CControl::AddRandomPlanet();
            break;
        default:
            break;
    }
    
    printf(">>Do you want the data exported in command window?\n");
    printf(">>A:Yes\n>>B:No\n>>");
    cin>>command;
    switch (command[0]) {
        case 'A':
            CControl::ShowRecord=true;
            break;
        case 'B':
            CControl::ShowRecord=false;
            break;
        default:
            break;
    }
    printf(">>Okay! Everything has prepared!\n");
    usleep(1000000);
    printf(">>Please enjoy!\n");
    printf(">>Loading......\n");
    usleep(1000000);
    printf(">>Tip:You can press ESC to quit the program\n");
    printf(">>Loading......\n");
    usleep(1000000);
    printf(">>Tip:You can press A W S D X to change the position of camera");
    printf("and J K L I to change the orientation of the camra\n");
    printf(">>Loading......\n");
    usleep(1000000);
    printf(">>Tip:To pause the program,press space\n");
    usleep(1000000);
    printf(">>Loading completed\n");
    usleep(1000000);
}

void CControl::initSolar(){
    printf(">>Please wait...\n");
    double dt=DAY*0.1;
    Solar.SetMass(MS);
    Solar.SetI(SI4);
    Solar.SetStep(dt);
    CPlanet mercuy("MERCURY",0.0553*ME,0.35,0.3871*RA,0,344,0,52716.3,0,.2, .2, .5);
    CPlanet venus("VENUS",0.815*ME,0.8,0.7233*RA,0,0,0,35200,0, 1, .7, 0);
    CPlanet earth("EARTH",ME,0.8,RA,0,0,0,29789,0, 0, 1, 0);
    CPlanet mars("MARS",0.1074*ME,3,1.523*RA,0,0,0,25310,0, 1, 1, 0);
    CPlanet jupiter("JUPITER",317.834*ME,2.5,5.202*RA,0,0,0,13413,0, 1, .5, .5);
    CPlanet saturnus("SATURNUS",95.159*ME,1.5,9.544*RA,0,0,0,9927.7,0, 1, 1, .5);
    CPlanet uranus("URANUS",14.5*ME,1.5,19.19*RA,0,0,0,6978,0, .5, 1, .5);
    CPlanet neptune("NEPTUNE",17.2*ME,0.35,30.13*RA,0,0,0,5670.9,0, .4, .4, .4);
    Solar.AddPlanet(mercuy);
    Solar.AddPlanet(venus);
    Solar.AddPlanet(earth);
    Solar.AddPlanet(mars);
    Solar.AddPlanet(jupiter);
    Solar.AddPlanet(saturnus);
    Solar.AddPlanet(uranus);
    Solar.AddPlanet(neptune);
    printf(">>done\n");
}

void CControl::AddNewPlanet(){
    string name;
    double mass;
    double radius;
    double x,y,z,vx,vy,vz;
    double r,g,b;
    
    printf(">>name:");
    cin>>name;
    printf(">>mass/kg:");
    cin>>mass;
    mass/=1e18;
    printf(">>radius/km:");
    cin>>radius;
    radius/=1.4e6;
    printf(">>Assuming the sun is in (0,0,0)\n");
    printf(">>Position X/AU:");
    cin>>x;
    x*=RA;
    printf(">>Position Y/AU:");
    cin>>y;
    y*=RA;
    printf(">>Position Z/AU:");
    cin>>z;
    z*=RA;
    printf(">>Velocity Vx/ms-1:");
    cin>>vx;
    printf(">>Velocity Vy/ms-1:");
    cin>>vy;
    printf(">>Velocity Vz/ms-1:");
    cin>>vz;
    printf(">>Set the Color now\n");
    printf(">>Red:");
    cin>>r;
    printf(">>Green:");
    cin>>g;
    printf(">>Blue:");
    cin>>b;
    
    P = new CPlanet(name,mass,radius,x,y,z,vx,vy,vz,r,g,b);
    Solar.AddPlanet(*P);
    
}

void CControl::SetSolarManually(){
    
    printf(">>Seting......\n");
    usleep(3000000);
    printf(">>Okay now you can setup your own solar system\n");
    usleep(1000000);
    printf(">>Your action?\n");
    printf(">>A:Set the center mass of my solar system\n");
    printf(">>B:Set the Integrator\n");
    printf(">>C:Add a new planet\n");
    printf(">>X:Okay I'm done\n");
    string command;
    string IntrgratorType;
    
    bool Ismass=false,IsIntegrator=false;
    bool isbreak=false;
    while (cin>>command) {
        switch (command[0]) {
            case 'A':
                double Mass;
                printf(">>Mass/kg:");
                cin>>Mass;
                Solar.SetMass(Mass);
                Ismass = true;
                break;
            case 'B':
                printf(">>You can choose the following Integrators\n");
                printf(">>A:SI2\n>>B:SI4\n>>C:SI6\n>>D:Grid\n>>");
                cin>>IntrgratorType;
                switch (IntrgratorType[0]) {
                    case 'A':
                        Solar.SetI(SI2);
                        IsIntegrator=true;
                        break;
                    case 'B':
                        Solar.SetI(SI4);
                        IsIntegrator=true;
                        break;
                    case 'C':
                        Solar.SetI(SI6);
                        IsIntegrator=true;
                        break;
                    case 'D':
                        Solar.SetI(Grid);
                        IsIntegrator=true;
                        break;
                    default:
                        break;
                }
                break;
            case 'C':
                CControl::AddNewPlanet();
                break;
            case 'X':
                if (IsIntegrator && Ismass) {
                    isbreak=true;
                }
                else{
                    if (!IsIntegrator) {
                        printf(">>You didn't set your solar's integrator\n");
                    }
                    if (!Ismass) {
                        printf(">>You didn't set your solar's center mass\n");
                    }
                }
                break;
            default:
                break;
        }
        
        if (isbreak) {
            break;
        }
        
        printf(">>Your action?\n");
        printf(">>A:Set the center mass of my solar system\n");
        printf(">>B:Set the Integrator\n");
        printf(">>C:Add a new planet\n");
        printf(">>X:Okay I'm done\n");
        
    }
    
    Solar.SetStep(DAY*0.1);
}

void CControl::AddRandomPlanet(){
    int n;
    printf(">>How many planet:N=");
    cin>>n;
    printf(">>Prepareing...\n");
    double dt=DAY*0.1;
    Solar.SetMass(MS);
    Solar.SetI(SI4);
    Solar.SetStep(dt);
    while (n--) {
        Solar.GenerateRandomPlanet();
    }
    printf(">>done\n");
    
}

void CControl::Terminate(){
    printf(">>The simuation is over\n");
    printf(">>Thanks for using\n");
    exit(0);
}











