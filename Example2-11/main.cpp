//
//  main.cpp
//  Example2-11
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
    glOrtho(-1, 2, -1, 2, -1, 2); // x轴0.0~1.0, y轴0.0~1.0, z轴-1.0~1.0
    
    // reset projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // define the object to be drawn
//    // 方法1
//    static GLubyte frontIndices[] = {4, 5, 6, 7};
//    static GLubyte rightIndices[] = {1, 2, 6, 5};
//    static GLubyte bottomIndices[] = {0, 1, 5, 4};
//    static GLubyte backIndices[] = {0, 3, 2, 1};
//    static GLubyte leftIndices[] = {0, 4, 7, 3};
//    static GLubyte topIndices[] = {2, 3, 7, 6};
//    
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frontIndices);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rightIndices);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottomIndices);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, backIndices);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, leftIndices);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topIndices);
    
    // 方法2
    static GLubyte allIndices[] = {4, 5, 6, 7, 1, 2, 6, 5,  0, 1, 5, 4, 0, 3, 2, 1,  0, 4, 7, 3, 2, 3, 7, 6};
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, allIndices);
    
    glutSwapBuffers();
}

void idle()
{
    glutPostRedisplay();
}

void initVertex()
{
    static GLint vertices[] = {
        0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1
    };
    static GLfloat colors[] = {
        1.0, 0.2, 0.2,
        0.2, 0.2, 1.0,
        0.8, 1.0, 0.2,
        0.75, 0.75, 0.75,
        0.35, 0.35, 0.35,
        0.5, 0.5, 0.5,
        1.0, 0.2, 0.2,
        0.2, 0.2, 1.0
    };
    
    glEnableClientState (GL_COLOR_ARRAY);
    glEnableClientState (GL_VERTEX_ARRAY);
    
    glVertexPointer (3, GL_INT, 0, vertices);
    glColorPointer (3, GL_FLOAT, 0, colors);
}

int main(int argc, char * argv[])
{
    // initialize a window
    glutInit(&argc, argv);
    glutInitWindowSize(480,480);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Example2-11");
    
    // init vertex
    initVertex();
    
    // register event handler
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    // update the window and check for events
    glutMainLoop();
    
    return EXIT_SUCCESS;
}
