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
constexpr float windowWidth{1280};
constexpr float windowHeight{800};
}; // namespace GameConfig

namespace GameColors {
constexpr Color BallColor{.r = 230, .g = 247, .b = 0, .a = 255};
constexpr Color PaddleColor{.r = 66, .g = 10, .b = 252, .a = 255};
constexpr Color BgColor{.r = 211, .g = 218, .b = 229, .a = 255};	 // d3dae5
constexpr Color BgLeftColor{.r = 225, .g = 230, .b = 239, .a = 255}; // e1e6ef
constexpr Color BgCircleColor{.r = 255, .g = 255, .b = 255, .a = 255};
constexpr Color ScoreColor{.r = 255, .g = 255, .b = 255, .a = 255};
} // namespace GameColors

class Food {
  public:
	Food(Vector2 pos, const int cellSize)
		: m_posX(static_cast<int>(pos.x)), m_posY(static_cast<int>(pos.y)), m_cellSize(cellSize) {
		Image image = LoadImage("assets/graphics/food.png");
		Texture2D m_texture = LoadTextureFromImage(image);
		UnloadImage(image);
	}

	~Food() {
		UnloadTexture(m_texture);
	}

	Food(const Food &) noexcept = delete;			 // copy ctor, const lval
	Food &operator=(const Food &) noexcept = delete; // copy assg, const lval
	Food(Food &&) noexcept = delete;				 // move ctor, non-const rval (std::move)
	Food &operator=(Food &&) noexcept = delete;		 // move assg, non-const rval (std::move)

	auto Draw() {
		DrawTexture(m_texture, m_posX * m_cellSize, m_posY * m_cellSize, WHITE);
	}
	auto Update() {
	}

  private:
	Texture m_texture{};
	int m_posX, m_posY;
	int m_cellSize;
};

class Game {
  public:
	Game()
	// :
	{

		InitWindow(static_cast<int>(GameConfig::windowWidth), static_cast<int>(GameConfig::windowHeight),
				   GameConfig::gameTitle);
		SetTargetFPS(60);
	}

	// Game() = delete; // remove default ctor
	~Game() {
		CloseWindow();
	}

	// copy & move operator
	Game(const Game &) noexcept = delete;			 // copy ctor, const lval
	Game &operator=(const Game &) noexcept = delete; // copy assg, const lval
	Game(Game &&) noexcept = delete;				 // move ctor, non-const rval (std::move)
	Game &operator=(Game &&) noexcept = delete;		 // move assg, non-const rval (std::move)

	void Run() {
		while (WindowShouldClose() == false) {
			BeginDrawing();
			ClearBackground(GameColors::BgColor);

			Update_prv();
			Draw_prv();

			EndDrawing();
		}
	}

  private:
	void Update_prv() {
		// ...
	}

	void Draw_prv() {
		// ...
	}
};

auto main() -> int {
	Game game{};

	game.Run();
	return 0;
}
