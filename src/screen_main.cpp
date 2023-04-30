#include "screens.h"

#include "gui.h"

MainScreen::MainScreen()
{
  m_finishScreen = Screen::AppScreen::MAIN;

  Layer layer0;
  layer0.active = true;
  layer0.bounds = {0, 0, (float)options.screenWidth, (float)options.screenHeight};
  Section sectionLeftTop;
  sectionLeftTop.bounds = {0.f,0.f,0.5f,0.5f};
  Button b;
  b.bounds = {0.05,0.05,0.5,0.05};
  sectionLeftTop.buttons.push_back(b);
  layer0.sections.push_back(sectionLeftTop);

  Section sectionLeftBot;
  sectionLeftBot.bounds = {0.f,0.5f,0.5f,0.5f};
  layer0.sections.push_back(sectionLeftBot);

  Section sectionRight;
  sectionRight.bounds = {0.5f,0.f,0.5f,1.f};
  layer0.sections.push_back(sectionRight);

  layer0.dividers.push_back({true,false,{0,1},{2},0.004,2});
  layer0.dividers.push_back({false,true,{0},{1},0.004,2});

  m_layers.push_back(layer0);
}

MainScreen::~MainScreen()
{
}

void MainScreen::Update()
{
  Vector2 mousePoint = GetMousePosition();
  for(Layer& l : m_layers)
  {
    UpdateLayer(l);
  }
}

void MainScreen::Paint()
{
  DrawRectangle(0, 0, options.screenWidth, options.screenHeight, GREEN);
  for(const Layer& l : m_layers)
  {
    PaintLayer(l);
  }
}

Screen::AppScreen MainScreen::Finish()
{
  return m_finishScreen;
}
