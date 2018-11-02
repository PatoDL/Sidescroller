#include "credits.h"

#include <raylib.h>

#include "game.h"
#include "app.h"
#include "menu.h"

using namespace app;
using namespace game;
using namespace menu;

namespace app
{
	namespace credits
	{
		static char text1[] = "Usando libreria raylib";
		static char text2[] = "Musica realizada con Bosca Ceoil";
		static char text3[] = "Creado por Mariano Martinez";
		static char text4[] = "MENU";
		static char text5[] = "GRAD10S V 1.1";
		static char text6[] = "Sonidos realizados con Bfxr";
		static char text7[] = "Imagenes y assets:";
		static char text8[] = "-'[M13] Cave Tileset', Autor: Beast, https://opengameart.org/content/m13-cave-tileset";
		static char text9[] = "-'STARLINK BATTLE FOR ATLAS SPACESHIP SPACE BATTLE', sin autor, https://anoncraft.com/starlink-battle-for-atlas-spaceship-space-battle-21216/";
		static char text10[] = "-'Azul Rojo Galaxy Fantasía Espacio fondo de pantalla', sin autor, http://www.hdfondos.eu/preview/65932/1024/768";
		static char text11[] = "-Sin titulo, Tony Rivera, https://www.clarin.com/deportes/futbol-internacional/diego-maradona-despues-triunfo-dorados-vendo-humo-vendo-trabajo_0_vGCzhB6lP.html";
		static char text12[] = "-La nave, los asteroides y el disparo fueron creados con Adobe Illustrator y las imagenes modificadas con Adobe Photoshop";
		static int sizeText = 0;
		static int sizeText2 = 0;
		static int sizeText3 = 0;
		static int textPositionX = 0;
		static int textPositionY = 0;
		static int text2PositionX = 0;
		static int text2PositionY = 0;
		static int text3PositionX = 0;
		static int text3PositionY = 0;
		static int text4PositionX = 0;
		static int text4PositionY = 0;
		static int text5PositionX = 0;
		static int text5PositionY = 0;
		static int text6PositionX = 0;
		static int text6PositionY = 0;
		static int text7PositionX = 0;
		static int text7PositionY = 0;
		static int text8PositionX = 0;
		static int text8PositionY = 0;
		static int text9PositionX = 0;
		static int text9PositionY = 0;
		static int text10PositionX = 0;
		static int text10PositionY = 0;
		static int text11PositionX = 0;
		static int text11PositionY = 0;
		static int text12PositionX = 0;
		static int text12PositionY = 0;
		static int halfScreen = 0;

		static const int scaleAux1 = 800;
		static const int scaleAux2 = 1600;

		static Vector2 mousePoint;
		static Rectangle rect1;
		static Color colorRect1;

		void InitCredits()
		{
			sizeText = (GetScreenWidth() * 20) / scaleAux1;
			sizeText2 = (GetScreenWidth() * 15) / scaleAux1;
			sizeText3 = (GetScreenWidth() * 9.8f) / scaleAux1;
			halfScreen = GetScreenWidth() / 2;

			textPositionX = halfScreen - MeasureText(text1, sizeText) / 2;
			textPositionY = GetScreenHeight() * 0.13;
			text2PositionX = halfScreen - MeasureText(text2, sizeText) / 2;
			text2PositionY = GetScreenHeight() * 0.21;
			text6PositionX = halfScreen - MeasureText(text6, sizeText) / 2;
			text6PositionY = GetScreenHeight() * 0.29;
			text3PositionX = halfScreen - MeasureText(text3, sizeText) / 2;
			text3PositionY = GetScreenHeight() * 0.37;
			text4PositionX = halfScreen - MeasureText(text4, sizeText2) / 2;
			text4PositionY = GetScreenHeight() * 0.80;
			text5PositionX = halfScreen - MeasureText(text5, sizeText) / 2;
			text5PositionY = GetScreenHeight() * 0.05;
			text7PositionX= halfScreen - MeasureText(text7, sizeText) / 2;
			text7PositionY= GetScreenHeight() * 0.45;
			text8PositionX = halfScreen - MeasureText(text8, sizeText3) / 2;
			text8PositionY = GetScreenHeight() * 0.53;
			text9PositionX = halfScreen - MeasureText(text9, sizeText3) / 2;
			text9PositionY = GetScreenHeight() * 0.58;
			text10PositionX = halfScreen - MeasureText(text10, sizeText3) / 2;
			text10PositionY = GetScreenHeight() * 0.63;
			text11PositionX = GetScreenWidth() / 2 - MeasureText(text11, sizeText3) / 2;
			text11PositionY = GetScreenHeight() * 0.68;
			text12PositionX = halfScreen - MeasureText(text12, sizeText3) / 2;
			text12PositionY = GetScreenHeight() * 0.73;

			colorRect1 = PURPLE;

			rect1.height = (GetScreenWidth() * 80) / scaleAux2;
			rect1.width = (GetScreenWidth() * 170) / scaleAux2;
			rect1.x = halfScreen - rect1.width / 2;
			rect1.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.275;
		}

		void UpdateCredits()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, rect1))
			{
				colorRect1.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					currentScreen = Menu;
					InitMenu();
				}
			}
			else colorRect1.a = 255;
		}

		void DrawCredits()
		{
			ClearBackground(BLACK);
			DrawRectangleRec(rect1, colorRect1);
			DrawText(text1, textPositionX, textPositionY, sizeText, GRAY);
			DrawText(text2, text2PositionX, text2PositionY, sizeText, GRAY);
			DrawText(text3, text3PositionX, text3PositionY, sizeText, GRAY);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, BLACK);
			DrawText(text5, text5PositionX, text5PositionY, sizeText, GRAY);
			DrawText(text6, text6PositionX, text6PositionY, sizeText, GRAY);
			DrawText(text7, text7PositionX, text7PositionY, sizeText, GRAY);
			DrawText(text8, text8PositionX, text8PositionY, sizeText3, GRAY);
			DrawText(text9, text9PositionX, text9PositionY, sizeText3, GRAY);
			DrawText(text10, text10PositionX, text10PositionY, sizeText3, GRAY);
			DrawText(text11, text11PositionX, text11PositionY, sizeText3, GRAY);
			DrawText(text12, text12PositionX, text12PositionY, sizeText3, GRAY);
		}
	}
}