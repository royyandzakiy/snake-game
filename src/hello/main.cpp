#include <array>
#include <concepts>
#include <fmt/base.h>
#include <functional>
#include <raylib.h>
#include <string>
#include <type_traits>
#include <utility>

namespace GameConfig {
constexpr const char *gameTitle{"Pong Game"};
constexpr int cellSize{30};
constexpr int cellCount{25};
constexpr float windowWidth{cellSize * cellCount};
constexpr float windowHeight{cellSize * cellCount};
}; // namespace GameConfig

namespace GameColors {
constexpr Color BallColor{.r = 230, .g = 247, .b = 0, .a = 255};
constexpr Color PaddleColor{.r = 66, .g = 10, .b = 252, .a = 255};
constexpr Color BgColor{.r = 173, .g = 204, .b = 96, .a = 255};
constexpr Color BgLeftColor{.r = 225, .g = 230, .b = 239, .a = 255}; // e1e6ef
constexpr Color BgCircleColor{.r = 255, .g = 255, .b = 255, .a = 255};
constexpr Color ScoreColor{.r = 255, .g = 255, .b = 255, .a = 255};
} // namespace GameColors

class Food {
  public:
	Food(Vector2 pos) : m_posX(static_cast<int>(pos.x)), m_posY(static_cast<int>(pos.y)) {
		const char *path = "C:/project-coding/cpp/202606/snake-game/assets/imgs/food.png";

		if (FileExists(path)) {
			Image image = LoadImage(path);
			m_texture = LoadTextureFromImage(image);
			UnloadImage(image);

			if (m_texture.id == 0) {
				TraceLog(LOG_ERROR, "texture fails to load!");
			}

			TraceLog(LOG_INFO, "Food texture loaded: %dx%d", m_texture.width, m_texture.height);
		}
	}

	~Food() {
		UnloadTexture(m_texture);
	}

	Food(const Food &) noexcept = delete;			 // copy ctor, const lval
	Food &operator=(const Food &) noexcept = delete; // copy assg, const lval
	Food(Food &&) noexcept = default;				 // move ctor, non-const rval (std::move)
	Food &operator=(Food &&) noexcept = default;	 // move assg, non-const rval (std::move)

	auto Draw() -> void {
		DrawTexture(m_texture, m_posX * GameConfig::cellSize, m_posY * GameConfig::cellSize, WHITE);
	}
	auto Update() -> void {
	}

  private:
	Texture2D m_texture{};
	int m_posX, m_posY;
};

class Game {
  public:
	Game() : m_food(Food{generateRandomPos()}) {
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

			Update_prv();
			Draw_prv();

			EndDrawing();
		}
	}

  private:
	Food m_food;

	auto Update_prv() -> void {
		m_food.Update();
	}

	auto Draw_prv() -> void {
		m_food.Draw();
	}

	auto generateRandomPos() -> Vector2 {
		auto x = static_cast<float>(GetRandomValue(0, GameConfig::cellCount - 1));
		auto y = static_cast<float>(GetRandomValue(0, GameConfig::cellCount - 1));
		return Vector2{.x = x, .y = y};
	}
};

auto main() -> int {
	InitWindow(static_cast<int>(GameConfig::windowWidth), static_cast<int>(GameConfig::windowHeight),
			   GameConfig::gameTitle);
	SetTargetFPS(60);

	Game game{};
	game.Run();

	CloseWindow();
	return 0;
}
