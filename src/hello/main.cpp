#include <chrono>
#include <deque>
#include <fmt/base.h>
#include <raylib.h>
#include <utility>

using namespace std::chrono_literals;

namespace GameConfig {
constexpr const char *gameTitle{"Pong Game"};
constexpr float cellSize{30};
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
constexpr Color SnakeColor{.r = 43, .g = 51, .b = 24, .a = 255};
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
		DrawTexture(m_texture, m_posX * static_cast<int>(GameConfig::cellSize),
					m_posY * static_cast<int>(GameConfig::cellSize), WHITE);
	}
	auto Update() -> void {
	}

  private:
	Texture2D m_texture{};
	int m_posX, m_posY;
};

class Snake {
  public:
	Snake() = default;
	~Snake() = default;

	Snake(const Snake &) noexcept = delete;			   // copy ctor, const lval
	Snake &operator=(const Snake &) noexcept = delete; // copy assg, const lval
	Snake(Snake &&) noexcept = default;				   // move ctor, non-const rval (std::move)
	Snake &operator=(Snake &&) noexcept = default;	   // move assg, non-const rval (std::move)

	auto Update() -> void {
		// read keys
		bool isMovingUp = moveDirection.y == -1;
		bool isMovingDown = moveDirection.y == 1;
		bool isMovingLeft = moveDirection.x == -1;
		bool isMovingRight = moveDirection.x == 1;

		if (IsKeyPressed(KEY_UP) && !isMovingDown)
			moveDirection = {0, -1};
		if (IsKeyPressed(KEY_DOWN) && !isMovingUp)
			moveDirection = {0, 1};
		if (IsKeyPressed(KEY_LEFT) && !isMovingRight)
			moveDirection = {-1, 0};
		if (IsKeyPressed(KEY_RIGHT) && !isMovingLeft)
			moveDirection = {1, 0};

		auto currentTime = std::chrono::steady_clock::now();
		if (currentTime - lastTime > moveInterval) {
			body.pop_back();
			body.push_front(Vector2{body.at(0).x + moveDirection.x, body.at(0).y + moveDirection.y});
			lastTime = std::chrono::steady_clock::now();
		}
	}

	auto Draw() -> void {
		for (size_t i = 0; i < body.size(); ++i) {
			float x = body.at(i).x;
			float y = body.at(i).y;
			Rectangle segment{.x = x * GameConfig::cellSize,
							  .y = y * GameConfig::cellSize,
							  .width = GameConfig::cellSize,
							  .height = GameConfig::cellSize};
			DrawRectangleRounded(segment, 0.5, 6, GameColors::SnakeColor);
		}
	}

  private:
	std::deque<Vector2> body = {Vector2{.x = 6, .y = 9}, Vector2{.x = 5, .y = 9}, Vector2{.x = 4, .y = 9}};
	Vector2 moveDirection{1, 0};
	std::chrono::time_point<std::chrono::steady_clock> lastTime{};
	const std::chrono::milliseconds moveInterval = 200ms;
};

class Game {
  public:
	Game(Snake &&snake) : m_food(Food{generateRandomPos()}), m_snake(std::move(snake)) {
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
	Snake m_snake;

	auto Update_prv() -> void {
		m_food.Update();
		m_snake.Update();
	}

	auto Draw_prv() -> void {
		m_food.Draw();
		m_snake.Draw();
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

	Snake snake{};
	Game game{std::move(snake)};
	game.Run();

	CloseWindow();
	return 0;
}
