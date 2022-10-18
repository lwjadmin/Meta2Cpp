#include "Text.h"
#include <Windows.h>

AText::AText()
{
}

AText::AText(int NewX, int NewY, string NewContent, int NewFontSize)
{
    X = NewX;
    Y = NewY;
    Content = NewContent;
    FontSize = NewFontSize;
    Font = TTF_OpenFont("./Data/NGULIM.TTF", FontSize);

    wstring Unicode(Content.length(), 0);
    //CP949 to Unicode
    MultiByteToWideChar(CP_ACP, 0, Content.c_str(), (int)Content.length(),
        (LPWSTR)Unicode.c_str(), (int)Content.length() + 1);


    ZOrder = 100;
    MyColor = { 255,255,255,0 };
    //MySurface = TTF_RenderText_Solid(Font, Content.c_str(), MyColor);
    SDL_Color bgColor{ 255,255,0,0 };

    //MySurface = TTF_RenderUNICODE_Solid(Font, (Uint16*)Unicode.c_str(), MyColor);
    //MySurface = TTF_RenderUNICODE_Shaded(Font, (Uint16*)Unicode.c_str(), MyColor, bgColor);
    MySurface = TTF_RenderUNICODE_LCD(Font, (Uint16*)Unicode.c_str(), MyColor, bgColor);

    MyTexture = SDL_CreateTextureFromSurface(GEngine->MyRenderer, MySurface);
}


AText::~AText()
{
    TTF_CloseFont(Font);
}

void AText::Render()
{
    SDL_Rect RenderRect = { X,Y,MySurface->w, MySurface->h };
    SDL_RenderCopy(GEngine->MyRenderer, MyTexture, nullptr, &RenderRect);
}
