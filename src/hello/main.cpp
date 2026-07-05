#include <algorithm>
#include <chrono>
#include <cstdio>
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
constexpr Color BgColor{.r = 173, .g = 204, .b = 96, .a = 255};
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
				fmt::println(stderr, "texture fails to load!");
			}

			fmt::println("Food texture loaded: {}x{}", m_texture.width, m_texture.height);
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

	auto setPosVec(Vector2 vec) -> void {
		m_posX = static_cast<int>(vec.x);
		m_posY = static_cast<int>(vec.y);
	}
	[[nodiscard]] auto getPosX() const -> int {
		return m_posX;
	}
	[[nodiscard]] auto getPosY() const -> int {
		return m_posY;
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
	Snake &operator=(Snake &&) noexcept = delete;	   // move assg, non-const rval (std::move)

	auto Update() -> void {
		bool isMovingUp = moveDirection.y == -1;
		bool isMovingDown = moveDirection.y == 1;
		bool isMovingLeft = moveDirection.x == -1;
		bool isMovingRight = moveDirection.x == 1;

		if (IsKeyPressed(KEY_UP) && !isMovingDown)
			moveDirection = {.x = 0, .y = -1};
		if (IsKeyPressed(KEY_DOWN) && !isMovingUp)
			moveDirection = {.x = 0, .y = 1};
		if (IsKeyPressed(KEY_LEFT) && !isMovingRight)
			moveDirection = {.x = -1, .y = 0};
		if (IsKeyPressed(KEY_RIGHT) && !isMovingLeft)
			moveDirection = {.x = 1, .y = 0};

		auto currentTime = std::chrono::steady_clock::now();
		if (currentTime - lastTime > moveInterval) {
			body.pop_back();
			body.push_front(Vector2{.x = body.at(0).x + moveDirection.x, .y = body.at(0).y + moveDirection.y});
			lastTime = std::chrono::steady_clock::now();
		}
	}

	auto Draw() -> void {
		std::ranges::for_each(body, [](const auto &pos) {
			Rectangle segment{.x = pos.x * GameConfig::cellSize,
							  .y = pos.y * GameConfig::cellSize,
							  .width = GameConfig::cellSize,
							  .height = GameConfig::cellSize};
			DrawRectangleRounded(segment, 0.5, 6, GameColors::SnakeColor);
		});
	}

	[[nodiscard]] auto GetHeadPos() const -> Vector2 {
		return body.at(0);
	}

	[[nodiscard]] auto IsValid() const -> bool {
		return body.empty() || body.size() == static_cast<size_t>(-1);
	}

	[[nodiscard]] auto IsInBody(Vector2 vec) const -> bool {
		if (IsValid()) {
			fmt::println(stderr, "WARNING: body is invalid in IsInBody!");
			return false;
		}

		return std::ranges::find_if(body, [&vec](const Vector2 &bodySegment) -> bool {
				   return bodySegment.x == vec.x && bodySegment.y == vec.y;
			   }) != body.end();
	}

  private:
	std::deque<Vector2> body = {Vector2{.x = 6, .y = 9}, Vector2{.x = 5, .y = 9}, Vector2{.x = 4, .y = 9}};
	Vector2 moveDirection{.x = 1, .y = 0};
	std::chrono::time_point<std::chrono::steady_clock> lastTime{};
	std::chrono::milliseconds moveInterval = 200ms;
};

class Game {
  public:
	Game(Snake &&snake) : m_snake(std::move(snake)), m_food(Food{GenerateRandomPos()}) {
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

			Update();
			Draw();

			EndDrawing();
		}
	}

  private:
	Snake m_snake;
	Food m_food;

	auto Update() -> void {
		bool isSnakeFoodCollide = static_cast<int>(m_snake.GetHeadPos().x) == m_food.getPosX() &&
								  static_cast<int>(m_snake.GetHeadPos().y) == m_food.getPosY();

		if (isSnakeFoodCollide) {
			auto newPos = GenerateRandomPos();
			m_food.setPosVec(newPos);
		}

		m_food.Update();
		m_snake.Update();
	}

	auto Draw() -> void {
		m_food.Draw();
		m_snake.Draw();
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
