#include <SDL.h>
#include <cstdlib>

SDL_Window* g_pWindow = 0; // 윈도우 관련 정보 저장
SDL_Renderer* g_pRenderer = 0; // 랜더링 상태를 포함하는 구조체
bool g_bRunning = false;

bool init(const char* title, int xpos, int ypos,
          int height, int width, int flags) //초기화
{
  if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
  {
    g_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);// 윈도우 관련 정보 생성

      if(g_pWindow != 0)
      {
        g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);// 랜더링 상태 생성
      }
  }
  else
  {
    return false;
  }

  return true;
}

void changeColor() // 렌더링 색을 랜덤으로 전환한다.
{
  SDL_SetRenderDrawColor(g_pRenderer, rand() % 255, rand() % 255, rand() % 255, 255);
  SDL_Delay(1000);
}

void render()
{
  SDL_RenderClear(g_pRenderer); // 지정한 색으로 rederer 지우기
  SDL_RenderPresent(g_pRenderer); // 백버퍼를 화면에 표시
}

int main(int argc, char* args[])
{
  if(init("partySDL",
          SDL_WINDOWPOS_CENTERED,
          SDL_WINDOWPOS_CENTERED,
          640, 480,
          SDL_WINDOW_SHOWN))
  {
    g_bRunning = true;
  }
  else
  {
    return 1; //something's wrong
  }

  while(g_bRunning)
  {
    // handle input - update - render
    changeColor();

    render();
  }

  SDL_Quit();

  return 0;
}