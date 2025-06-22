//Pacman
#include "pacUtility.h"
#include "pacTile.h"
//Engine
#include "Component/Transform/huruTransform.h"

namespace pac::util
{
	Vector2 SnapToTileCenter(Vector2 tilePos)
	{
		return Vector2
		(
			tilePos.x * Tile::Size.x + Tile::Size.x * 0.5f,
			tilePos.y * Tile::Size.y + Tile::Size.y * 0.5f
		);
	}

	Vector2 WorldToTile(Vector2 worldPos)
	{
		return Vector2
		(
			static_cast<int>(worldPos.x / Tile::Size.x),
			static_cast<int>(worldPos.y / Tile::Size.y)
		);
	}

	bool IsOnPortalTile(Vector2 currentTile, const vector<Tile*>& portals)
	{
		for (Tile* portal : portals)
			if (portal->GetIndex() == currentTile)
				return true;
		return false;
	}

	void TeleportToOtherPortal(Vector2 currentTile, Transform* transform, const vector<Tile*>& portals)
	{
		if (portals.size() != 2) return;

		int current = (portals[0]->GetIndex() == currentTile) ? 0 : 1;
		int other = 1 - current;

		Vector2 targetTile = portals[other]->GetIndex();
		Vector2 targetCenter = SnapToTileCenter(targetTile);
		transform->SetPosition(targetCenter);
	}
}