//
//  main.cpp
//  Example3-1 Transformed Cube
//
//  Created by 陈超 on 15/4/16.
//  Copyright (c) 2015年 Chao Chen. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    
    // 此时使用的矩阵是MODELVIEW MATRIX
    // reset modelview matrix
    glLoadIdentity ();
    
    // viewing transformation
    gluLookAt (0.8, 1.2, 1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);    // camera/viewpoint的世界坐标(0.8, 1.2, 1)，视线一端是camera另一端是(0, 0, 0)，视见体由下向上方向为(0, 1, 0)
    
    // modeling transformation
    glScalef (1.0, 2.0, 1.0);   // scale
    
    // draw
    glutWireCube (1.0); // wire cube的中心在(0, 0, 0)，边长为1
    
    glFlush ();
}

void reshape (int w, int h) //  is called when the window is first created and whenever the window is moved or reshaped.
{
    // 设置viewport大小为屏幕窗口大小
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
    // 使用PROJECTION MATRIX
    glMatrixMode (GL_PROJECTION);
    // reset projection matrix
    glLoadIdentity ();
    // 设定透视投影视见体，
    glFrustum (-1, 1, -1, 1, 0.56, 5);  // 在eye coordinates下设置视见体。前两个参数是near clipping plane的u轴坐标范围，中间两个参数是near clipping plane的v轴坐标范围，后两个参数是near clipping plane的n轴坐标范围。near clipping plane即是投影平面，指定的坐标范围构成了投影平面上的窗口
    
    // 使用MODELVIEW MATRIX，只是为了保证之后矩阵操作是使用modelview matrix
    glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
