#pragma once

#include "GameObject/huruGameObject.h"

namespace pac
{
	class Tile : public GameObject
	{
	public:
		enum class eTileType
		{
			Path,
			Wall,
			Jail,
			Portal
		};

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
		Vector2 GetIndexPosition() const { return Vector2 (mIndexX, mIndexY); }
		int GetIndexX() const { return mIndexX; }
		int GetIndexY() const { return mIndexY; }

		void SetTileType(eTileType type) { mTileType = type; }
		eTileType GetTileType() const { return mTileType; }

	public:
		static Vector2 Size;
		static Vector2 Scale;

	private:
		int mIndexX;
		int mIndexY;

		eTileType mTileType;
	};
}
