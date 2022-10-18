#pragma once
#include "Actor.h"
#include "SDL_ttf.h"
#include "MyEngine.h"
#include <string>

using namespace std;

class AText : public AActor
{
public:
    AText();
    AText(int NewX, int NewY, string NewContent, int NewFontSize);
    ~AText();

    virtual void Render() override;
    string Content;
    int FontSize;
    TTF_Font* Font;
};

