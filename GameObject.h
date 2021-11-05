#ifndef __GameObject__
#define __GameObject__

#include "LoaderParams.h"

class GameObject
{
public :
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void clean() = 0;

  virtual ~GameObject() {}

protected :
  GameObject(const LoaderParams* pRarams) {}
};

#endif