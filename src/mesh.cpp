#include "mesh.hpp"
#include "polyroots.hpp"
#include <iostream>

Mesh::Mesh(const std::vector<Point3D>& verts,
           const std::vector< std::vector<int> >& faces)
  : m_verts(verts),
    m_faces(faces)
{
  //bounding volume
  Point3D p = m_verts[0];
  double xmin = p[0], xmax = p[0];
  double ymin = p[1], ymax = p[1];
  double zmin = p[2], zmax = p[2];

  for(std::vector<Point3D>::const_iterator i = m_verts.begin(); i != m_verts.end(); i++){
    p = *i;
    if(p[0] < xmin)
      xmin = p[0];
    if(p[0] > xmax)
      xmax = p[0];

    if(p[1] < ymin)
      ymin = p[1];
    if(p[1] > ymax)
      ymax = p[1];

    if(p[2] < zmin)
      zmin = p[2];
    if(p[2] > zmax)
      zmax = p[2];
  }

  NonhierBox* box = new NonhierBox(Point3D(0,0,0), 1);
  m_bounding = new GeometryNode("boundingBox", box);
  m_bounding->translate(Vector3D(xmin-1, ymin-1, zmin-1));
  m_bounding->scale(Vector3D(xmax-xmin+1, ymax-ymin+1, zmax-zmin+1));

}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  std::cerr << "mesh({";
  for (std::vector<Point3D>::const_iterator I = mesh.m_verts.begin(); I != mesh.m_verts.end(); ++I) {
    if (I != mesh.m_verts.begin()) std::cerr << ",\n      ";
    std::cerr << *I;
  }
  std::cerr << "},\n\n     {";
  
  for (std::vector<Mesh::Face>::const_iterator I = mesh.m_faces.begin(); I != mesh.m_faces.end(); ++I) {
    if (I != mesh.m_faces.begin()) std::cerr << ",\n      ";
    std::cerr << "[";
    for (Mesh::Face::const_iterator J = I->begin(); J != I->end(); ++J) {
      if (J != I->begin()) std::cerr << ", ";
      std::cerr << *J;
    }
    std::cerr << "]";
  }
  std::cerr << "});" << std::endl;
  return out;
}

Intersection* Mesh::intersect(Ray& ray){
  //return m_bounding->intersect(ray);
  if(m_bounding->intersect(ray) == NULL)
    return NULL;

  Vector3D l = ray.getDir();
  Point3D o = ray.getPoint();

  double tmin = 9999999;
  Vector3D normal;
  bool hit = false;
  for(std::vector<Face>::const_iterator i = m_faces.begin(); i!=m_faces.end(); i++){
    Face face = *i;
    // get vertices for face
    Point3D p[face.size()];
    for(int j=0; j<face.size(); j++){
      p[j] = m_verts[face[j]];
    }

    // calculate the normal
    Vector3D n = (p[2] - p[1]).cross(p[0] - p[1]);

    // find the intersection with plane
    double A = 0;
    double B = l*n;
    double C = (o - p[0])*n;
    
    double roots[2];
    int size = quadraticRoots(A, B, C, roots);

    if(size <= 0)
      continue;

    double t = roots[0];
    Point3D x = o + t*l;

    // check if inside polygon
    bool inside = true;
		for (int i=0; i<face.size(); i++) {
			double d = (p[(i+1)%face.size()] - p[i]).cross(x - p[i])*n;
			if(d < 0) {
        inside = false;
        break;
			} 
    }

    if(!inside)
      continue;

    // calculate closest intersection
    if(t < tmin && t > EPS){
      tmin = t;
      normal = n;
      hit = true;
    }

  }

  if(hit)
    return new Intersection(o + tmin*l, tmin, normal);

  return NULL;
}
