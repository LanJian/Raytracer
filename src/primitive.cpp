#include "primitive.hpp"
#include "polyroots.hpp"

Primitive::~Primitive()
{
}

Intersection* Primitive::intersect(Ray& ray) {
  return NULL;
}

Sphere::~Sphere()
{
}

Cube::~Cube()
{
}

NonhierSphere::~NonhierSphere()
{
}

Intersection* NonhierSphere::intersect(Ray& ray) {
  Vector3D l = ray.getDir();
  Point3D p = ray.getPoint();
  Vector3D e(p[0], p[1], p[2]);
  Vector3D c(m_pos[0], m_pos[1], m_pos[2]);
  double r = m_radius;
  
  double A = l*l;
  double B = 2*l*e - 2*l*c;
  double C = e*e + c*c - 2*e*c - r*r;

	double roots[2];
	int size = quadraticRoots(A, B, C, roots);

  if(size <= 0)
    return NULL;

  double t;
  if(size == 1)
    if(roots[0] > EPS)
      t = roots[0];
    else
      return NULL;
  else{
    t = roots[0] <  roots[1] ? roots[0] : roots[1];
    if(t < EPS)
      return NULL;
  }

  Point3D i = p + t*l;
  return new Intersection(i, t, i-m_pos);
}

NonhierBox::~NonhierBox()
{
}

Intersection* NonhierBox::intersect(Ray& ray) {
  Vector3D l = ray.getDir();
  Point3D o = ray.getPoint();

  double tmin = 99999999;
  bool hit = false;
  Vector3D normal;

  Vector3D ns[] = {Vector3D(-1,0,0), Vector3D(1,0,0), Vector3D(0,-1,0), 
    Vector3D(0,1,0), Vector3D(0,0,-1), Vector3D(0,0,1)};
  Vector3D ps[] = {Vector3D(0,0,0), Vector3D(m_size,0,0), Vector3D(0,0,0), 
    Vector3D(0,m_size,0), Vector3D(0,0,0), Vector3D(0,0,m_size)};
  for(int i=0; i<6; i++){
    Vector3D n = ns[i];
    Point3D p = m_pos + ps[i];
    double A = 0;
    double B = l*n;
    double C = (o - p)*n;
    
    double roots[2];
    int size = quadraticRoots(A, B, C, roots);

    if(size <= 0)
      continue;

    double t = roots[0];
    Point3D x = o + t*l;

    if(n[0] != 0 && !inFaceBounds(x, 1, 2))
      continue;
    if(n[1] != 0 && !inFaceBounds(x, 0, 2))
      continue;
    if(n[2] != 0 && !inFaceBounds(x, 0, 1))
      continue;

    if(t < tmin && t > EPS){
      hit = true;
      tmin = t;
      normal = n;
    }
  }

  if(hit)
    return new Intersection(o+tmin*l, tmin, normal);

  return NULL;
}

bool NonhierBox::inFaceBounds(Point3D& p, int d1, int d2){
  return p[d1] >= m_pos[d1] && p[d1] <= m_pos[d1]+m_size &&
    p[d2] >= m_pos[d2] && p[d2] <= m_pos[d2]+m_size;
}
