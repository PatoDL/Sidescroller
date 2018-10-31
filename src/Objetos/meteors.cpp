#include "meteors.h"

#include <cmath>

#include "spaceship.h"
#include "game.h"
#include "app.h"

using namespace app;
using namespace game;
using namespace spaceship;

namespace app
{
	namespace meteors
	{
		static const int maxBigMeteors = 6;
		

		static Meteor bigMeteor[maxBigMeteors];

		static Meteor floorMeteors[maxBigMeteors];
	
		static int destroyedMeteorsCount;
		static float meteorSpeed;
		static const float speedBoost = 100.0f; //variable para que la velocidad se ajuste al GetFrameTime
		static int initialCorrection = 150;//para que los meteoros no tomen la posicion de la nave en el inicio
		static float posx, posy;
		static float velx, vely;
		static bool correctRange;

		//Imagenes y texturas
		static Image meteorImage;
		static Texture2D meteorTexture;

		//Numeros magicos para escalar las textura
		static float bigMeteorScale;
		static Vector2 bigMeteorScalePos;

		//Sonidos 
		static Sound explosionSound;
		bool pauseSoundExplosion=false;

		static bool init;
		static int scaleAux = 1600;
		static void initFloorMeteors();
		static void updateFloorMeteors();
		static const float floorMeteorsDistance = 400.0f;

		void initFloorMeteors()
		{
			floorMeteors[0].position = { (float)GetScreenWidth() / 6 * 4, (float)GetScreenHeight() / 6 * 5 };
			for (int i = 0; i < maxBigMeteors; i++)
			{
				floorMeteors[i].active = true;
				floorMeteors[i].radius = 50.0f;
				floorMeteors[i].color = RED;
				floorMeteors[i].speed = { 100.0f,0.0f };
				if (i != 0)
				{
					floorMeteors[i].position = { floorMeteors[i-1].position.x + floorMeteorsDistance,(float)GetScreenHeight() / 6 * 5 };
				}
				floorMeteors[i].tag = i;
			}
			
		}

		static int lastMeteorX;

		static void checkFloorMeteorsCol()
		{
			for (int i = 0; i < shipMaxBombs; i++)
			{
				for (int j = 0; j < maxBigMeteors; j++)
				{
					if (CheckCollisionCircles(bombs[i].position, bombs[i].radius, floorMeteors[j].position, floorMeteors[j].radius))
					{
						floorMeteors[j].active = false;
						bombs[i].active = false;
					}
				}
			}
		}

		static void checkLastMeteor()
		{
			lastMeteorX = 0;
			for (int k = 0; k < maxBigMeteors; k++)
			{
				if (floorMeteors[k].position.x > lastMeteorX)
				{
					lastMeteorX = floorMeteors[k].position.x;
				}
			}
		}

		void updateFloorMeteors()
		{
			for (int i = 0; i < maxBigMeteors; i++)
			{
				if (floorMeteors[i].active)
				{
					floorMeteors[i].position.x -= floorMeteors[i].speed.x*GetFrameTime();
					if (floorMeteors[i].position.x < -floorMeteors[i].radius * 2)
					{
						checkLastMeteor();
						floorMeteors[i].position.x = lastMeteorX + floorMeteorsDistance;
					}
				}
			}
			checkFloorMeteorsCol();
		}

		void InitMeteors()
		{
			explosionSound = LoadSound("res/assets/explosion.wav");
			meteorImage = LoadImage("res/assets/asteroide.png");
	
			meteorTexture = LoadTextureFromImage(meteorImage);

			correctRange = false;
			init = false;

			destroyedMeteorsCount = 0;
			meteorSpeed = 2;

			for (int i = 0; i < maxBigMeteors; i++)
			{
				posx = GetRandomValue(GetScreenWidth()-bigMeteor[i].radius,GetScreenWidth()-500);

				posy = GetRandomValue(0+ bigMeteor[i].radius*2, GetScreenHeight()- bigMeteor[i].radius*2);

				bigMeteor[i].position = { posx, posy };

				velx = GetRandomValue(-meteorSpeed, -meteorSpeed-1);
				vely = GetRandomValue(-meteorSpeed, meteorSpeed);

				while (!correctRange)
				{
					if (velx == 0 && vely == 0)
					{
						velx = -meteorSpeed;
						vely = GetRandomValue(-meteorSpeed, meteorSpeed);
					}
					else correctRange = true;
				}

				bigMeteor[i].speed = { velx, vely };
				bigMeteor[i].radius = (50 * GetScreenWidth()) / scaleAux;
				bigMeteor[i].active = true;
				bigMeteor[i].color = BLUE;
			}

			bigMeteorScale = (GetScreenWidth()* 0.25f) / scaleAux;
			bigMeteorScalePos = { (bigMeteorScale*meteorImage.width) / 2 ,(bigMeteorScale*meteorImage.height) / 2 };
			initFloorMeteors();
		}

		void UpdateMeteors()
		{
			if (!gameOver)
			{
				for (int a = 0; a < maxBigMeteors; a++)
				{
					if (CheckCollisionCircles({ ship.collider.x, ship.collider.y }, ship.collider.z, bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active)
					{
						gameOver = true;
						victory = false;
						currentScreen = GameOver;
					}
				}

				// Meteors logic: big meteors
				for (int i = 0; i < maxBigMeteors; i++)
				{
					if (bigMeteor[i].active)
					{
						// Movement
						bigMeteor[i].position.x += bigMeteor[i].speed.x*GetFrameTime() * speedBoost;
						bigMeteor[i].position.y += bigMeteor[i].speed.y*GetFrameTime() * speedBoost;

						// Collision logic: meteor vs wall
						if (bigMeteor[i].position.x > GetScreenWidth() + bigMeteor[i].radius)
						{
							bigMeteor[i].position.x = -(bigMeteor[i].radius);
						}
						else if (bigMeteor[i].position.x < 0 - bigMeteor[i].radius)
						{
							bigMeteor[i].position.x = GetScreenWidth() + bigMeteor[i].radius;
							bigMeteor[i].position.y= GetRandomValue(bigMeteor[i].radius, GetScreenHeight());
						}
						if (bigMeteor[i].position.y > GetScreenHeight() - bigMeteor[i].radius)
						{
							bigMeteor[i].speed.y *= -1;
						}
						else if (bigMeteor[i].position.y < 0 + bigMeteor[i].radius)
						{
							bigMeteor[i].speed.y *= -1;
						}
					}
				}

				// Collision logic: player-shoots vs meteors
				for (int i = 0; i < shipMaxShoots; i++)
				{
					if ((shoot[i].active))
					{
						for (int a = 0; a < maxBigMeteors; a++)
						{
							if (bigMeteor[a].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, bigMeteor[a].position, bigMeteor[a].radius))
							{
								if (!pauseSoundExplosion)
								{
									PlaySound(explosionSound);
								}
								else
								{
									PauseSound(explosionSound);
								}
								shoot[i].active = false;
								bigMeteor[a].active = false;
								destroyedMeteorsCount++;
								a = maxBigMeteors;
							}
						}

						
					}
				}
			}

			if (destroyedMeteorsCount == maxBigMeteors)
			{
				victory = true;
				gameOver = true;
				currentScreen = GameOver;
			}

			updateFloorMeteors();
		}

		void DrawMeteors()
		{
			for (int i = 0; i < maxBigMeteors; i++)
			{
				if (bigMeteor[i].active)
				{
					DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, DARKGRAY);
					DrawTextureEx(meteorTexture, { bigMeteor[i].position.x - bigMeteorScalePos.x,bigMeteor[i].position.y - bigMeteorScalePos.y }, 0, bigMeteorScale, WHITE);
				}
				else DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, BLANK);

				if (floorMeteors[i].active)
				{
					DrawCircleV(floorMeteors[i].position, floorMeteors[i].radius, floorMeteors[i].color);
				}
			}
		}

		void UnloadMeteors()
		{
			UnloadSound(explosionSound);
			UnloadTexture(meteorTexture);
			UnloadImage(meteorImage);
		}

		void ResetMeteors()
		{
			correctRange = false;
			init = false;

			destroyedMeteorsCount = 0;
			meteorSpeed = 2;

			for (int i = 0; i < maxBigMeteors; i++)
			{
				posx = GetRandomValue(GetScreenWidth() - bigMeteor[i].radius, GetScreenWidth() - 500);

				posy = GetRandomValue(0 + bigMeteor[i].radius * 2, GetScreenHeight() - bigMeteor[i].radius * 2);

				bigMeteor[i].position = { posx, posy };

				velx = GetRandomValue(-meteorSpeed, -meteorSpeed - 1);
				vely = GetRandomValue(-meteorSpeed, meteorSpeed);

				while (!correctRange)
				{
					if (velx == 0 && vely == 0)
					{
						velx = -meteorSpeed;
						vely = GetRandomValue(-meteorSpeed, meteorSpeed);
					}
					else correctRange = true;
				}

				bigMeteor[i].speed = { velx, vely };
				bigMeteor[i].radius = (50 * GetScreenWidth()) / scaleAux;
				bigMeteor[i].active = true;
				bigMeteor[i].color = BLUE;
			}

			bigMeteorScale = (GetScreenWidth()* 0.25f) / scaleAux;
			bigMeteorScalePos = { (bigMeteorScale*meteorImage.width) / 2 ,(bigMeteorScale*meteorImage.height) / 2 };
			initFloorMeteors();
		}
	}
}