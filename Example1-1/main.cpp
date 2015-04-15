//
//  main.cpp
//  Example1-1
//
//  Created by 陈超 on 15-4-10.
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
    
    // glColor3f() sets what color to use for drawing objects. All objects drawn after this call use this color, until it's changed with another call to set the color.
    glColor3f (1.0, 1.0, 1.0);
    
    // glOrtho() specifies the coordinate system OpenGL assumes as it draws the final image and how the image gets mapped to the screen
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); // x轴0.0~1.0, y轴0.0~1.0, z轴-1.0~1.0
    
    // reset projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // glBegin() and glEnd() define the object to be drawn
    glBegin(GL_POLYGON);
        // glVertex3f() defines vertex
        glVertex3f (0.25, 0.25, 0.0);
        glVertex3f (0.75, 0.25, 0.0);
        glVertex3f (0.75, 0.75, 0.0);
        glVertex3f (0.25, 0.75, 0.0);
    glEnd();
    
    // glFlush() ensures that the drawing commands are actually executed rather than stored in a buffer awaiting additional OpenGL commands
    glFlush();
}

int main(int argc, char * argv[])
{
    // initialize a window
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Example1-1");
    
    glutDisplayFunc(display);
    
    // update the window and check for events
    glutMainLoop();
    
    return EXIT_SUCCESS;
}
