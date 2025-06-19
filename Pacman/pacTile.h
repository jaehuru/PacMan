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
			Portal,
			Pellet
		};

		Tile();
		~Tile();

		void		Initialize()	override;
		void		Update()		override;
		void		LateUpdate()	override;
		void		Render(HDC hdc) override;

		void		SetIndex(int x, int y)
		{
			mIndexX = x;
			mIndexY = y;
		}
		Vector2		GetIndex()				const { return Vector2 (mIndexX, mIndexY); }

		void		SetTileType(eTileType type)	{ mTileType = type; }
		eTileType	GetTileType()				const { return mTileType; }
		void		SetHasDot(bool hasDot)		{ mHasDot = hasDot; }
		bool		HasDot() const				{ return mHasDot; }

	private:
		void		DrawDot(HDC hdc);

	public:
		static Vector2	Size;
		static Vector2	Scale;

	private:
		int				mIndexX;
		int				mIndexY;

		eTileType		mTileType;

		bool			mHasDot;
	};
}
