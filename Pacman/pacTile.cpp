// Pacman
#include "pacTile.h"
#include "pacEnum.h"
#include "pacGameManager.h"
// Engine
#include "Component/Transform/huruTransform.h"
#include "Component/TileMapRenderer/huruTileMapRenderer.h"
#include "Component/SpriteRenderer/huruSpriteRenderer.h"
#include "Resource/huruResources.h"

namespace pac
{
	Vector2 Tile::Size = Vector2(12.f, 12.f);
	Vector2 Tile::Scale = Vector2(1.f, 1.f);

	Tile::Tile() :
		mIndexX(-1),
		mIndexY(-1),
		mTileType(eTileType::Path)
	{

	}

	Tile::~Tile()
	{

	}

	void Tile::Initialize()
	{
		TileMapRenderer* tileMapRenderer = this->GetComponent<TileMapRenderer>();
		if (tileMapRenderer)
		{
			tileMapRenderer->SetSize(Size);  // 외부에서 받아온 타일 크기 할당
			tileMapRenderer->SetScale(Scale);
		}

		GameObject::Initialize();
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Tile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
