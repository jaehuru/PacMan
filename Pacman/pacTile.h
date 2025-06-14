#pragma once

#include "GameObject/huruGameObject.h"

namespace pac
{
	class Tile : public GameObject
	{
	public:
		Tile();
		~Tile();

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
		static Vector2 Size;
		static Vector2 Scale;

	private:
		int mIndexX;
		int mIndexY;
	};
}
