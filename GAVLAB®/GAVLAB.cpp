//
//  main.cpp
//  GAVLAB
//
//  Created by bbb on 16/5/23.
//  Copyright © 2016年 Mr.B. All rights reserved.
//

#include <cmath>
#include "Header.h"
using namespace std;
CSolar Solar;
CPlanet* P;
int main(int argc, char** argv) {
    
    CControl Control;
    Control.init();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGBA |  GLUT_SINGLE);
    glutInitWindowSize (700, 700);
    glutInitWindowPosition (700, 100);
    glutCreateWindow ("Gravitational Laboratory");
    // 用来画图的函数
    glutDisplayFunc(CDisplay::display);
    // 调整窗口大小的函数
    glutReshapeFunc(CDisplay::reshape);
    // 接受键盘命令的函数
    glutKeyboardFunc(CControl::keyboard);
    // 用来更新时步的函数
    glutIdleFunc(CControl::UpdateState);
    glutMainLoop();
    return 0;
}
