#include <GL/glut.h>  // (or others, depending on the system in use)

#include "Polyhedron.h"


Polyhedron::Polyhedron(string _fname, Vector3d _c, double _rotY, Vector3d _clr) : ObjLoader(_fname) {
  //cout << "Polyhedron constructor. " << endl;
  center = _c;
  rotY = _rotY;
  color = _clr;
}

Polyhedron::Polyhedron(const Polyhedron& other) {
  //cout << "Polyhedron copy constructor. " << endl;
  center = other.center;
  rotY = other.rotY;
  color = other.color;
  filename = other.filename;
  //////////////////////////////////////////////////////////
  //other data from obj loader

  verts = other.verts;
  vts = other.vts;
  vns = other.vns;
  faces = other.faces;
}

void Polyhedron::Recenter() {
  //TODO 
    
    Vector3d com(0, 0, 0);
    for (vector<Vector3d>::iterator vit = verts.begin(); vit != verts.end(); vit++) {
        com += *vit;
    }
    com /= verts.size();
    cout << "---------------------------------------------------" << endl;
    cout << "COM is: " << com << endl;
    cout << "---------------------------------------------------" << endl;
    for (vector<Vector3d>::iterator vit = verts.begin(); vit != verts.end(); vit++) {
        *vit -= com;
    }
    center.SetX(com.GetX());
    center.SetY(com.GetY());
    center.SetZ(com.GetZ());

}

void Polyhedron::RecenterXZ() {
  //TODO 

    center.SetX(0);
    center.SetZ(0);
}



void Polyhedron::Draw() {
  //TODO 
    glPushMatrix();

    glTranslated(center.GetX(), center.GetY(), center.GetZ());
    glRotated(rotY, 0, 1, 0);

    glColor3d(color.GetX(), color.GetY(), color.GetZ());
    for (int i = 0; i < faces.size(); i++) {
        Face& f = faces[i];

        //Vector3d n = ComputeNormal(f)

        glBegin(GL_TRIANGLES);
        for (int j = 0; j < f.ids.size(); j++) {
            Vector3d& v = verts[f.ids[j] - 1];
           // glNormal3d(n.GetX(), n.GetY(), n.GetZ());
            glVertex3d(v.GetX(), v.GetY(), v.GetZ());
        }
        glEnd();
    }

    glPopMatrix();
  //cout << "Polyhedron::Draw color = " << color << endl;
}
