//
//  main.cpp
//  LightExample
//
//  Created by 陈超 on 15/4/16.
//  Copyright (c) 2015年 Chao Chen. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <cmath>
#include <stdio.h>

struct vector3
{
    float x, y, z;
};

// 定义四面体的四个点
float r = 1.0f;
float a[] = {-0.5, -0.5, -0.25};
float b[] = {-0.5, r-0.5f, -0.25};
float c[] = {(float)sqrt(3.0f)*r/2.0f-0.5f, r/2.0f-0.5f, -0.25f};
float d[] = {(float)sqrt(3.0f)*r/6.0f-0.5f, r/2.0f-0.5f, (float)sqrt(6.0f)*r/3.0f-0.25f};

// 四个面的法向量
vector3 normalACB, normalABD, normalBCD, normalADC;

// 绕 x 轴， y 轴旋转的角度
int anglex = 0, angley = 0;

// 定义光源
float light_pos[] = {2.0, 2.0, 2.0, 0.0};
float light_Ka[] = {1.0, 0.0, 0.0, 1.0};
float light_Kd[] = {1.0, 1.0, 1.0, 1.0};
float light_Ks[] = {1.0, 1.0, 1.0, 1.0};

// 计算一个三角形的法向量
vector3 calculateNormal(float a[], float b[], float c[])
{
    float ab[3], ac[3];
    vector3 normal;
    ab[0] = b[0] - a[0];
    ab[1] = b[1] - a[1];
    ab[2] = b[2] - a[2];
    ac[0] = c[0] - a[0];
    ac[1] = c[1] - a[1];
    ac[2] = c[2] - a[2];
    
    normal.x = ab[1]*ac[2] - ab[2]*ac[1];
    normal.y = ab[2]*ac[0] - ab[0]*ac[2];
    normal.z = ab[0]*ac[1] - ab[1]*ac[0];
    
    float const l = std::sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
    normal.x/= l;
    normal.y/= l;
    normal.z/= l;
    
    return normal;
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void idle()
{
}

void timer (int)
{
    anglex = (anglex + 1) % 360;
    angley = (angley + 1) % 360;
    glutTimerFunc(10,timer,1);
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 画坐标轴
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(5.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 5.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 5.0);
    glEnd();
    
    glPushMatrix();
    glRotated(anglex, 1.0, 0.0, 0.0);
    
    normalACB = calculateNormal(a, b, c);
    normalABD = calculateNormal(a, d, b);
    normalBCD = calculateNormal(b, d, c);
    normalADC = calculateNormal(a, c, d);
    
    // 画四个面
    glBegin(GL_TRIANGLES);
    glNormal3f(normalACB.x, normalACB.y, normalACB.z);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(normalABD.x, normalABD.y, normalABD.z);
    glVertex3fv(a);
    glVertex3fv(d);
    glVertex3fv(b);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(normalBCD.x, normalBCD.y, normalBCD.z);
    glVertex3fv(b);
    glVertex3fv(d);
    glVertex3fv(c);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(normalADC.x, normalADC.y, normalADC.z);
    glVertex3fv(a);
    glVertex3fv(c);
    glVertex3fv(d);
    glEnd();
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0 * w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("test");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutTimerFunc(10,timer,1);
    glutMainLoop();
    return 0;
}
