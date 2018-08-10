#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include "PointType.h"

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}


void draw_box(PointType origin){
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f( 1.0f + origin.x, 1.0f + origin.y, -1.0f + origin.z);
    glVertex3f(-1.0f + origin.x, 1.0f + origin.y, -1.0f + origin.z);
    glVertex3f(-1.0f + origin.x, 1.0f + origin.y,  1.0f + origin.z);
    glVertex3f( 1.0f + origin.x, 1.0f + origin.y,  1.0f + origin.z);

    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    glVertex3f( 1.0f + origin.x, -1.0f + origin.y,  1.0f + origin.z);
    glVertex3f(-1.0f + origin.x, -1.0f + origin.y,  1.0f + origin.z);
    glVertex3f(-1.0f + origin.x, -1.0f + origin.y, -1.0f + origin.z);
    glVertex3f( 1.0f + origin.x, -1.0f + origin.y, -1.0f + origin.z);

    // Front face  (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f( 1.0f + origin.x,  1.0f + origin.y, 1.0f + origin.z);
    glVertex3f(-1.0f + origin.x,  1.0f + origin.y, 1.0f + origin.z);
    glVertex3f(-1.0f + origin.x, -1.0f + origin.y, 1.0f + origin.z);
    glVertex3f( 1.0f + origin.x, -1.0f + origin.y, 1.0f + origin.z);

    // Back face (z = -1.0f)
    glColor3f(1.0f + origin.x, 1.0f + origin.y, 0.0f + origin.z);     // Yellow
    glVertex3f( 1.0f + origin.x, -1.0f + origin.y, -1.0f + origin.z);
    glVertex3f(-1.0f + origin.x, -1.0f + origin.y, -1.0f + origin.z);
    glVertex3f(-1.0f + origin.x,  1.0f + origin.y, -1.0f + origin.z);
    glVertex3f( 1.0f + origin.x,  1.0f + origin.y, -1.0f + origin.z);

    // Left face (x = -1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-1.0f + origin.x,  1.0f + origin.y,  1.0f + origin.z);
    glVertex3f(-1.0f + origin.x,  1.0f + origin.y, -1.0f + origin.z);
    glVertex3f(-1.0f + origin.x, -1.0f + origin.y, -1.0f + origin.z);
    glVertex3f(-1.0f + origin.x, -1.0f + origin.y,  1.0f + origin.z);

    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    glVertex3f(1.0f + origin.x,  1.0f + origin.y, -1.0f + origin.z);
    glVertex3f(1.0f + origin.x,  1.0f + origin.y,  1.0f + origin.z);
    glVertex3f(1.0f + origin.x, -1.0f + origin.y,  1.0f + origin.z);
    glVertex3f(1.0f + origin.x, -1.0f + origin.y, -1.0f + origin.z);
    glEnd();  // End of drawing color-cube
}

void draw_pyra(){
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
    // Front
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left
    glColor3f(1.0f,0.0f,0.0f);       // Red
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f,0.0f,1.0f);       // Blue
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glColor3f(0.0f,1.0f,0.0f);       // Green
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glEnd();   // Done drawing the pyramid
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    // Render a color-cube consisting of 6 quads with different colors
    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen

    PointType origin;
    origin.x = 0;
    origin.y = 0;
    origin.z = 0;
    draw_box(origin);

    origin.x = 3;
    origin.y = 0;
    origin.z = 0;
    draw_box(origin);

    // Render a pyramid consists of 4 triangles
    glLoadIdentity();                  // Reset the model-view matrix
    glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen
    draw_pyra();

    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
