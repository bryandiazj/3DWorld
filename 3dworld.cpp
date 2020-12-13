#include <stdlib.h>
#include <math.h>
#include <random>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include "Polyhedron.h"

static int window;
static int menu_id;
static int submenu_id;
static int value = 0;


std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(-1, 1);

std::uniform_real_distribution<double> distribution2(-1, 1);

void menu(int num) {//-------------------------------------menu function----------------------------
    if (num == 0) {
        glutDestroyWindow(window);
        exit(0);
    }
    else {
        value = num;
    }
    glutPostRedisplay();
}

void createMenu(void) {//----------------------------------------this as well--------------------------------------------------
    submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Tower", 2);
    glutAddMenuEntry("Tree", 3);
    glutAddMenuEntry("Stone", 4);
    //glutAddMenuEntry("Tower", 5);     
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Draw", submenu_id);
    glutAddMenuEntry("Quit", 0);     
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


vector<Polyhedron> polys;

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 0.9};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */

void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if (h == 0)
    h = 1;
  float ratio =  w * 1.0 / h;

  // Use the Projection Matrix
  glMatrixMode(GL_PROJECTION);

  // Reset Matrix
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // Set the correct perspective.
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);

  // Get Back to the Modelview
  glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan() {

  //glColor3f(1.0f, 1.0f, 1.0f);
  glColor3f(1.0f, 0.0f, 0.0f);

  // Draw Body

  glTranslatef(0.0f ,0.75f, 0.0f);
  glutSolidSphere(0.75f,20,20);

  // Draw Head
  glTranslatef(0.0f, 1.0f, 0.0f);
  glutSolidSphere(0.25f,20,20);

  // Draw Eyes
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.05f, 0.10f, 0.18f);
  glutSolidSphere(0.05f,10,10);
  glTranslatef(-0.1f, 0.0f, 0.0f);
  glutSolidSphere(0.05f,10,10);
  glPopMatrix();

  // Draw Nose
  glColor3f(1.0f, 0.5f , 0.5f);
  glRotatef(0.0f,1.0f, 0.0f, 0.0f);
  glutSolidCone(0.08f,0.5f,10,2);
}

void computePos(float deltaMove) {

  x += deltaMove * lx * 0.2f;
  z += deltaMove * lz * 0.2f;
}

void computeDir(float deltaAngle) {

  angle += deltaAngle;
  lx = sin(angle);
  lz = -cos(angle);
}

void init() {
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  glClearColor (1.0, 1.0, 1.0, 1.0);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_COLOR_MATERIAL);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}


void tree(void) {

    ofstream outfile;
    outfile.open("tree.txt");

    for (int i = 0; i < 10; i++) {

        double randx = (1.0 * (rand() % 100)) - 50;
        double randy = -8;
        double randz = (1.0 * (rand() % 100)) - 50;

        outfile << "name1 " << "models/CartoonTree1-trunk.obj" << endl;
        outfile << "name2 " << "models/CartoonTree1-top.obj" << endl;
        outfile << "randx " << randx << endl;
        outfile << "randy " << randy << endl;
        outfile << "randz " << randz << endl;
        outfile << "rotY " << 0 << endl;
        outfile << "colorx1 " << .59 << endl;
        outfile << "colory1 " << .29 << endl;
        outfile << "colorz1 " << 0 << endl;
        outfile << "colorx2 " << .08 << endl;
        outfile << "colory2 " << .59 << endl;
        outfile << "colorz2 " << .15 << endl;

        Polyhedron pz("models/CartoonTree1-trunk.obj", Vector3d(randx, randy, randz), 0, Vector3d(.59, .29, 0));
        pz.Load();
        pz.Print();
        polys.push_back(pz);

        Polyhedron pk("models/CartoonTree1-top.obj", Vector3d(randx, randy, randz), 0, Vector3d(.08, .59, .15));
        pk.Load();
        pk.Print();
        polys.push_back(pk);
    }
    outfile.close();
}

void tower(void) {//---------------------------------------------need to work on-------------------------

    ofstream outfile;

    outfile.open("tower.txt");

    for (int i = 0; i < 10; i++){
        double randx = (1.0 * (rand() % 100)) - 50;
        double randz = (1.0 * (rand() % 100)) - 50;
        for (int j = 0; j < 30; j++) {

            
            double randy = j * 4;
           

            double rotY = rand() % 360;

            double colorx = .4;
            double colory = .4;
            double colorz = .4;

            outfile << "name " << "models/cube.obj" << endl;
            outfile << "randx " << randx << endl;
            outfile << "randy " << 0 << endl;
            outfile << "randz " << randz << endl;
            outfile << "rotY " << 0 << endl;
            outfile << "colorx " << .4 << endl;
            outfile << "colory " << .4 << endl;
            outfile << "colorz " << .4 << endl;

            Polyhedron pz("models/cube.obj", Vector3d(randx, randy, randz), 0, Vector3d(colorx, colory, colorz));
            pz.Load();
            pz.Print();
            polys.push_back(pz);
        }
    }
    outfile.close();
}

void stone(void) {

    ofstream outfile;
    outfile.open("stone.txt");

    for (int i = 0; i < 10; i++) {

        double randx = (1.0 * (rand() % 100)) - 50;
        double randy = 0;
        double randz = (1.0 * (rand() % 100)) - 50;
        double rotY = rand() % 360;

        double random_number = distribution(generator);
        double random_number2 = distribution2(generator);

        double totalx = randx + random_number;
        double totalz = randz + random_number2;


        outfile << "name " << "models/stone2_S.obj" << endl;
        outfile << "randx " << totalx << endl;
        outfile << "randy " << randy << endl;
        outfile << "randz " << totalz << endl;
        outfile << "rotY " << rotY << endl;
        outfile << "colorx " << .59 << endl;
        outfile << "colory " << .14 << endl;
        outfile << "colorz " << .32 << endl;


        Polyhedron pz("models/stone2_S.obj", Vector3d(totalx, randy, totalz), rotY, Vector3d(.59, .14, .32));
        pz.Load();
        pz.Print();
        polys.push_back(pz);

    }
    outfile.close();
}



void initPolyhedron() {
  //TODO
  /*
  Polyhedron p1("models/cube.obj", Vector3d(20,19,-15), 0, Vector3d(1,0,0));
  p1.Load();
  p1.Recenter();
  p1.Print();
  polys.push_back(p1);

  Polyhedron p2("models/cube.obj", Vector3d(20, 10, 0), 0, Vector3d(0, 1, 0));
  p2.Load();
  p2.RecenterXZ();
  p2.Print();
  polys.push_back(p2);
  */


    tower(); 
    //tree();
    //stone();

  

  /*
  for (int i = 0; i < 30; i++) { //-------------------------this is to check if the recenter and recenterxy work

      double randx = (1.0 * (rand() % 100)) - 50;
      double randy = (1.0 * (rand() % 100)) - 50;
      double randz = (1.0 * (rand() % 100)) - 50;

      double rotY = rand() % 360;

      double colorx = (1.0 * rand() / RAND_MAX);
      double colory = (1.0 * rand() / RAND_MAX);
      double colorz = (1.0 * rand() / RAND_MAX);

     Polyhedron p3("models/rocket.obj", Vector3d(randx, randy, randz), 0, Vector3d(colorx, colory, colorz));
      p3.Load();
      //p3.RecenterXZ();
      p3.Print();
      polys.push_back(p3);
  }*/  
}

void loadFromFile(string filename) {//------------------work_in_progress-----------------------------
    ifstream infile;
    if (filename == "stone.txt") {
        infile.open("stone.txt");
        string s, name;
        int randx, randy, randz, rotY, colorx, colory, colorz;
        while (infile >> s) {
            if (s == "name") {
                string _name;
                infile >> _name;
                name = _name;
            }
            else if (s == "randx") {
                int x;
                infile >> x;
                randx = x;
            }
            else if (s == "randy") {
                int y;
                infile >> y;
                randy = y;
            }
            else if (s == "randz") {
                int z;
                infile >> z;
                randz = z;
            }
            else if (s == "rotY") {
                int ry;
                infile >> ry;
                rotY = ry;
            }
            else if (s == "colorx") {
                int cx;
                infile >> cx;
                colorx = cx;
            }
            else if (s == "colory") {
                int cy;
                infile >> cy;
                colory = cy;
            }
            else if (s == "colorz") {
                int cz;
                infile >> cz;
                colorz = cz;
            }
            Polyhedron stone(name, Vector3d(randx, randy, randz), rotY, Vector3d(colorx, colory, colorz));
            stone.Load();
            stone.Print();
            polys.push_back(stone);
        }


    }
}

void renderScene(void) {

  if (deltaMove)
    computePos(deltaMove);
  if (deltaAngle)
    computeDir(deltaAngle);

  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  if (value == 1) {//--------------------------------for the menu function----------------------------------------
      return; //glutPostRedisplay();
  }
  else if (value == 2) {
      tower();
  }
  else if (value == 3) {
      tree();
  }
  else if (value == 4) {
      stone();
  }

  glFlush();

  // Reset transformations
  glLoadIdentity();
  // Set the camera
  gluLookAt(	x, 1.0f, z,
      x+lx, 1.0f,  z+lz,
      0.0f, 1.0f,  0.0f);

  // Draw ground

  glColor3f(0.9f, 0.9f, 0.9f);
  glBegin(GL_QUADS);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glVertex3f(-100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f, -100.0f);
  glEnd();

  // Draw 36 SnowMen

  if(1)
  for(int i = -3; i < 3; i++)
    for(int j=-3; j < 3; j++) {
      glPushMatrix();
      glTranslatef(i*10.0,0,j * 10.0);
      //drawSnowMan();
      glPopMatrix();
    }



  for(int i=0; i<(int)polys.size(); i++) {
    polys[i].Draw();
  }

  

  glutSwapBuffers();
}

void pressKey(int key, int xx, int yy) {

  switch (key) {
    case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
    case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
    case GLUT_KEY_UP : deltaMove = 0.5f; break;
    case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
  }
}

void releaseKey(int key, int x, int y) {

  switch (key) {
    case GLUT_KEY_LEFT :
    case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
    case GLUT_KEY_UP :
    case GLUT_KEY_DOWN : deltaMove = 0;break;
  }
}


void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 'q':
    case 27:             // ESCAPE key
      exit (0);
      break;
  }
}

int main(int argc, char **argv) {

  // init GLUT and create window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(640,640);
  glutCreateWindow("3D World");

  createMenu();

  // register callbacks
  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutIdleFunc(renderScene);

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(pressKey);

  // here are the new entries
  glutIgnoreKeyRepeat(1);
  glutSpecialUpFunc(releaseKey);

  // OpenGL init
  glEnable(GL_DEPTH_TEST);
  init();
  initPolyhedron();
  // enter GLUT event processing cycle
  glutMainLoop();

  return 1;
}
