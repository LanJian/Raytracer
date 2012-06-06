#include "material.hpp"

Material::~Material()
{
}

PhongMaterial::PhongMaterial(const Colour& kd, const Colour& ks, double shininess, double reflectivity)
  : m_kd(kd), m_ks(ks), m_shininess(shininess), m_reflectivity(reflectivity)
{
}

PhongMaterial::~PhongMaterial()
{
}

void PhongMaterial::apply_gl() const
{
  // Perform OpenGL calls necessary to set up this material.
}
