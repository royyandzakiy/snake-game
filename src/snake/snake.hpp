#pragma once
#include "config.hpp"
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <deque>
#include <fmt/base.h>
#include <iterator>
#include <raylib.h>

class Snake {
  public:
	Snake() = default;
	~Snake() = default;

	Snake(const Snake &) noexcept = delete;			   // copy ctor, const lval
	Snake &operator=(const Snake &) noexcept = delete; // copy assg, const lval
	Snake(Snake &&) noexcept = default;				   // move ctor, non-const rval (std::move)
	Snake &operator=(Snake &&) noexcept = delete;	   // move assg, non-const rval (std::move)

	auto Update() -> void {
		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> moveInterval = std::chrono::duration<float>(1.0f / moveSpeed);
		if (currentTime - lastTime > moveInterval) {
			if (!shouldAddSegment) {
				body.pop_back(); // remove tail to look moving
			} else {
				// do NOT remove tail to look growing
				shouldAddSegment = false;
			}

			body.push_front(
				Vector2{.x = body.at(0).x + moveDirection.x, .y = body.at(0).y + moveDirection.y}); // move head forward

			lastTime = std::chrono::steady_clock::now();
		}
	}

	auto Draw() -> void {
		bool isHead = true;
		Color colorSelected{};
		std::ranges::for_each(body, [&isHead, &colorSelected](const auto &segmentPos) {
			Rectangle segment{.x = GameConfig::borderOffset + segmentPos.x * GameConfig::cellSize,
							  .y = GameConfig::borderOffset + segmentPos.y * GameConfig::cellSize,
							  .width = GameConfig::cellSize,
							  .height = GameConfig::cellSize};
			colorSelected = isHead ? GameColors::SnakeHeadColor : GameColors::SnakeColor;
			if (isHead)
				isHead = false;
			DrawRectangleRounded(segment, 0.5, 6, colorSelected);
		});
	}

	[[nodiscard]] auto GetSize() const -> size_t {
		return body.size();
	}
	auto Reset() -> void {
		body = {Vector2{.x = 6, .y = 9}, Vector2{.x = 5, .y = 9}, Vector2{.x = 4, .y = 9}};
		moveDirection = {.x = 1, .y = 0};
	}
	auto MoveStart() -> void {
		moveSpeed = GameConfig::snakeDefaultMoveSpeed;
	}
	auto MoveStop() -> void {
		moveSpeed = 0.0f;
	}
	auto MoveUp() -> void {
		if (bool isMovingDown = moveDirection.y == 1; !isMovingDown)
			moveDirection = {.x = 0, .y = -1};
		if (moveSpeed == 0.0f)
			MoveStart();
	}
	auto MoveDown() -> void {
		if (bool isMovingUp = moveDirection.y == -1; !isMovingUp)
			moveDirection = {.x = 0, .y = 1};
		if (moveSpeed == 0.0f)
			MoveStart();
	}
	auto MoveLeft() -> void {
		if (bool isMovingRight = moveDirection.x == 1; !isMovingRight)
			moveDirection = {.x = -1, .y = 0};
		if (moveSpeed == 0.0f)
			MoveStart();
	}
	auto MoveRight() -> void {
		if (bool isMovingLeft = moveDirection.x == -1; !isMovingLeft)
			moveDirection = {.x = 1, .y = 0};
		if (moveSpeed == 0.0f)
			MoveStart();
	}

	[[nodiscard]] auto GetHeadPos() const -> Vector2 {
		return body.at(0);
	}

	[[nodiscard]] auto IsInvalid() const -> bool {
		return body.empty() || body.size() == static_cast<size_t>(-1);
	}

	[[nodiscard]] auto IsInBody(Vector2 element, size_t skipBodySegmentCount = 0) const -> bool {
		if (IsInvalid()) {
			fmt::println(stderr, "WARNING: body is invalid in IsInBody!");
			return false;
		}

		if (skipBodySegmentCount < 0)
			return false;

		auto start = std::next(body.begin(), static_cast<ptrdiff_t>(skipBodySegmentCount));
		return std::ranges::find_if(start, body.end(), [&element](const Vector2 &bodySegment) -> bool {
				   return bodySegment.x == element.x && bodySegment.y == element.y;
			   }) != body.end();
	}

	auto SetShouldAddSegment() -> void {
		shouldAddSegment = true;
	}

  private:
	std::deque<Vector2> body{Vector2{.x = 6, .y = 9}, Vector2{.x = 5, .y = 9}, Vector2{.x = 4, .y = 9}};
	Vector2 moveDirection{.x = 1, .y = 0};
	std::chrono::time_point<std::chrono::steady_clock> lastTime{};
	float moveSpeed{GameConfig::snakeDefaultMoveSpeed};
	bool shouldAddSegment{false};
};
