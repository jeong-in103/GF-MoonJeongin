#ifndef __GameObject__
#define __GameObject__

#include <string>
#include "LoaderParams.h"
#include "SDL.h"

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