#include "config.hpp"
#include "game.hpp"
#include "snake.hpp"
#include <fmt/base.h>
#include <raylib.h>
#include <utility>

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
