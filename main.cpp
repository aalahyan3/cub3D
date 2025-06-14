#include <GLUT/glut.h>
#include <iostream>
float px,py;
void draw_player()
{
    glColor3f(1,1,0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px,py);
    glEnd();
}
void key_press(unsigned char  key,int x, int y )
{
    if(key == 'a')
    {
         px-=10;
    }
    if(key == 'd')
        px +=10;
    if(key == 'w')
        py -= 10;
    if(key == 's')
        py += 10;
    glutPostRedisplay();
}
void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     draw_player();
    glutSwapBuffers();
}

void init()
{
    glClearColor(0.3,0.3,0.3,0);
    px = 300;
    py = 300;
    gluOrtho2D(0,1024,512,0);
}
int main(int argc, char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024,512);
    glutCreateWindow("raycasting");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(key_press);
    glutMainLoop();
}