// src/snake/game.hpp
#pragma once
#include "config.hpp"
#include "food.hpp"
#include "snake.hpp"
#include <raylib.h>
#include <string>
#include <utility>

class Game {
  public:
	Game(Snake &&snake) : m_snake(std::move(snake)), m_food(Food{GenerateRandomPos()}) {
		InitAudioDevice();
		eatSound = LoadSound("assets/audio/eat.mp3");
		gameoverSound = LoadSound("assets/audio/wall.mp3");
	}

	// Game() = delete; // remove default ctor
	~Game() = default;

	// copy & move operator
	Game(const Game &) noexcept = delete;			 // copy ctor, const lval
	Game &operator=(const Game &) noexcept = delete; // copy assg, const lval
	Game(Game &&) noexcept = delete;				 // move ctor, non-const rval (std::move)
	Game &operator=(Game &&) noexcept = delete;		 // move assg, non-const rval (std::move)

	auto Run() -> void {
		while (WindowShouldClose() == false) {
			BeginDrawing();
			ClearBackground(GameColors::BgColor);
			DrawText("Snake Game", GameConfig::borderOffset - 5, 20, 40, GameColors::BorderColor);
			DrawText(std::to_string(gameScore).c_str(), GameConfig::borderOffset - 5,
					 GameConfig::borderOffset + GameConfig::cellSize * GameConfig::cellCount + 10, 40,
					 GameColors::ScoreColor);
			DrawRectangleLinesEx(Rectangle{.x = GameConfig::borderOffset - 5,
										   .y = GameConfig::borderOffset - 5,
										   .width = GameConfig::cellSize * GameConfig::cellCount + 10,
										   .height = GameConfig::cellSize * GameConfig::cellCount + 10},
								 5, GameColors::BorderColor);

			CheckKeyPress();
			Update();
			Draw();

			EndDrawing();
		}
	}

  private:
	Snake m_snake;
	Food m_food;
	int gameScore{0};
	Sound eatSound{};
	Sound gameoverSound{};

	auto IsSnakeFoodCollide() -> bool {
		return static_cast<int>(m_snake.GetHeadPos().x) == m_food.getPosX() &&
			   static_cast<int>(m_snake.GetHeadPos().y) == m_food.getPosY();
	}

	auto IsSnakeWallCollide() -> bool {
		return static_cast<int>(m_snake.GetHeadPos().x) == GameConfig::cellCount ||
			   static_cast<int>(m_snake.GetHeadPos().x) == -1 ||
			   static_cast<int>(m_snake.GetHeadPos().y) == GameConfig::cellCount ||
			   static_cast<int>(m_snake.GetHeadPos().y) == -1;
	}

	auto IsSnakeHeadTailCollide() -> bool {
		if (m_snake.GetSize() <= 4)
			return false;

		return m_snake.IsInBody(m_snake.GetHeadPos(), 1);
	}

	auto Update() -> void {
		if (IsSnakeWallCollide() || IsSnakeHeadTailCollide()) {
			GameOver();
		}

		if (IsSnakeFoodCollide()) {
			auto newPos = GenerateRandomPos();
			m_food.setPosVec(newPos);
			m_snake.SetShouldAddSegment();
			gameScore++;
			PlaySound(eatSound);
		}

		m_food.Update();
		m_snake.Update();
	}

	auto Draw() -> void {
		m_food.Draw();
		m_snake.Draw();
	}

	auto CheckKeyPress() -> void {
		if (IsKeyPressed(KEY_UP)) {
			m_snake.MoveUp();
		}
		if (IsKeyPressed(KEY_DOWN)) {
			m_snake.MoveDown();
		}
		if (IsKeyPressed(KEY_LEFT)) {
			m_snake.MoveLeft();
		}
		if (IsKeyPressed(KEY_RIGHT)) {
			m_snake.MoveRight();
		}
	}

	auto GenerateRandomPos() -> Vector2 {
		auto randPosX = static_cast<float>(GetRandomValue(0, GameConfig::cellCount - 1));
		auto randPosY = static_cast<float>(GetRandomValue(0, GameConfig::cellCount - 1));

		// check if pos is inside snake
		while (m_snake.IsInBody(Vector2{.x = randPosX, .y = randPosY})) {
			randPosX = static_cast<float>(GetRandomValue(0, GameConfig::cellCount - 1));
			randPosY = static_cast<float>(GetRandomValue(0, GameConfig::cellCount - 1));
		}

		return Vector2{.x = randPosX, .y = randPosY};
	}

	auto GameOver() -> void {
		auto foodNewPos = GenerateRandomPos();
		m_food.setPosVec(foodNewPos);
		m_snake.Reset();
		m_snake.MoveStop();
		gameScore = 0;
		PlaySound(gameoverSound);
	}
};
