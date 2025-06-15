#pragma once

namespace pac::define
{
	inline constexpr int MaxMapWidth = 96;
	inline constexpr int MaxMapHeight = 40;

	inline constexpr int GetLinearIndex(int x, int y)
	{
		return y * MaxMapWidth + x;
	}

	inline constexpr int GetLinearIndex(const Vector2& idx)
	{
		return static_cast<int>(idx.y) * MaxMapWidth + static_cast<int>(idx.x);
	}
}
