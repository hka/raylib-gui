#include "screens.h"

//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------
std::unique_ptr<Screen> currentScreen;
AppOptions options;

//------------------------------------------------------------------------------

Screen::~Screen(){}
