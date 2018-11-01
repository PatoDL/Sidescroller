#include "app.h"
#include "raylib.h"
#include <cmath>

void prueba()
{
	InitWindow(900, 600, "xd");

	bool game = true;
	int radio = 40;
	Vector2 pos = { 900 / 2,600 / 2 };

	Rectangle rec;
	rec.width = 50;
	rec.height = 20;
	rec.x = pos.x;
	rec.y = pos.y;

	float angle;

	Vector2 v1;
	Vector2 v2;

	//------------------------
	static float prodVec;

	static float moduloV2;

	static float moduloV1;

	static float prodMod;
	//------------------------

	

	while (!WindowShouldClose())
	{
		v1.x = GetMouseX() - pos.x;
		v1.y = GetMouseY() - pos.y;

		v2.x = 0.0f;
		v2.y = -pos.y;

		prodVec = v2.x*v1.x + v2.y*v1.y;

		moduloV2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));

		moduloV1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));

		prodMod = moduloV2 * moduloV1;

		angle=acos(prodVec / (prodMod));

		angle *=  RAD2DEG;

		if (GetMouseX() < pos.x) {

			angle = 360 - angle;

		}


		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawCircleV(pos, radio, GREEN);
		DrawRectanglePro(rec, { 0.0f,rec.height / 2 }, angle-90, RED);
		EndDrawing();
	}

	CloseWindow();
}

int main()
{
	app::ExecuteGame();
	//prueba();
	return 0;
}