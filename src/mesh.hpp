#ifndef CS488_MESH_HPP
#define CS488_MESH_HPP

#include <vector>
#include <iosfwd>
#include "primitive.hpp"
#include "algebra.hpp"
#include "scene.hpp"

// A polygonal mesh.
class Mesh : public Primitive {
public:
  Mesh(const std::vector<Point3D>& verts,
       const std::vector< std::vector<int> >& faces);

  typedef std::vector<int> Face;
  virtual Intersection* intersect(Ray& ray);
  
private:
  std::vector<Point3D> m_verts;
  std::vector<Face> m_faces;

  GeometryNode* m_bounding;

  friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh);
};

#endif
