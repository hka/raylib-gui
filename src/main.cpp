#include "raylib.h"
#include "screens.h"

#include <memory>
#include <stdio.h>
#include <string>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

constexpr const char* PROGRAM_NAME = "raylib-sample";

namespace
{
void UpdatePaintFrame();
void ChangeToScreen(Screen::AppScreen screen);
}

int main(void)
{
  InitWindow(options.screenWidth, options.screenHeight, PROGRAM_NAME);

  currentScreen = std::make_unique<MainScreen>();

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdatePaintFrame, 60, 1);
#else

  SetTargetFPS(options.fps);

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    UpdatePaintFrame();
  }
#endif
  CloseWindow();
  return 0;
}

namespace
{
void ChangeToScreen(Screen::AppScreen screen)
{
  if(screen == currentScreen->GetEnum())
  {
    return;
  }

  switch(screen)
  {
   case Screen::AppScreen::MAIN:
     currentScreen = std::make_unique<MainScreen>();
     break;
   case Screen::AppScreen::NOSCREEN:
     currentScreen = nullptr;
     break;
   default:
     break;
  }
}

void UpdatePaintFrame(void)
{
  currentScreen->Update();
  ChangeToScreen(currentScreen->Finish());

  if(currentScreen == nullptr){ return; }

  BeginDrawing();

  ClearBackground(RAYWHITE);

  currentScreen->Paint();

  EndDrawing();

}
} //anonymous namespace
