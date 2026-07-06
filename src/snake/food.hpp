#pragma once
#include "config.hpp"
#include <cstdio>
#include <fmt/base.h>
#include <raylib.h>

class Food {
  public:
	Food(Vector2 pos) : m_posX(static_cast<int>(pos.x)), m_posY(static_cast<int>(pos.y)) {
		const char *path = "assets/imgs/food.png";

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
		DrawTexture(m_texture, GameConfig::borderOffset + m_posX * static_cast<int>(GameConfig::cellSize),
					GameConfig::borderOffset + m_posY * static_cast<int>(GameConfig::cellSize), WHITE);
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
