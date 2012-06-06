#include "a4.hpp"
#include "a2.hpp"
#include "image.hpp"

void a4_render(// What to render
               SceneNode* root,
               // Where to output the image
               const std::string& filename,
               // Image size
               int width, int height,
               // Viewing parameters
               const Point3D& eye, const Vector3D& view,
               const Vector3D& up, double fov,
               // Lighting parameters
               const Colour& ambient,
               const std::list<Light*>& lights,
               double fogDist
               )
{
  // Fill in raytracing code here.

  std::cerr << "Stub: a4_render(" << root << ",\n     "
            << filename << ", " << width << ", " << height << ",\n     "
            << eye << ", " << view << ", " << up << ", " << fov << ",\n     "
            << ambient << ",\n     {";

  for (std::list<Light*>::const_iterator I = lights.begin(); I != lights.end(); ++I) {
    if (I != lights.begin()) std::cerr << ", ";
    std::cerr << **I;
  }
  std::cerr << "});" << std::endl;

  Vector3D viewVector = view;
  Vector3D upVector = up;
  Vector3D sideVector = viewVector.cross(upVector);
  viewVector.normalize();
  upVector.normalize();
  sideVector.normalize();
  
  Image img(width, height, 3);

  int progress = 0;
  int numPixels = width*height;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int newProgress = (int)((double)(y*width + x)/numPixels*100);
      if(newProgress >= progress+5){
        progress = newProgress;
        std::cerr << progress << std::endl;
      }

      double d = height/2.0/tan(toRadian(fov)/2);
      Vector3D dir = (x-(width/2.0))*sideVector + 
          ((height/2.0)-y)*upVector + d*viewVector;
      dir.normalize();
      Ray ray = Ray(eye, dir);

      bool fogOn = true;
      if(fogDist <= 0)
        fogOn = false;
      Colour* color = rayTrace(ambient, eye, ray, root, lights, 5, fogDist);
      Colour fog(1,1,1);
      if(color == NULL) {
        // sunset colours
        Colour horizon(0.94, 0.55, 0.05);
        Colour zenith(0.2, 0.27, 0.4);
        Colour bg = zenith*(1-(double)y/height) + horizon*((double)y/height);
        if(fogOn)
          color = new Colour(0.8,0.8,0.8);
        else
          color = new Colour(bg);
      }

      img(x, y, 0) = color->R();
      img(x, y, 1) = color->G();
      img(x, y, 2) = color->B();
    }
  }
  img.savePng(filename);
  
}

Colour* rayTrace(const Colour& ambient, const Point3D& eye, Ray ray, SceneNode* root,
    const std::list<Light*>& lights, int level, double fogDist){
  if(level <= 0)
    return NULL;

  Intersection* i = root->intersect(ray);
  bool fogOn = true;
  if(fogDist <= 0)
    fogOn = false;

  if(i != NULL){
    Colour color(0,0,0);
    Colour fog(0.8,0.8,0.8);
    Colour diffuse(0,0,0), specular(0,0,0);

    Material* material = i->getMaterial();
    Vector3D n = i->getNormal();
    n.normalize();
    Point3D p = i->getPoint();
    Vector3D v = eye - p;
    v.normalize();

    for (std::list<Light*>::const_iterator I = lights.begin(); I != lights.end(); ++I) {
      Light light = **I;

      Vector3D l = light.position - p;
      l.normalize();
      Vector3D r = 2*l*n*n - l;
      r.normalize();

      // shadows
      Ray lightRay = Ray(p, l);
      Intersection* lightIsc = root->intersect(lightRay);
      if(lightIsc == NULL){
        // add light contribution
        //std::cerr << "light" << std::endl;
        if(n*l > 0)
          diffuse = diffuse + material->getDiffuse() * (l*n) * light.colour;
        if(r*v > 0)
          specular = specular + material->getSpecular() * pow((r*v), material->getShininess()) * light.colour;
      }

    }


    //secondaty rays
    Vector3D r = 2*v*n*n - v;
    r.normalize();
    Ray refRay(p, r);
    Colour* reflectedColor = rayTrace(ambient, eye, refRay, root, lights, level-1, fogDist);

    if(reflectedColor != NULL){
      if(n*r > 0)
        diffuse = diffuse + material->getDiffuse() * (r*n) * material->getReflectivity() * (*reflectedColor);
      if(r*v > 0)
        specular = specular + material->getSpecular() * pow((r*v), material->getShininess()) * material->getReflectivity() * (*reflectedColor);
    }

    color = ambient*material->getColor() + diffuse + specular;
    if(fogOn){
      double dist = i->getT()/fogDist;
      if(dist>1)
        dist=1;
      color = (1-dist)*color + dist*fog;
    }

    return new Colour(color);
  }  

  return NULL;
}

