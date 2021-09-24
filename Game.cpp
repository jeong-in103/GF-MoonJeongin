#include "Game.h"
#include "SDL_image.h"
#include <iostream>

//키보드 입력 추가

bool Game::init(const char *title, int xpos, int ypos, int width, int height, int flags)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    return false;
  }

  m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
  if(m_pWindow == 0)
  {
    return false;
  }

  m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
  if(m_pRenderer == 0)
  {
    return false;
  }

  SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);

  SDL_Surface* pTempSurface = IMG_Load("Assets/pngwing.com.png");
  if(pTempSurface == 0)
  {
    return false;
  }

  m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

  SDL_FreeSurface(pTempSurface);

  SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
  

  std::cout << "w : " << m_sourceRectangle.w << "\n" << "h : " << m_sourceRectangle.h << std::endl;

  m_sourceRectangle.w = 230;
  m_sourceRectangle.h = 320;

  m_sourceRectangle.x = 0;
  m_sourceRectangle.y = 0;

  m_destinationRectangle.w = m_sourceRectangle.w;
  m_destinationRectangle.h = m_sourceRectangle.h;

  m_destinationRectangle.x = 0;
  m_destinationRectangle.y = 0;

  m_bRunning = true;

  return true;
}

void Game::update()
{
  m_sourceRectangle.x = 256 * ((SDL_GetTicks() / 100) % 4);
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);
  SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
  //SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, 0, SDL_FLIP_HORIZONTAL);
  SDL_RenderPresent(m_pRenderer);
}

bool Game::running()
{
  return m_bRunning;
}

void Game::handleEvents()
{
  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT :
        m_bRunning = false;
        break;
      case SDL_KEYDOWN :
        if(event.key.keysym.sym == SDLK_ESCAPE)
        {
          m_bRunning = false;
        }
        else if(event.key.keysym.sym == SDLK_LEFT)
        {
          m_destinationRectangle.x -= 10;
        }
        else if(event.key.keysym.sym == SDLK_RIGHT)
        {
          m_destinationRectangle.x += 10;
        }

      default:
        break;
    }
  }
}

void Game::clean()
{
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}