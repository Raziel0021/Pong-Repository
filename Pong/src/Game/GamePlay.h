#ifndef GAMEPLAY_H
#define GAMEPLAY_H


#include <raylib.h>
namespace game {
	namespace GamePlay
	{
		struct Player
		{
			Vector2 position;
			Vector2 size;
			int points;
		};

		struct Ball
		{
			Vector2 position;
			Vector2 speed;
			int radius;
			bool active;
		};

		extern Ball ball;
		extern Player player1, player2;

		extern Sound ping, pong;
		extern Music music;
		
		extern const int screenWidth;
		extern const int screenHeight;
		extern bool gameover;
		extern bool machineON;

		extern const int INIT_PLAYERS_POINTS;

		extern const int CALC_HALFSCREEN_HEIGHT;
		extern const int CALC_HALFSCREEN_WIDTH;

		void InitGame();
		void play();
		
		void drawGame();
	}
}
#endif // !GAMEPLAY_H