#include <unistd.h>
#include <cmath>
#include <iostream>
#include <cstdio>

#include "CControl.hpp"
#include "CDisplay.hpp"
#include "CSolar.hpp"

bool CControl::ShowRecord = false;
bool CControl::play = true;
int CControl::prev_mouse_x = -1;
int CControl::prev_mouse_y = -1;
double CControl::E_init = 0;

// receive commands from the keyboard
void CControl::keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            CDisplay::g *= 1.5;
            break;
        case '-':
            CDisplay::g /= 1.5;
            break;
        case 's':
            DEBUG_TEST("zoom out\n");
            CDisplay::eyeX *= 1.5;
            CDisplay::eyeY *= 1.5;
            CDisplay::eyeZ *= 1.5;
            break;
        case 'w':
            DEBUG_TEST("zoom in\n");
            CDisplay::eyeX /= 1.5;
            CDisplay::eyeY /= 1.5;
            CDisplay::eyeZ /= 1.5;
            break;
        case 'a':
            DEBUG_TEST("slow down simulation\n");
            Solar.SetStep(Solar.GetStep() * 0.8);
            break;
        case 'd':
            DEBUG_TEST("speed up simulation\n");
            Solar.SetStep(Solar.GetStep() / 0.8);
            break;
        case 'l':
            CDisplay::centerX -= 0.5 * CDisplay::g * OFFSET;
            break;
        case 'j':
            CDisplay::centerX += 0.5 * CDisplay::g * OFFSET;
            break;
        case 'i':
            CDisplay::centerY += CDisplay::g * OFFSET;
            break;
        case 'k':
            CDisplay::centerY -= CDisplay::g * OFFSET;
            break;
        case 'r':
            CDisplay::eyeX = 2.8;
            CDisplay::eyeY = 1.4;
            CDisplay::eyeZ = 2.4;
            CDisplay::centerX = 0;
            CDisplay::centerY = 0;
            CDisplay::centerZ = 0;
            CDisplay::upX = 0;
            CDisplay::upY = 0;
            CDisplay::upZ = 1;
            break;
        case 'q':
            Terminate();
            break;
        case ' ':
            play = !play;
            break;
        default:
            break;
    }
    if (ShowRecord == true) {
        printf("LookAt:(%lf,%lf,%lf)\n", CDisplay::eyeX, CDisplay::eyeY,
               CDisplay::eyeZ);
    }
}

// reset the prev_mouse position to -1 when release the button
void CControl::mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            DEBUG_TEST("button pressed\n");
            prev_mouse_x = -1;
            prev_mouse_y = -1;
        }
    }
}

// receive the action from the mouse
void CControl::motion(int x, int y) {
    if (prev_mouse_x == -1) prev_mouse_x = x;
    if (prev_mouse_y == -1) prev_mouse_y = y;
    int delta_x = x - prev_mouse_x;
    int delta_y = y - prev_mouse_y;

    double dtheta = CDisplay::g * 3.14 * delta_x / 700;
    GLdouble new_eyeX, new_eyeY, new_eyeZ;
    // update the eyeX and eyeY based on rotation matrix
    new_eyeX =
        CDisplay::eyeX * std::cos(dtheta) - CDisplay::eyeY * std::sin(dtheta);
    new_eyeY =
        CDisplay::eyeX * std::sin(dtheta) + CDisplay::eyeY * std::cos(dtheta);

    // update eyeZ and re-normalize
    new_eyeZ = CDisplay::eyeZ + delta_y * 0.01 * CDisplay::g;
    double oldR = std::sqrt(new_eyeX * new_eyeX + new_eyeY * new_eyeY +
                            CDisplay::eyeZ * CDisplay::eyeZ);
    double newR = std::sqrt(new_eyeX * new_eyeX + new_eyeY * new_eyeY +
                            new_eyeZ * new_eyeZ);

    CDisplay::eyeX = new_eyeX * oldR / newR;
    CDisplay::eyeY = new_eyeY * oldR / newR;
    CDisplay::eyeZ = new_eyeZ * oldR / newR;

    prev_mouse_x = x;
    prev_mouse_y = y;
    DEBUG_TEST("dx=%d, dy=%d\n", delta_x, delta_y);
}

// update the state of the GLUT display
void CControl::UpdateState() {
    if (play) {
        Solar.UpdateSolar();
        auto energy = Solar.GetTotalEnergy();
        if (E_init == 0) E_init = energy;
        DEBUG_TEST("energy = %.10f\n", energy/E_init-1);
    }
    glutPostRedisplay();
}

// initailize the system from the command line input
void CControl::init() {
    Solar.Stars.clear();
    printf("---------------------------------------------\n");
    printf(">> Welcome to my Gravitational Laboratory!\n");
    usleep(100000);
    printf(
        ">> In this program you can enjoy yourself in the word of gravity\n");
    usleep(100000);
    printf(">> So want do you want to do?\n");
    usleep(100000);
    printf(">> A:Show we the real solar system!\n");
    printf(">> B:I want to set my solar system manually\n");
    printf(">> C:Generate some planet randomly!\n");
    printf(">> ");
    string command;
    cin >> command;
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

    printf(">> Do you want the data exported in command window?\n");
    printf(">> A:Yes\n>> B:No\n>> ");
    cin >> command;
    switch (command[0]) {
        case 'A':
            CControl::ShowRecord = true;
            break;
        case 'B':
            CControl::ShowRecord = false;
            break;
        default:
            break;
    }
    printf(">> Okay! Everything has prepared!\n");
    usleep(100000);
    printf(">> Please enjoy!\n");
    printf(">> Loading......\n");
    usleep(100000);
    printf(">> Tip:You can press ESC to quit the program\n");
    printf(">> Loading......\n");
    usleep(100000);
    printf(">> Tip:You can press A W S D X to change the position of camera");
    printf("and J K L I to change the orientation of the camra\n");
    printf(">> Loading......\n");
    usleep(100000);
    printf(">> Tip:To pause the program,press space\n");
    usleep(100000);
    printf(">> Loading completed\n");
    usleep(100000);
}

// initailze the solar system
void CControl::initSolar() {
    printf(">> Please wait...\n");
    double dt = DAY * 0.1;
    Solar.SetMass(MS);
    Solar.SetI(SI6);
    Solar.SetStep(dt);
    CPlanet mercuy("MERCURY", 0.0553 * ME, 0.35, 0.3871 * RA, 0, 344, 0,
                   52716.3, 0, .2, .2, .5);
    CPlanet venus("VENUS", 0.815 * ME, 0.8, 0.7233 * RA, 0, 0, 0, 35200, 0, 1,
                  .7, 0);
    CPlanet earth("EARTH", ME, 0.8, RA, 0, 0, 0, 29789, 0, 0, 1, 0);
    CPlanet mars("MARS", 0.1074 * ME, 3, 1.523 * RA, 0, 0, 0, 25310, 0, 1, 1,
                 0);
    CPlanet jupiter("JUPITER", 317.834 * ME, 2.5, 5.202 * RA, 0, 0, 0, 13413, 0,
                    1, .5, .5);
    CPlanet saturnus("SATURNUS", 95.159 * ME, 1.5, 9.544 * RA, 0, 0, 0, 9927.7,
                     0, 1, 1, .5);
    CPlanet uranus("URANUS", 14.5 * ME, 1.5, 19.19 * RA, 0, 0, 0, 6978, 0, .5,
                   1, .5);
    CPlanet neptune("NEPTUNE", 17.2 * ME, 0.35, 30.13 * RA, 0, 0, 0, 5670.9, 0,
                    .4, .4, .4);
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

void CControl::AddNewPlanet() {
    string name;
    double mass;
    double radius;
    double x, y, z, vx, vy, vz;
    double r, g, b;

    printf(">> name:");
    cin >> name;
    printf(">> mass/kg:");
    cin >> mass;
    mass /= 1e18;
    printf(">> radius/km:");
    cin >> radius;
    radius /= 1.4e6;
    printf(">> Assuming the sun is in (0,0,0)\n");
    printf(">> Position X/AU:");
    cin >> x;
    x *= RA;
    printf(">> Position Y/AU:");
    cin >> y;
    y *= RA;
    printf(">> Position Z/AU:");
    cin >> z;
    z *= RA;
    printf(">> Velocity Vx/ms-1:");
    cin >> vx;
    printf(">> Velocity Vy/ms-1:");
    cin >> vy;
    printf(">> Velocity Vz/ms-1:");
    cin >> vz;
    printf(">> Set the Color now\n");
    printf(">> Red:");
    cin >> r;
    printf(">> Green:");
    cin >> g;
    printf(">> Blue:");
    cin >> b;

    P = new CPlanet(name, mass, radius, x, y, z, vx, vy, vz, r, g, b);
    Solar.AddPlanet(*P);
}

void CControl::SetSolarManually() {
    printf(">> Seting......\n");
    usleep(3000000);
    printf(">> Okay now you can setup your own solar system\n");
    usleep(1000000);
    printf(">> Your action?\n");
    printf(">> A:Set the center mass of my solar system\n");
    printf(">> B:Set the Integrator\n");
    printf(">> C:Add a new planet\n");
    printf(">> X:Okay I'm done\n");
    string command;
    string IntrgratorType;

    bool Ismass = false, IsIntegrator = false;
    bool isbreak = false;
    while (cin >> command) {
        switch (command[0]) {
            case 'A':
                double Mass;
                printf(">> Mass/kg:");
                cin >> Mass;
                Solar.SetMass(Mass);
                Ismass = true;
                break;
            case 'B':
                printf(">> You can choose the following Integrators\n");
                printf(">> A:SI2\n>> B:SI4\n>> C:SI6\n>> D:Grid\n>> ");
                cin >> IntrgratorType;
                switch (IntrgratorType[0]) {
                    case 'A':
                        Solar.SetI(SI2);
                        IsIntegrator = true;
                        break;
                    case 'B':
                        Solar.SetI(SI4);
                        IsIntegrator = true;
                        break;
                    case 'C':
                        Solar.SetI(SI6);
                        IsIntegrator = true;
                        break;
                    case 'D':
                        Solar.SetI(Grid);
                        IsIntegrator = true;
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
                    isbreak = true;
                } else {
                    if (!IsIntegrator) {
                        printf(">> You didn't set your solar's integrator\n");
                    }
                    if (!Ismass) {
                        printf(">> You didn't set your solar's center mass\n");
                    }
                }
                break;
            default:
                break;
        }

        if (isbreak) {
            break;
        }

        printf(">> Your action?\n");
        printf(">> A:Set the center mass of my solar system\n");
        printf(">> B:Set the Integrator\n");
        printf(">> C:Add a new planet\n");
        printf(">> X:Okay I'm done\n");
    }

    Solar.SetStep(DAY * 0.1);
}

void CControl::AddRandomPlanet() {
    int n;
    printf(">> How many planet:N=");
    cin >> n;
    printf(">> Prepareing...\n");
    double dt = DAY * 0.1;
    Solar.SetMass(MS);
    Solar.SetI(SI4);
    Solar.SetStep(dt);
    while (n--) {
        Solar.GenerateRandomPlanet();
    }
    printf(">> done\n");
}

void CControl::Terminate() {
    printf(">> The simuation is over\n");
    printf(">> Thanks for using\n");
    exit(0);
}
