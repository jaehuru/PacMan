// Pacman
#include "pacTile.h"
// Engine
#include "Component/Transform/huruTransform.h"
#include "Component/TileMapRenderer/huruTileMapRenderer.h"

namespace pac
{
	::huru::math::Vector2 Tile::Size = ::huru::math::Vector2(12.f, 12.f);
	::huru::math::Vector2 Tile::Scale = ::huru::math::Vector2(1.f, 1.f);

	void Tile::Initialize()
	{
		::huru::GameObject::Initialize();

		::huru::TileMapRenderer* tileMapRenderer = this->GetComponent<::huru::TileMapRenderer>();
		if (tileMapRenderer)
		{
			tileMapRenderer->SetSize(Size);  // 외부에서 받아온 타일 크기 할당
			tileMapRenderer->SetScale(Scale);
		}
	}

	void Tile::Update()
	{
		::huru::GameObject::Update();
	}

	void Tile::LateUpdate()
	{
		::huru::GameObject::LateUpdate();
	}

	void Tile::Render(HDC hdc)
	{
		::huru::GameObject::Render(hdc);
	}
}
