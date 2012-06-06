#include "scene.hpp"
#include "a2.hpp"
#include <iostream>

SceneNode::SceneNode(const std::string& name)
  : m_name(name)
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::rotate(char axis, double angle)
{
  set_transform(get_transform()*rotation(toRadian(angle), axis));
}

void SceneNode::scale(const Vector3D& amount)
{
  set_transform(get_transform()*scaling(amount));
}

void SceneNode::translate(const Vector3D& amount)
{
  set_transform(get_transform()*translation(amount));
}

bool SceneNode::is_joint() const
{
  return false;
}

Intersection* SceneNode::intersect(Ray& ray) {
  Intersection* ret = NULL;
  // transform ray by inverse
  Ray newRay = ray;
  newRay.transform(m_invtrans);

  for(ChildList::const_iterator ci = m_children.begin(); ci != m_children.end(); ci++){
    Intersection* hit = (*ci)->intersect(newRay);
    if(hit != NULL)
      if(ret == NULL)
        ret = hit;
      else if(hit->getT() < ret->getT())
        ret = hit;
  }

  // transform intersection back
  if(ret!=NULL)
    ret->transform(m_trans, m_invtrans);
  return ret;
}

JointNode::JointNode(const std::string& name)
  : SceneNode(name)
{
  std::cerr << "joint" << std::endl;
}

JointNode::~JointNode()
{
}

bool JointNode::is_joint() const
{
  return true;
}

void JointNode::set_joint_x(double min, double init, double max)
{
  m_joint_x.min = min;
  m_joint_x.init = init;
  m_joint_x.max = max;
}

void JointNode::set_joint_y(double min, double init, double max)
{
  m_joint_y.min = min;
  m_joint_y.init = init;
  m_joint_y.max = max;
}

GeometryNode::GeometryNode(const std::string& name, Primitive* primitive)
  : SceneNode(name),
    m_primitive(primitive)
{
}

GeometryNode::~GeometryNode()
{
}
 
Intersection* GeometryNode::intersect(Ray& ray) {
  // transform ray by inverse
  Ray newRay = ray;
  newRay.transform(m_invtrans);

  Intersection* ret = m_primitive->intersect(newRay);
  if(ret!=NULL)
    ret->setMaterial(m_material);

  for(ChildList::const_iterator ci = m_children.begin(); ci != m_children.end(); ci++){
    Intersection* hit = (*ci)->intersect(newRay);
    if(hit != NULL)
      if(ret == NULL)
        ret = hit;
      else if(hit->getT() < ret->getT())
        ret = hit;
  }

  // transform intersection back
  if(ret!=NULL){
    ret->transform(m_trans, m_invtrans);
  }
  return ret;
}
