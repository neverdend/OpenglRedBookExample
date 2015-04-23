//
//  main.cpp
//  Example2-16
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

#include <math.h>
#include <iostream>
#include <assert.h>

#define X .525731112119133606
#define Z .850650808352039932

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

void drawtriangle(float *v1, float *v2, float *v3)
{
    glBegin(GL_TRIANGLES);
    glNormal3fv(v1); glVertex3fv(v1);
    glNormal3fv(v2); glVertex3fv(v2);
    glNormal3fv(v3); glVertex3fv(v3);
    glEnd();
}

void normalize(float v[3]) {
    GLfloat d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    if (d == 0.0) {
        assert("zero length vector");
        return;
    }
    v[0] /= d; v[1] /= d; v[2] /= d;
}

void subdivide(float *v1, float *v2, float *v3)
{
    GLfloat v12[3], v23[3], v31[3];
    GLint i;
    
    for (i = 0; i < 3; i++) {
        v12[i] = v1[i]+v2[i];
        v23[i] = v2[i]+v3[i];
        v31[i] = v3[i]+v1[i];
    }
    normalize(v12);
    normalize(v23);
    normalize(v31);
    drawtriangle(v1, v12, v31);
    drawtriangle(v2, v23, v12);
    drawtriangle(v3, v31, v23);
    drawtriangle(v12, v23, v31);
}

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
    

    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // 绘制的图形以线框模式显示
    

    int i;
    
    glBegin(GL_TRIANGLES);
    for (i = 0; i < 20; i++) {
        subdivide(&vdata[tindices[i][0]][0],
                  &vdata[tindices[i][1]][0],
                  &vdata[tindices[i][2]][0]);
    }
    glEnd();
    
    glutSwapBuffers();
}

void idle()
{
    return;
}

int main(int argc, char * argv[])
{
    // initialize a window
    glutInit(&argc, argv);
    glutInitWindowSize(480,480);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Example2-16");
    
    // register event handler
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    // update the window and check for events
    glutMainLoop();
    
    return EXIT_SUCCESS;
}
