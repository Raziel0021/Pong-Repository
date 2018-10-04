#include "Credits.h"

#include <raylib.h>

#include "Game/GamePlay.h"
#include "Menu.h"

using namespace game;
namespace game {
	namespace Credits
	{
		static const int FONT_SIZE_TITLE = 50;
		static const int FONT_SIZE = 35;
		static const int FONT_SIZE_URL = 16;
		static const float FONT_SIZE_HELPER = FONT_SIZE/2;
		static const int GAMETITLE_LINE_DIVIDER = 10;
		static const int CREDITS_LINE_DIVIDER = 5;
		static const float HELPER_LINE_DIVIDER = 1.2;
		static const float VERSION_LINE_DIVIDER = 1.1;
		static const int LINE_DIVIDER = 4;
		static const int DIVIDER_MEASURE_TEXT = 2;
		bool credits;
		void showCredits()
		{
			DrawText(FormatText("PONG "), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("PONG", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / GAMETITLE_LINE_DIVIDER, FONT_SIZE_TITLE, DARKPURPLE);
			DrawText(FormatText("Credits"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Credits", FONT_SIZE) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / CREDITS_LINE_DIVIDER, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Héctor Iván Pereira"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Hector Ivan Pereira", FONT_SIZE) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / LINE_DIVIDER, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Assets Library"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Assets Library", FONT_SIZE) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / LINE_DIVIDER + FONT_SIZE, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Raylib, Freesounds.org"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Raylib, Freesounds.org", FONT_SIZE) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / LINE_DIVIDER + FONT_SIZE*2, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Music"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Music", FONT_SIZE) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / LINE_DIVIDER + FONT_SIZE*3, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("michorvath"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("michorvath", FONT_SIZE) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / LINE_DIVIDER + FONT_SIZE*4, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("https://freesound.org/people/michorvath/"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("https://freesound.org/people/michorvath/", FONT_SIZE_URL) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / LINE_DIVIDER + FONT_SIZE * 5, FONT_SIZE_URL, DARKGRAY);
			DrawText(FormatText("Sounds"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Sounds", FONT_SIZE) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / LINE_DIVIDER + FONT_SIZE * 6, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("thirteenthfail - NoiseCollector"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("thirteenthfail - NoiseCollector", FONT_SIZE) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / LINE_DIVIDER + FONT_SIZE * 7, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("https://freesound.org/people/NoiseCollector/"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("https://freesound.org/people/NoiseCollector/", FONT_SIZE_URL) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / LINE_DIVIDER + FONT_SIZE * 8, FONT_SIZE_URL, DARKGRAY);
			DrawText(FormatText("https://freesound.org/people/thirteenthfail/"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("https://freesound.org/people/thirteenthfail/", FONT_SIZE_URL) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / LINE_DIVIDER + (FONT_SIZE * 8)+FONT_SIZE_URL, FONT_SIZE_URL, DARKGRAY);
			DrawText(FormatText("Press Esc to back to Menu"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Press Esc to back to Menu", FONT_SIZE_HELPER) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / HELPER_LINE_DIVIDER + FONT_SIZE, FONT_SIZE_HELPER, DARKGRAY);
			DrawText(FormatText("Version 1.0"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Version 1.0", FONT_SIZE_HELPER) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight / VERSION_LINE_DIVIDER + FONT_SIZE, FONT_SIZE_HELPER, DARKGRAY);
			updateCredits();
		}
		void updateCredits()
		{
			if (IsKeyPressed(KEY_ESCAPE))
			{
				Menu::menu = true;
				credits = false;
			}
		}
	}
}