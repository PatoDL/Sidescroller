#ifndef METEORS_H
#define METEORS_H

#include <raylib.h>

namespace app
{
	namespace meteors
	{

		struct Meteor
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			bool active;
			Color color;
			int tag;
		};

		extern const int posMachinesY;

		void InitMeteors();
		void UpdateMeteors();
		void DrawMeteors();
		void UnloadMeteors();
		void ResetMeteors();

		extern bool pauseSoundExplosion;
	}
}
#endif // !METEORS_H
