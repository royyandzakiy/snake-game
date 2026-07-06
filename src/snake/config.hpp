#pragma once
#include <raylib.h>

namespace GameConfig {
constexpr const char *gameTitle{"Pong Game"};
constexpr float cellSize{30};
constexpr int cellCount{10};
constexpr int borderOffset{75};
constexpr int windowWidth{static_cast<int>((2 * borderOffset) + (cellSize * cellCount))};
constexpr int windowHeight{static_cast<int>((2 * borderOffset) + (cellSize * cellCount))};
constexpr float snakeDefaultMoveSpeed = 10.0f;
}; // namespace GameConfig

namespace GameColors {
constexpr Color BgColor{.r = 173, .g = 204, .b = 96, .a = 255};
constexpr Color BorderColor{.r = 43, .g = 51, .b = 24, .a = 255};
constexpr Color SnakeColor{.r = 43, .g = 51, .b = 24, .a = 255};
} // namespace GameColors
