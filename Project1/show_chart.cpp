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

float floatGL(int x)
{
   return (((x*2)/500.0) - 1);
}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT);

   ifstream file("output.txt");
   string s;
   int x1, y1, x2, y2, n;
   float r, g, b, width;
   if(file.is_open())
   {
      while(file >> s) 
      {
         if(s == "set_color") //set_color r g b
         {
            file >> r >> g >> b;
            glColor3f(r, g, b);
         }
         else if(s == "draw_point") //draw_point girth, x1, y1
         {
            file >> width >> x1 >> y1;
            glPointSize(width);
            glBegin(GL_POINTS);
               glVertex2f(floatGL(x1), floatGL(y1));
            glEnd();
         }
         else if(s == "draw_line") //draw_line girth x1 y1 x2 y2
         {
            file >> width >> x1 >> y1 >> x2 >> y2;
            glLineWidth(width);
            glBegin(GL_LINES);
               glVertex2f(floatGL(x1), floatGL(y1));
               glVertex2f(floatGL(x2), floatGL(y2));
            glEnd();
         }
         else if(s == "draw_polygon") //draw_polygon n x1, y1, ..., xn yn
         {
            file >> n;
            glBegin(GL_POLYGON);
            for(int i = 0; i < n; i++) 
            {
               file >> x1 >> y1;
               glVertex2f(floatGL(x1), floatGL(y1));
            }
            glEnd();
         }
      }
   }
   else {cout << "unable to open file.";}
   glFlush();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode (GL_PROJECTION);    
   glLoadIdentity();    
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
  glutInitWindowPosition(250, 250);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("Project 1");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}

