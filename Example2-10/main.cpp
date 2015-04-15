//
//  main.cpp
//  Example2-10
//
//  Created by 陈超 on 15/4/13.
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
    glOrtho(0.0, 640, 0.0, 480, -1.0, 1.0); // x轴0.0~1.0, y轴0.0~1.0, z轴-1.0~1.0
    
    // reset projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // glBegin() and glEnd() define the object to be drawn
    glBegin(GL_TRIANGLES);
        glArrayElement (2);
        glArrayElement (3);
        glArrayElement (5);
    glEnd();
    
    glutSwapBuffers();
}

void idle()
{
    glutPostRedisplay();
}

void initVertex()
{
    static GLint vertices[] = {
        25, 25,
        100, 325,
        175, 25,
        175, 325,
        250, 25,
        325, 325};
    static GLfloat colors[] = {
        1.0, 0.2, 0.2,
        0.2, 0.2, 1.0,
        0.8, 1.0, 0.2,
        0.75, 0.75, 0.75,
        0.35, 0.35, 0.35,
        0.5, 0.5, 0.5};
    
    glEnableClientState (GL_COLOR_ARRAY);
    glEnableClientState (GL_VERTEX_ARRAY);
    
    glVertexPointer (2, GL_INT, 0, vertices);
    glColorPointer (3, GL_FLOAT, 0, colors);
}

int main(int argc, char * argv[])
{
    // initialize a window
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Example2-10");
    
    // init vertex
    initVertex();
    
    // register event handler
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    // update the window and check for events
    glutMainLoop();
    
    return EXIT_SUCCESS;
}

