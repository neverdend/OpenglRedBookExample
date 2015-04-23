//
//  main.cpp
//  Example2-15
//
//  Created by 陈超 on 15/4/16.
//  Copyright (c) 2015年 Chao Chen. All rights reserved.
//

// include glut
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

void display()
{
    // 渲染之前必须先clear buffer，不然会在buffer原来残留数据的基础上进行渲染
    // glClearColor() sets what color the window will be cleared to
    glClearColor (0.0, 0.0, 0.0, 0.0);
    // glClear() uses the color just set to clear the window
    glClear (GL_COLOR_BUFFER_BIT);
    
    // glOrtho() specifies the coordinate system OpenGL assumes as it draws the final image and how the image gets mapped to the screen
    glOrtho(-1, 1, -1, 1, -1, 1); // x轴0.0~1.0, y轴0.0~1.0, z轴-1.0~1.0
    //
    //    // reset projection matrix
    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    
#define X .525731112119133606
#define Z .850650808352039932
    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // 绘制的图形以线框模式显示
    
    static GLfloat vdata[12][3] = {
        {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
        {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
        {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
    };
    static GLuint tindices[20][3] = {
        {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
        {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
        {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
        {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };
    int i;
    
    glBegin(GL_TRIANGLES);
    for (i = 0; i < 20; i++) {
        glNormal3fv(&vdata[tindices[i][0]][0]);
        glVertex3fv(&vdata[tindices[i][0]][0]);
        glNormal3fv(&vdata[tindices[i][1]][0]);
        glVertex3fv(&vdata[tindices[i][1]][0]);
        glNormal3fv(&vdata[tindices[i][2]][0]);
        glVertex3fv(&vdata[tindices[i][2]][0]);
    }
    glEnd();
    
    glutSwapBuffers();
}

void idle()
{
    glutPostRedisplay();
}

void initLight()
{
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);  // Setup The Ambient Light设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);  // Setup The Diffuse Light设置漫射光
    glLightfv(GL_LIGHT1, GL_POSITION,position);  // Position The Light设置光源位置
    glEnable(GL_LIGHTING);     // 启动光照
    glEnable(GL_LIGHT1);     // Enable Light One启用一号光源
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 0.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
}

int main(int argc, char * argv[])
{
    // initialize a window
    glutInit(&argc, argv);
    glutInitWindowSize(480,480);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Example2-15");
    
    initLight();
    
    // register event handler
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    // update the window and check for events
    glutMainLoop();
    
    return EXIT_SUCCESS;
}

