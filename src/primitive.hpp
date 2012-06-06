#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"

const double EPS = 1e-8;

class Primitive {
public:
  virtual ~Primitive();
  virtual Intersection* intersect(Ray& ray);
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const Point3D& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual Intersection* intersect(Ray& ray);

private:
  Point3D m_pos;
  double m_radius;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const Point3D& pos, double size)
    : m_pos(pos), m_size(size)
  {
  }
  
  virtual ~NonhierBox();
  virtual Intersection* intersect(Ray& ray);
  bool inFaceBounds(Point3D& p, int d1, int d2);

private:
  Point3D m_pos;
  double m_size;
};

class Sphere : public NonhierSphere {
public:
  Sphere()
    : NonhierSphere(Point3D(0,0,0), 1)
  {
  }
  virtual ~Sphere();
};

class Cube : public NonhierBox {
public:
  Cube()
    : NonhierBox(Point3D(0,0,0), 1)
  {
  }
  virtual ~Cube();
};

#endif
