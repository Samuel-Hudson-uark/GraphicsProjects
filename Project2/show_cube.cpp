#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;

#define MIN_X_VIEW -1
#define MAX_X_VIEW 1
#define MIN_Y_VIEW -1
#define MAX_Y_VIEW 1
#define MIN_Z_VIEW -1
#define MAX_Z_VIEW 1
#define MIN_X_SCREEN 0
#define MAX_X_SCREEN 500
#define MIN_Y_SCREEN 0
#define MAX_Y_SCREEN 500

float cubesize = 0.1;
float cubex = 0;
float cubey = 0;
float xspeed = 0;
float yspeed = 0;
float initx = -1;
float inity = -1;
int angle = 30;
bool isMoving = false;

void cube(float midx, float midy, float midz, float size)
{
    // Define 8 vertices
    float ax = midx - size / 2;
    float ay = midy - size / 2;
    float az = midz + size / 2;
    float bx = midx + size / 2;
    float by = midy - size / 2;
    float bz = midz + size / 2;
    float cx = midx + size / 2;
    float cy = midy + size / 2;
    float cz = midz + size / 2;
    float dx = midx - size / 2;
    float dy = midy + size / 2;
    float dz = midz + size / 2;
    float ex = midx - size / 2;
    float ey = midy - size / 2;
    float ez = midz - size / 2;
    float fx = midx + size / 2;
    float fy = midy - size / 2;
    float fz = midz - size / 2;
    float gx = midx + size / 2;
    float gy = midy + size / 2;
    float gz = midz - size / 2;
    float hx = midx - size / 2;
    float hy = midy + size / 2;
    float hz = midz - size / 2;

    // Draw 6 faces
    
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(ax, ay, az);
    glVertex3f(ex, ey, ez);
    glVertex3f(fx, fy, fz);
    glVertex3f(bx, by, bz);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(gx, gy, gz);
    glVertex3f(cx, cy, cz);
    glVertex3f(bx, by, bz);
    glVertex3f(fx, fy, fz);
    glEnd();

    if(angle < 240) {
        glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 1.0);
        glVertex3f(gx, gy, gz);
        glVertex3f(hx, hy, hz);
        glVertex3f(dx, dy, dz);
        glVertex3f(cx, cy, cz);
        glEnd();
    }
    
    if(angle < 120 || angle > 240) {
        glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(ax, ay, az);
        glVertex3f(bx, by, bz);
        glVertex3f(cx, cy, cz);
        glVertex3f(dx, dy, dz);
        glEnd();
    } else {
        glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(gx, gy, gz);
        glVertex3f(fx, fy, fz);
        glVertex3f(ex, ey, ez);
        glVertex3f(hx, hy, hz);
        glEnd();
    }

    if(angle < 120) {
        glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(ax, ay, az);
        glVertex3f(dx, dy, dz);
        glVertex3f(hx, hy, hz);
        glVertex3f(ex, ey, ez);
        glEnd();
    }

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //Display stuff here
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(cubex, cubey, 0.0);
    glRotatef(angle, 1.0, 1.0, 1.0);
    glTranslatef(-cubex, -cubey, 0.0);
    cube(cubex, cubey, 0.0, cubesize);
    glPopMatrix();
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(MIN_X_VIEW, MAX_X_VIEW, 
    MIN_Y_VIEW, MAX_X_VIEW, 
    MIN_Z_VIEW, MAX_Z_VIEW);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value)
{
    if(isMoving)
    {
        angle = (angle%360) + 1;
        if(cubex + cubesize/2 + xspeed >= 1 || cubex - cubesize/2 + xspeed <= -1)
            xspeed = -xspeed;
        if(cubey - cubesize/2 + yspeed <= -1) {
            yspeed = -yspeed/1.4;
            if(yspeed < 0.0018)
                isMoving = false;
        }
        cubex += xspeed;
        cubey += yspeed;
        yspeed -= 0.0004;
    }
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

void mouse(int button, int state, int x, int y)
{
    float x_scale = (MAX_X_VIEW - MIN_X_VIEW) / 
        (float)(glutGet(GLUT_WINDOW_WIDTH) - MIN_X_SCREEN);
    float y_scale = (MIN_Y_VIEW - MAX_Y_VIEW) / 
        (float)(glutGet(GLUT_WINDOW_HEIGHT) - MIN_Y_SCREEN);
    if(state == GLUT_DOWN)
    {
        cubex = MIN_X_VIEW + (x - MIN_X_SCREEN) * x_scale;
        cubey = MAX_Y_VIEW + (y - MIN_Y_SCREEN) * y_scale;
        if(initx == -1) {
            xspeed = 0;
            yspeed = 0;
            initx = cubex;
            inity = cubey;
            isMoving = false;
        }
        glutPostRedisplay();
    }
    else if(state == GLUT_UP)
    {
        xspeed = (initx - cubex)/15;
        yspeed = (inity - cubey)/15;
        initx = -1;
        inity = -1;
        isMoving = true;
    }
}

void motion(int x, int y)
{
    // Calculate scale factors
    float x_scale = (MAX_X_VIEW - MIN_X_VIEW) / 
        (float)(glutGet(GLUT_WINDOW_WIDTH) - MIN_X_SCREEN);
    float y_scale = (MIN_Y_VIEW - MAX_Y_VIEW) / 
        (float)(glutGet(GLUT_WINDOW_HEIGHT) - MIN_Y_SCREEN);

    // Handle mouse motion
    cubex = MIN_X_VIEW + (x - MIN_X_SCREEN) * x_scale;
    cubey = MAX_Y_VIEW + (y - MIN_Y_SCREEN) * y_scale;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(MAX_Y_SCREEN, MAX_X_SCREEN);
    glutInitWindowPosition(MAX_Y_SCREEN/2, MAX_X_SCREEN/2);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Project 2");
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    init();
    glutMainLoop();
    return 0;
}