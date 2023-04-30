#include "gui.h"

#include <cstring>
#include <algorithm>
#include <cstdio>

void PaintLayer(const Layer& layer)
{
  for(const Section& s : layer.sections)
  {
    PaintSection(s, layer.bounds);
  }
  for(const Divider& d : layer.dividers)
  {
    PaintDivider(d, layer.sections, layer.bounds);
  }
}
Rectangle RelToAbs(const Rectangle& relRec, const Rectangle& bounds)
{
  Rectangle rec;
  rec.x = bounds.width*relRec.x + bounds.x;
  rec.y = bounds.height*relRec.y + bounds.y;
  rec.width = bounds.width*relRec.width;
  rec.height = bounds.height*relRec.height;
  return rec;
}
void PaintSection(const Section& section, const Rectangle& bounds)
{
  Rectangle rec = RelToAbs(section.bounds, bounds);
  DrawRectangleRec(rec, GRAY);
  for(const Button& b : section.buttons)
  {
    PaintButton(b, {section.bounds, bounds});
  }
}

Rectangle GetDividerRec(const Divider& divider,
                        const std::vector<Section>& sections,
                        const Rectangle& bounds)
{
  float minY = 1.f;
  float totHeight = 0.f;
  float minX = 1.f;
  float totWidth = 0.f;
  for(size_t ii = 0; ii < divider.ix0.size();++ii)
  {
    minY = std::min(sections[divider.ix0[ii]].bounds.y, minY);
    totHeight += sections[divider.ix0[ii]].bounds.height;
    minX = std::min(sections[divider.ix0[ii]].bounds.x, minX);
    totWidth += sections[divider.ix0[ii]].bounds.width;
  }
  Rectangle rec;
  if(divider.leftRight)
  {
    rec.width = std::max(divider.minWidth, bounds.width*divider.dividerWidth);
    rec.height = totHeight*bounds.height;
    rec.y = minY*bounds.height + bounds.y;
    rec.x = sections[divider.ix1[0]].bounds.x*bounds.width + bounds.x - rec.width/2;
  }
  else if(divider.topBottom)
  {
    rec.width = totWidth*bounds.width;
    rec.height = std::max(divider.minWidth, bounds.width*divider.dividerWidth);
    rec.x = minX*bounds.width + bounds.x;
    rec.y = (sections[divider.ix1[0]].bounds.y)*bounds.height + bounds.y - rec.height/2;
  }
  return rec;
}

void PaintDivider(const Divider& divider,
                  const std::vector<Section>& sections,
                  const Rectangle& bounds)
{
  DrawRectangleRec(GetDividerRec(divider,sections, bounds), BLACK);
}

void UpdateLayer(Layer& layer)
{
  for(Divider& d : layer.dividers)
  {
    UpdateDivider(d, layer.sections, layer.bounds);
  }
  for(Section& s : layer.sections)
  {
    UpdateSection(s, layer.bounds);
  }
}
void UpdateSection(Section& section, const Rectangle& bounds)
{
  Vector2 mousePos = GetMousePosition();
  for(Button& b : section.buttons)
  {
    if(CheckButton(mousePos, b, {section.bounds, bounds}))
    {

    }
  }
}

void UpdateDivider(Divider& divider,
                   std::vector<Section>& sections,
                   Rectangle& bounds)
{
  Rectangle divRec = GetDividerRec(divider,sections, bounds);
  Vector2 mousePos = GetMousePosition();
  if(CheckCollisionPointRec(mousePos, divRec))
  {
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
      divider.tracking = true;
    }
  }
  if(divider.tracking)
  {
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
      if(divider.leftRight)
      {
        float relX = (mousePos.x - bounds.x)/bounds.width;
        for(size_t ii = 0; ii < divider.ix0.size(); ++ii)
        {
          sections[divider.ix0[ii]].bounds.width = relX - sections[divider.ix0[ii]].bounds.x;
        }
        for(size_t ii = 0; ii < divider.ix1.size(); ++ii)
        {
          sections[divider.ix1[ii]].bounds.width -= relX-sections[divider.ix1[ii]].bounds.x;
          sections[divider.ix1[ii]].bounds.x = relX;
        }
      }
      if(divider.topBottom)
      {
        float relY = (mousePos.y - bounds.y)/bounds.height;
        for(size_t ii = 0; ii < divider.ix0.size(); ++ii)
        {
          sections[divider.ix0[ii]].bounds.height = relY - sections[divider.ix0[ii]].bounds.y;
        }
        for(size_t ii = 0; ii < divider.ix1.size(); ++ii)
        {
          sections[divider.ix1[ii]].bounds.height -= relY-sections[divider.ix1[ii]].bounds.y;
          sections[divider.ix1[ii]].bounds.y = relY;
        }
      }
    }
    else
    {
      divider.tracking = false;
    }
  }
}

void PaintButton(const Button& button, const std::vector<Rectangle>& bounds)
{
  //Button
  Rectangle rec = button.bounds;
  for(size_t ii = 0; ii < bounds.size(); ++ii)
  {
    rec = RelToAbs(rec, bounds[ii]);
  }
  switch(button.state)
  {
   case MouseState::NO:
     DrawRectangleRec(rec, LIME);
     break;
   case MouseState::CLICKED:
     DrawRectangleRec(rec, GOLD);
     break;
   case MouseState::OVER:
     DrawRectangleRec(rec, DARKGRAY);
     break;
  }
 }

bool CheckButton(const Vector2& p, Button& button, const std::vector<Rectangle>& bounds)
{
  Rectangle rec = button.bounds;
  for(size_t ii = 0; ii < bounds.size(); ++ii)
  {
    rec = RelToAbs(rec, bounds[ii]);
  }
  if (CheckCollisionPointRec(p, rec))
  {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
      button.state = MouseState::CLICKED;
    }
    else
    {
      button.state = MouseState::OVER;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
      return true;
    }
  }
  else
  {
    button.state = MouseState::NO;
  }
  return false;
}
