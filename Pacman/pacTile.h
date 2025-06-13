#pragma once

#include "GameObject/huruGameObject.h"

namespace pac
{
	class Tile : public ::huru::GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetIndexPosition(int x, int y)
		{
			mIndexX = x;
			mIndexY = y;
		}
		int GetIndexX() const { return mIndexX; }
		int GetIndexY() const { return mIndexY; }

	public:
		static ::huru::math::Vector2 Size;
		static ::huru::math::Vector2 Scale;

	private:
		int mIndexX = -1;
		int mIndexY = -1;

	};
}
