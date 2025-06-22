//Pacman
#include "pacTileManager.h"
#include "pacGameManager.h"
#include "pacTile.h"
#include "pacPellet.h"
//Engine
#include "Resource/huruTexture.h"
#include "Object/huruObject.h"
#include "Component/TileMapRenderer/huruTileMapRenderer.h"

namespace pac
{
	void TileManager::LoadMapFile(const wstring& filePath, graphics::Texture* texture)
	{
		Clear(); // 기존 데이터 초기화

		mTileMap.resize(define::MaxMapWidth * define::MaxMapHeight, nullptr);

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, filePath.c_str(), L"rb");

		if (!pFile)
		{
			wstring msg = L"Failed to open file: " + filePath;
			MessageBox(nullptr, msg.c_str(), L"Error", MB_OK);
			return;
		}

		while (true)
		{
			int tool_idxX = 0, tool_idxY = 0;
			int tool_posX = 0, tool_posY = 0;

			if (fread(&tool_idxX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&tool_idxY, sizeof(int), 1, pFile) != 1) break;
			if (fread(&tool_posX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&tool_posY, sizeof(int), 1, pFile) != 1) break;

			Tile* tile = object::Instantiate<Tile>(ToEngineLayerType(ePacLayerType::Tile), Vector2(tool_posX, tool_posY));
			int tileTypeInt = 0;
			if (fread(&tileTypeInt, sizeof(int), 1, pFile) != 1) break;
			tile->SetTileType(static_cast<Tile::eTileType>(tileTypeInt));

			int tileIdxX = tool_posX / Tile::Size.x;
			int tileIdxY = tool_posY / Tile::Size.y;
			int linearIndex = define::GetLinearIndex(tileIdxX, tileIdxY);

			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			tmr->SetTexture(texture);
			tmr->SetSize(Tile::Size);
			tmr->SetScale(Tile::Scale);
			tmr->SetIndex(Vector2(tool_idxX, tool_idxY));

			tile->SetIndex(tileIdxX, tileIdxY);

			if (linearIndex >= 0 && linearIndex < static_cast<int>(mTileMap.size()))
			{
				mTileMap[linearIndex] = tile;
			}

			if (tile->GetTileType() == Tile::eTileType::Portal)
			{
				mPortalTiles.push_back(tile);
			}

			if (tile->GetTileType() == Tile::eTileType::Pellet)
			{
				Pellet* pellet = object::Instantiate<Pellet>(ToEngineLayerType(ePacLayerType::Item), Vector2::Zero);
				pellet->Initialize();
				tile->AddChild(pellet);

				Vector2 tilePos = tile->GetComponent<Transform>()->GetPosition();
				Vector2 pelletPos = tilePos + Tile::Size * 0.5f;
				pellet->GetComponent<Transform>()->SetPosition(pelletPos);
			}
		}
		fclose(pFile);

		int maxX = 0;
		int maxY = 0;
		for (Tile* tile : mTileMap)
		{
			if (tile)
			{
				int x = static_cast<int>(tile->GetIndex().x);
				int y = static_cast<int>(tile->GetIndex().y);
				if (x > maxX) maxX = x;
				if (y > maxY) maxY = y;
			}
		}
		mMapWidth = maxX + 1;
		mMapHeight = maxY + 1;
	}

	void TileManager::Clear()
	{
		for (Tile* tile : mTileMap)
			object::Destroy(tile);
		mTileMap.clear();
		mPortalTiles.clear();
	}

	Tile* TileManager::GetTile(int x, int y)
	{
		if (x < 0 || y < 0 || x >= define::MaxMapWidth || y >= define::MaxMapHeight)
			return nullptr;

		int index = define::GetLinearIndex(x, y);
		if (index < 0 || index >= static_cast<int>(mTileMap.size()))
			return nullptr;

		return mTileMap[index];
	}
}