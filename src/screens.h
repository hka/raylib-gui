#ifndef APP_SCREENS_H
#define APP_SCREENS_H

#include "raylib.h"

#include <stdlib.h>
#include <string>
#include <memory>
#include <vector>

#include "gui.h"

struct AppOptions
{
  int screenWidth = 1280;
  int screenHeight = 720;
  int fps = 60;
};

class Screen
{
 public:
  enum class AppScreen { MAIN,
                         NOSCREEN };
  virtual ~Screen() = 0;
  virtual void Update() = 0;
  virtual void Paint() = 0;
  virtual AppScreen Finish() = 0;
  virtual AppScreen GetEnum() = 0;
};

class MainScreen : public Screen
{
 public:
  MainScreen();
  ~MainScreen();
  void Update();
  void Paint();
  AppScreen Finish();
  AppScreen GetEnum(){return Screen::AppScreen::MAIN;}
 private:
  AppScreen m_finishScreen;
  std::vector<Layer> m_layers;
};

// Globals
extern std::unique_ptr<Screen> currentScreen;
extern AppOptions options;
#endif
