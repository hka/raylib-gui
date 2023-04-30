#ifndef APP_GUI
#define APP_GUI

#include "raylib.h"

#include <vector>

enum class MouseState {NO, OVER, CLICKED};
struct Button
{
  Rectangle   bounds;
  MouseState  state = MouseState::NO;
  int clickState = 0;
};

struct Section
{
  Rectangle bounds;

  std::vector<Button> buttons;
};

struct Divider
{
  bool leftRight;
  bool topBottom;
  std::vector<size_t> ix0;
  std::vector<size_t> ix1;
  float dividerWidth;
  float minWidth;
  bool tracking = false;
};

struct Layer
{
  Rectangle bounds;
  bool active = false;

  std::vector<Section> sections;
  std::vector<Divider> dividers;
};

void PaintLayer(const Layer& layer);
void PaintSection(const Section& section, const Rectangle& bounds);
void PaintDivider(const Divider& divider,
                  const std::vector<Section>& sections,
                  const Rectangle& bounds);

void UpdateLayer(Layer& layer);
void UpdateDivider(Divider& divider,
                   std::vector<Section>& sections,
                   Rectangle& bounds);
void UpdateSection(Section& section, const Rectangle& bounds);

void PaintButton(const Button& button, const std::vector<Rectangle>& bounds);
bool CheckButton(const Vector2& p, Button& button, const std::vector<Rectangle>& bounds);

#endif
