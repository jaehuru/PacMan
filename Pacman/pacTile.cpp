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
		mTileType(eTileType::Path),
		mHasDot(false)
	{
		mHasDot = (mTileType == eTileType::Path);
	}

	Tile::~Tile()
	{

	}

	void Tile::Initialize()
	{
		TileMapRenderer* tileMapRenderer = this->GetComponent<TileMapRenderer>();
		if (tileMapRenderer)
		{
			tileMapRenderer->SetSize(Size);  // �ܺο��� �޾ƿ� Ÿ�� ũ�� �Ҵ�
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
		DrawDot(hdc);

		GameObject::Render(hdc);
	}

	void Tile::DrawDot(HDC hdc)
	{
		if (mTileType == eTileType::Path && mHasDot)
		{
			graphics::Texture* dotTexture = GameManager::GetInstance().GetDotTexture();

			if (dotTexture->GetTextureType() == graphics::Texture::eTextureType::Png)
			{
				Gdiplus::Graphics graphics(hdc);

				float width = dotTexture->GetWidth();
				float height = dotTexture->GetHeight();

				Vector2 drawPos = Vector2(mIndexX, mIndexY) * Size;
				drawPos.x += Size.x * 0.5f;  // Ÿ�� �߾� x ��ǥ
				drawPos.y += Size.y * 0.5f;  // Ÿ�� �߾� y ��ǥ

				drawPos.x -= width * 0.5f;   // �� �ؽ�ó ũ���� ������ ���� �߾� ����
				drawPos.y -= height * 0.5f;

				graphics.DrawImage(
					dotTexture->GetImage(),
					Gdiplus::Rect(
						(int)drawPos.x,
						(int)drawPos.y,
						(int)width,
						(int)height)
				);
			}
		}
	}
}
