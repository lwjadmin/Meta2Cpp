#include "Player.h"
#include <iostream>
#include "MyEngine.h"

using namespace std;

APlayer::APlayer()
{
	Shape = 'P';
	ZOrder = 40;
	CollisionType = ECollisionType::CollisionEnable;
	MyColor = { 0, 255, 0, 0 };
	MyColorKey = { 255,0,255,0 };
	LoadBMP("Data/Player.bmp");
	RenderPosX = 0;
	RenderPosY = 3;
	ElapsedTime = 0;
	ExecuteTime = 250;
}

APlayer::APlayer(int NewX, int NewY)
	: APlayer()
{
	X = NewX;
	Y = NewY;
}

APlayer::~APlayer()
{
}

void APlayer::Tick()
{
	ElapsedTime += GEngine->GetWorldDeltaSeconds();
	if (ElapsedTime > ExecuteTime)
	{
		RenderPosX = (RenderPosX + 1) % 5;
		ElapsedTime = 0;
	}
	

	if (GEngine->MyEvent.type != SDL_KEYDOWN)
	{
		return;
	}

	switch (GEngine->MyEvent.key.keysym.sym)
	{
		case SDLK_w:
			RenderPosY = 2;
			
			Y--;
			if (!PredictCanMove())
			{
				Y++;
			}
			break;

		case SDLK_a:
			RenderPosY = 0;
			X--;
			if (!PredictCanMove())
			{
				X++;
			}
			break;

		case SDLK_s:
			RenderPosY = 3;
			Y++;
			if (!PredictCanMove())
			{
				Y--;
			}
			break;

		case SDLK_d:
			RenderPosY = 1;
			X++;
			if (!PredictCanMove())
			{
				X--;
			}
			break;

		case SDLK_ESCAPE:
			GEngine->QuitGame();

			break;
	}
}

bool APlayer::PredictCanMove()
{
	for (AActor* Actor : GEngine->GetAllActors())
	{
		if (X == Actor->X && Y == Actor->Y &&
			dynamic_cast<APlayer*>(Actor) == nullptr)
		{
			if (CheckHit(Actor))
			{
				return false;
			}
		}
	}
	return true;
}

void APlayer::Render()
{
	//2DEngineRender

	SDL_Rect MyRect = SDL_Rect({ X * TileSize, Y * TileSize, TileSize, TileSize });
	if (MyTexture == nullptr)
	{
		SDL_SetRenderDrawColor(GEngine->MyRenderer, MyColor.r, MyColor.g, MyColor.b, MyColor.a);
		SDL_RenderFillRect(GEngine->MyRenderer, &MyRect);
	}
	else
	{
		//움직임 만들어보기!

		int SpriteSizeX = MySurface->w / 5;
		int SpriteSizeY = MySurface->h / 5;

		int RectPosX = RenderPosX * SpriteSizeX;
		int RectPosY = RenderPosY * SpriteSizeY;

		/*-----------------------------
		W : [2,0] , [2,1] , [2,2] , [2,3] , [2,4]
		A : [0,0] , [0,1] , [0,2] , [0,3] , [0,4]
		S : [3,0] , [3,1] , [3,2] , [3,3] , [3,4]
		D : [1,0] , [1,1] , [1,2] , [1,3] , [1,4]
		-----------------------------*/

		SDL_Rect SourceRect = SDL_Rect({ RectPosX, RectPosY, SpriteSizeX, SpriteSizeY });

		SDL_RenderCopy(GEngine->MyRenderer, MyTexture, &SourceRect, &MyRect);
	}

}
