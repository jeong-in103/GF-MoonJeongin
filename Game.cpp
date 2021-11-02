#include "Game.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

Game* Game::s_pInstance = 0;

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

  // 오브젝트 텍스쳐
  if(!TheTextureManager::Instance()->load("Assets/animate-alpha.png", "animate", m_pRenderer))
  {
    return false;
  }

  m_gameObjects.push_back(new Player(new LoaderParams(200, 200, 128, 82, "animate")));
  m_gameObjects.push_back(new Enemy(new LoaderParams(100, 100, 128, 82, "animate")));

  m_bRunning = true;

  return true;
}

void Game::update()
{
  for(int i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->update();
  }
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);

  for(int i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->draw();
  }

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