#ifndef CS488_MATERIAL_HPP
#define CS488_MATERIAL_HPP

#include "algebra.hpp"

class Material {
public:
  virtual ~Material();
  virtual void apply_gl() const = 0;

  virtual Colour getColor() = 0;
  virtual Colour getDiffuse() = 0;
  virtual Colour getSpecular() = 0;
  virtual double getShininess() = 0;
  virtual double getReflectivity() = 0;

protected:
  Material()
  {
  }
};

class PhongMaterial : public Material {
public:
  PhongMaterial(const Colour& kd, const Colour& ks, double shininess, double reflectivity);
  virtual ~PhongMaterial();

  virtual Colour getColor(){return m_kd;}
  virtual Colour getDiffuse(){return m_kd;}
  virtual Colour getSpecular(){return m_ks;}
  virtual double getShininess(){return m_shininess;}
  virtual double getReflectivity(){return m_reflectivity;}

  virtual void apply_gl() const;

private:
  Colour m_kd;
  Colour m_ks;

  double m_shininess;
  double m_reflectivity;
};


#endif
