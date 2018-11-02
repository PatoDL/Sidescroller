#include "game.h"

#include <raylib.h>

#include "meteors.h"
#include "spaceship.h"
#include "app.h"

using namespace app;
using namespace	spaceship;
using namespace	meteors;

namespace app
{
	namespace game
	{
		extern bool victory = false;
		extern bool gameOver = false;
		static char text[] = "W A S D : movimiento, CLICK IZQ: Disparar";
		static int sizeText;
		static float textPositionX;
		static float textPositionY;

		//Imagenes y texturas

		static Image backImage;
		static Texture2D backTexture;
		static Image backImage2;
		static Texture2D backTexture2;

		static Rectangle frameRec;
		static float currentFrame;

		static float framesCounter;
		static float framesSpeed;

		static Rectangle frameRec2;
		static float currentFrame2;

		static float framesCounter2;
		static float framesSpeed2;

		//Boton pausa

		static Rectangle botonPausa1;
		static Rectangle botonPausa2;
		static Color colorRect;
		static Vector2 mousePoint;

		//Puntaje 

		int score;
		

		static bool init;

		void InitValues()
		{
			sizeText = (GetScreenWidth() * 22) / 1600;
			textPositionX = GetScreenWidth()*0.01f;
			textPositionY = GetScreenHeight() * 0.97f;

			backImage = LoadImage("res/assets/parallax.png");
			backImage2 = LoadImage("res/assets/parallax2.png");

			//init boton pausa
			botonPausa1.x = GetScreenWidth()*0.96f;
			botonPausa1.y = GetScreenHeight()*0.02f;
			botonPausa1.height = (GetScreenWidth() * 40) / 1600;
			botonPausa1.width = (GetScreenWidth() * 15) / 1600;
			botonPausa2.x = GetScreenWidth()*0.975f;
			botonPausa2.y = GetScreenHeight()*0.02f;
			botonPausa2.height = (GetScreenWidth() * 40) / 1600;
			botonPausa2.width = (GetScreenWidth() * 15) / 1600;
			colorRect = GRAY;

			backTexture = LoadTextureFromImage(backImage);
			backTexture2 = LoadTextureFromImage(backImage2);

			frameRec = { 0.0f, 0.0f, (float)backTexture.width, (float)backTexture.height };
			currentFrame = 0;

			framesCounter = 0;
			framesSpeed = 0.001f;

			frameRec2 = { 0.0f, 0.0f, (float)backTexture2.width, (float)backTexture2.height };
			currentFrame2 = 0;

			framesCounter2 = 0;
			framesSpeed2 = 0.001f;

			score = 0;
			
			InitSpaceship();
			InitMeteors();
		}
		

		static void Input()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, botonPausa1))
			{
				colorRect.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					currentScreen = Pause;
				}
			}
			else colorRect.a = 255;

			if (CheckCollisionPointRec(mousePoint, botonPausa2))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					currentScreen = Pause;
				}
			}

		}

		

		static void Update()
		{
			framesCounter+=GetFrameTime();

			if (framesCounter >= framesSpeed)
			{
				framesCounter = 0;
				currentFrame+=0.1;

				if (currentFrame > 1594) currentFrame = 0;

				frameRec.x = (float)currentFrame;
			}
			framesCounter2+=GetFrameTime();

			if (framesCounter2 >= framesSpeed2)
			{
				framesCounter2 = 0;
				currentFrame2 += 1;

				if (currentFrame2 > 1280) currentFrame2 = 0;

				frameRec2.x = (float)currentFrame2;
			}

			UpdateSpaceship();
			UpdateMeteors();
		}

		void UpdateFrame()
		{
			Input();
			Update();
		}

		void DrawGameplay()
		{
			ClearBackground(BLANK);
			DrawTextureRec(backTexture, frameRec, { 0,0 }, WHITE);
			DrawMeteors();
			DrawTextureRec(backTexture2, frameRec2, { 0,0 }, WHITE);

			DrawSpaceship();

			DrawRectangleRec(botonPausa1, colorRect);
			DrawRectangleRec(botonPausa2, colorRect);
			DrawText(text, textPositionX, textPositionY, sizeText, PURPLE);
		}

		void ResetValues()
		{
			sizeText = (GetScreenWidth() * 20) / 1600;
			textPositionX = GetScreenWidth()*0.01f;
			textPositionY = GetScreenHeight() * 0.97f;

			//init boton pausa
			botonPausa1.x = GetScreenWidth()*0.96f;
			botonPausa1.y = GetScreenHeight()*0.02f;
			botonPausa1.height = (GetScreenWidth() * 40) / 1600;
			botonPausa1.width = (GetScreenWidth() * 15) / 1600;
			botonPausa2.x = GetScreenWidth()*0.975f;
			botonPausa2.y = GetScreenHeight()*0.02f;
			botonPausa2.height = (GetScreenWidth() * 40) / 1600;
			botonPausa2.width = (GetScreenWidth() * 15) / 1600;
			colorRect = GRAY;

			frameRec = { 0.0f, 0.0f, (float)backTexture.width, (float)backTexture.height };
			currentFrame = 0;

			framesCounter = 0;
			framesSpeed = 0.001f;

			frameRec2 = { 0.0f, 0.0f, (float)backTexture2.width, (float)backTexture2.height };
			currentFrame2 = 0;

			framesCounter2 = 0;
			framesSpeed2 = 0.001f;

			score = 0;

			ResetSpaceship();
			ResetMeteors();
			gameOver = false;
		}

		void UnloadGameplay()
		{
			UnloadMeteors();
			UnloadSpaceship();
			UnloadTexture(backTexture);
			UnloadTexture(backTexture2);
			UnloadImage(backImage);
			UnloadImage(backImage2);
		}
	}
}