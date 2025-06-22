#pragma once

#include "Common/CommonInclude.h"

namespace huru
{
	class Tile;
	class Transform;
}

namespace pac::util
{
	Vector2 SnapToTileCenter(Vector2 tilePos);
	Vector2 WorldToTile(Vector2 worldPos);
	bool IsOnPortalTile(Vector2 currentTile, const vector<Tile*>& portals);
	void TeleportToOtherPortal(Vector2 currentTile, Transform* transform, const vector<Tile*>& portals);
}
