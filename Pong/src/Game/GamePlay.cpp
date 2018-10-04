#include "GamePlay.h"

#include <raylib.h>

#include "Screens\GameOver.h"
#include "Screens\Menu.h"

using namespace game;
namespace game {
	namespace GamePlay
	{
		Player player1;
		Player player2;
		Ball ball;

		Texture2D crash;

		const int screenWidth = 800;
		const int screenHeight = 600;
		bool gameover = false;
		bool machineON = false;

		Sound ping, pong;
		Music music;

		const int CALC_HALFSCREEN_HEIGHT = screenHeight / 2;
		const int CALC_HALFSCREEN_WIDTH = screenWidth / 2;
		static int FONT_SIZE_HELPER = 25;
		static const float HELPER_LINE_DIVIDER = 1.7;
		static const int DIVIDER_MEASURE_TEXT = 2;

		static const int INIT_PLAYERS_POSITION_X = 20;
		static const Vector2 PLAYERS_SIZE = { 10,80 };
		const int INIT_PLAYERS_POINTS = 0;
		static const int PLAYER_LIM_POINTS = 10;

		static const Vector2 INIT_BALLSPEED = { 0,0 };
		static const Vector2 LAUNCH_BALL_SPEED = {5,3};
		static const int BALL_RADIUS = 20;
		static const float BALL_COLLISION_SPEED_X = -1.018;
		static const float BALL_SPEED_MULTIPLIER = 75;
		static const float BALL_COLLISION_SPEED_MULTIPLIER_Y=4;

		static const float WALLS_SPEED_MULTIPLIER = -1;
		static const float PLAYER_MOVE_SPEED = 450;
		static const int CALC_PLAYER_TOP_LIM = 10;
		static const int CALC_PLAYER_BOT_LIM = 5;

		static const int FONT_SIZE_POINTS = 60;
		static const int POINTS_POS_Y = 10;
		static const int POINTS_POS_X_PLAYER1 = GamePlay::CALC_HALFSCREEN_WIDTH - 80;
		static const int POINTS_POS_X_PLAYER2 = GamePlay::CALC_HALFSCREEN_WIDTH + 20;

		static Vector2 midLine = { (float)GamePlay::CALC_HALFSCREEN_WIDTH, 20 };
		static const Vector2 MIDLINE_SIZE = {5,GamePlay::screenHeight - 40 };
		void InitGame()
		{
			Menu::menu = true;
			// Initialize player1
			player1.position.x = INIT_PLAYERS_POSITION_X;
			player1.position.y = CALC_HALFSCREEN_HEIGHT;
			player1.size = PLAYERS_SIZE;
			player1.points = INIT_PLAYERS_POINTS;

			// Initialize player2
			player2.position.x = (float)screenWidth - INIT_PLAYERS_POSITION_X;
			player2.position.y = CALC_HALFSCREEN_HEIGHT;
			player2.size = PLAYERS_SIZE;
			player2.points = INIT_PLAYERS_POINTS;

			// Initialize ball
			ball.position.x = CALC_HALFSCREEN_WIDTH;
			ball.position.y = CALC_HALFSCREEN_HEIGHT;
			ball.speed.x = INIT_BALLSPEED.x;
			ball.speed.y = INIT_BALLSPEED.y;
			ball.radius = BALL_RADIUS;
			ball.active = false;
		}
		void play()
		{
			#define AUDIO
			#ifdef AUDIO	
				UpdateMusicStream(music);
			#endif // AUDIO

			//--------------------------------------- Player 1 move -------------------------------------------
			if (IsKeyDown(KEY_W)) player1.position.y -= PLAYER_MOVE_SPEED * GetFrameTime();
			if ((player1.position.y - player1.size.y / CALC_PLAYER_TOP_LIM) <= 0) player1.position.y = player1.size.y / CALC_PLAYER_TOP_LIM;
			if (IsKeyDown(KEY_S)) player1.position.y += PLAYER_MOVE_SPEED * GetFrameTime();
			if ((player1.position.y + player1.size.y + CALC_PLAYER_BOT_LIM) >= screenHeight) player1.position.y = screenHeight - player1.size.y - CALC_PLAYER_BOT_LIM;
			//-------------------------------------------------------------------------------------------------

			if (machineON)
			{
				//--------------------------------------IA-Player---------------------------------------------
					if ((player2.position.y + player2.size.y / 2) > ball.position.y) player2.position.y -= PLAYER_MOVE_SPEED * GetFrameTime();
					if ((player2.position.y - player2.size.y / CALC_PLAYER_TOP_LIM) <= 0) player2.position.y = player2.size.y / CALC_PLAYER_TOP_LIM;
					if ((player2.position.y + player2.size.y / 2) < ball.position.y) player2.position.y += PLAYER_MOVE_SPEED * GetFrameTime();
					if ((player2.position.y + player2.size.y + CALC_PLAYER_BOT_LIM) >= screenHeight) player2.position.y = screenHeight - player2.size.y - CALC_PLAYER_BOT_LIM;
			}
			else
			{
				//--------------------------------------- Player 2 move -------------------------------------------
				if (IsKeyDown(KEY_UP)) player2.position.y -= PLAYER_MOVE_SPEED * GetFrameTime();
				if ((player2.position.y - player2.size.y / CALC_PLAYER_TOP_LIM) <= 0) player2.position.y = player2.size.y / CALC_PLAYER_TOP_LIM;
				if (IsKeyDown(KEY_DOWN)) player2.position.y += PLAYER_MOVE_SPEED * GetFrameTime();
				if ((player2.position.y + player2.size.y + CALC_PLAYER_BOT_LIM) >= screenHeight) player2.position.y = screenHeight - player2.size.y - CALC_PLAYER_BOT_LIM;
				//-------------------------------------------------------------------------------------------------
			}

			// Ball launching logic
			if (!ball.active)
			{
				if (IsKeyPressed(KEY_SPACE))
				{
					ball.active = true;
					ball.speed.x = GetRandomValue(-1, 1) * LAUNCH_BALL_SPEED.x;
					ball.speed.y = GetRandomValue(-5, 5) * LAUNCH_BALL_SPEED.y;
					while (ball.speed.x == 0)
					{
						ball.speed.x = GetRandomValue(-1, 1) * LAUNCH_BALL_SPEED.x;
					}
				}
			}
			// Ball movement logic
			if (ball.active)
			{
				ball.position.x += ball.speed.x*BALL_SPEED_MULTIPLIER * GetFrameTime();
				ball.position.y += ball.speed.y*BALL_SPEED_MULTIPLIER * GetFrameTime();
			}
			else
			{
				ball.position.x = CALC_HALFSCREEN_WIDTH;
				ball.position.y = CALC_HALFSCREEN_HEIGHT;
			}
			// Collision logic: ball vs walls 
			if (((ball.position.y + ball.radius) >= screenHeight) || ((ball.position.y - ball.radius) <= 0))
			{
				if ((ball.position.y + ball.radius) >= screenHeight)
				{
					ball.position.y = screenHeight - ball.radius;
				}
				else if ((ball.position.y - ball.radius) <= 0)
				{
					ball.position.y = ball.radius;
				}
				ball.speed.y *= WALLS_SPEED_MULTIPLIER;
			}
			if ((ball.position.x - ball.radius) <= 0)
			{
				ball.speed.x = INIT_BALLSPEED.x;
				ball.speed.y = INIT_BALLSPEED.y;
				ball.active = false;

				player2.points++;
				if (player2.points >= PLAYER_LIM_POINTS)
				{
					gameover = true;
				}
				player1.position.y = CALC_HALFSCREEN_HEIGHT;
				player2.position.y = CALC_HALFSCREEN_HEIGHT;
			}
			if ((ball.position.x + ball.radius) >= screenWidth)
			{
				ball.speed.x = INIT_BALLSPEED.x;
				ball.speed.y = INIT_BALLSPEED.y;
				ball.active = false;

				player1.points++;

				if (player1.points >= PLAYER_LIM_POINTS)
				{
					gameover = true;
				}

				player1.position.y = CALC_HALFSCREEN_HEIGHT;
				player2.position.y = CALC_HALFSCREEN_HEIGHT;
			}
			// Collision logic: ball vs player1
			if (CheckCollisionCircleRec(ball.position, ball.radius, { player1.position.x - player1.size.x / 2, player1.position.y , player1.size.x, player1.size.y }))
			{
				if (ball.speed.x != 0)
				{
					ball.position.x = player1.position.x + player1.size.x + ball.radius;
					ball.speed.x *= BALL_COLLISION_SPEED_X;
					if (ball.speed.y >= 0)
					{
						ball.speed.y = (ball.position.y - player1.position.y) / (player1.size.y / 2) * BALL_COLLISION_SPEED_MULTIPLIER_Y;
					}
					else
					{
						ball.speed.y = (ball.position.y - player1.position.y) / (player1.size.y / 2) * -BALL_COLLISION_SPEED_MULTIPLIER_Y;
					}
				}
#ifdef AUDIO	
				if (GetRandomValue(0, 1) != 0)
					PlaySound(ping);
				else
					PlaySound(pong);
#endif // AUDIO
			}
			// Collision logic: ball vs player2
			if (CheckCollisionCircleRec(ball.position, ball.radius, { player2.position.x + player2.size.x / 2, player2.position.y , player2.size.x, player2.size.y }))
			{
				if (ball.speed.x != 0)
				{
					ball.position.x = player2.position.x - player1.size.x / 2 - ball.radius / 2;
					ball.speed.x *= BALL_COLLISION_SPEED_X;
					if (ball.speed.y >= 0)
					{
						ball.speed.y = (ball.position.y - player2.position.y) / (player2.size.y / 2) * BALL_COLLISION_SPEED_MULTIPLIER_Y;
					}
					else
					{
						ball.speed.y = (ball.position.y - player2.position.y) / (player2.size.y / 2) * -BALL_COLLISION_SPEED_MULTIPLIER_Y;
					}
				}
			#ifdef AUDIO	
				if (GetRandomValue(0, 1) != 0)
					PlaySound(ping);
				else
					PlaySound(pong);
			#endif // AUDIO
			}
		}
		void drawGame()
		{
			DrawText(FormatText("%02i", GamePlay::player1.points),POINTS_POS_X_PLAYER1, POINTS_POS_Y, FONT_SIZE_POINTS, DARKGRAY);
			DrawText(FormatText("%02i", GamePlay::player2.points), POINTS_POS_X_PLAYER2, POINTS_POS_Y, FONT_SIZE_POINTS, DARKGRAY);
			DrawRectangle(midLine.x, midLine.y, MIDLINE_SIZE.x, MIDLINE_SIZE.y, DARKGRAY);
			if (!ball.active)
			DrawText(FormatText("Press Space to Start"), GamePlay::CALC_HALFSCREEN_WIDTH - (MeasureText("Press Space to Start", FONT_SIZE_HELPER) / DIVIDER_MEASURE_TEXT), GamePlay::screenHeight /HELPER_LINE_DIVIDER, FONT_SIZE_HELPER, GRAY);
			DrawCircleV(GamePlay::ball.position, GamePlay::ball.radius, DARKPURPLE);
			DrawRectangle(GamePlay::player1.position.x, GamePlay::player1.position.y, GamePlay::player1.size.x, GamePlay::player1.size.y, DARKPURPLE);
			DrawRectangle(GamePlay::player2.position.x, GamePlay::player2.position.y, GamePlay::player2.size.x, GamePlay::player2.size.y, DARKPURPLE);
		}
	}
}