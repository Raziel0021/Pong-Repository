#include "Menu.h"

#include <raylib.h>

#include "Game\GamePlay.h"
#include "Credits.h"
#include "Game/GameController.h"
using namespace game;
namespace game {
	namespace Menu
	{
		static const int FONT_SIZE_TITLE = 100;
		static const int FONT_SIZE_OPTIONS = 50;
		static const int FONT_SIZE_VERSION = FONT_SIZE_OPTIONS / 2;
		static const int DIVIDER_MEASURE_TEXT = 2;
		static const int GAMETITLE_LINE_DIVIDER = 6;
		static const int OPTIONS_LINE_DIVIDER = 3;
		static const float VERSION_LINE_DIVIDER = 1.7;
		bool menu;
		void showMenu()
		{
			DrawText(FormatText("PONG "), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("PONG", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / GAMETITLE_LINE_DIVIDER, FONT_SIZE_TITLE, DARKPURPLE);
			DrawText(FormatText("1.Player"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("1.Player", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / OPTIONS_LINE_DIVIDER, FONT_SIZE_OPTIONS, DARKGRAY);
			DrawText(FormatText("2.Players"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("2.Players", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / OPTIONS_LINE_DIVIDER + FONT_SIZE_OPTIONS, FONT_SIZE_OPTIONS, DARKGRAY);
			DrawText(FormatText("3.Credits"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("3.Credits", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / OPTIONS_LINE_DIVIDER + (FONT_SIZE_OPTIONS*2), FONT_SIZE_OPTIONS, DARKGRAY);
			DrawText(FormatText("Press Esc to Exit"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Press Esc to exit", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / OPTIONS_LINE_DIVIDER + (FONT_SIZE_OPTIONS * 3), FONT_SIZE_OPTIONS, DARKGRAY);
			DrawText(FormatText("Version 1.0"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Version 1.0", FONT_SIZE_VERSION) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / VERSION_LINE_DIVIDER + FONT_SIZE_OPTIONS, FONT_SIZE_VERSION, DARKGRAY);
			UpdateMenu();
		}
		void UpdateMenu()
		{
			if (IsKeyPressed(KEY_ONE))
			{
				menu = false;
				GamePlay::machineON = true;
			}
			if (IsKeyPressed(KEY_TWO))
				menu = false;
			if (IsKeyPressed(KEY_THREE))
			{
				menu = false;
				Credits::credits = true;
			}
			if (IsKeyPressed(KEY_ESCAPE))
				gameController::UnloadGame();
				//CloseWindow();
		}
	}
}