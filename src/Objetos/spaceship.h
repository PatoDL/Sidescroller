#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <raylib.h>

namespace app
{
	namespace spaceship
	{
		void InitSpaceship();
		void UpdateSpaceship();
		void DrawSpaceship();
		void UnloadSpaceship();
		void ResetSpaceship();

		struct Spaceship
		{
			Vector2 position;
			Vector2 speed;
			Vector2 acceleration;
			float rotation;
			Vector3 collider;
			Color color;
		};

		struct Shoot
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			float rotation;
			bool active;
			Color color;
		};
		
		struct Bomb
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			float rotation;
			bool active;
			Color color;
			int tag;
		};

		extern Bomb bombs[];
		extern Spaceship ship;
		extern const int shipMaxShoots;
		extern const int shipMaxBombs;
		extern Shoot shoot[];
		extern bool pauseSoundShoot;
	}
}
#endif // !SPACESHIP_H
