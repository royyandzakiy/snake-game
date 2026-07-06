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
// Soothing blue theme - calm ocean palette
constexpr Color BgColor{.r = 235, .g = 245, .b = 255, .a = 255};	  // Very light ice blue background
constexpr Color BorderColor{.r = 30, .g = 60, .b = 114, .a = 255};	  // Deep navy blue border
constexpr Color SnakeColor{.r = 41, .g = 128, .b = 185, .a = 255};	  // Medium ocean blue snake
constexpr Color SnakeHeadColor{.r = 21, .g = 87, .b = 136, .a = 255}; // Darker blue for head
constexpr Color ScoreColor{.r = 30, .g = 60, .b = 114, .a = 255};	  // Navy blue for score
} // namespace GameColors
