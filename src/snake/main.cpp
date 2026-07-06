#include "config.hpp"
#include "game.hpp"
#include "snake.hpp"
#include <raylib.h>
#include <utility>

auto main() -> int {
	InitWindow(GameConfig::windowWidth, GameConfig::windowHeight, GameConfig::gameTitle);
	SetTargetFPS(60);

	Snake snake{};
	Game game{std::move(snake)};
	game.Run();

	CloseWindow();
	return 0;
}
