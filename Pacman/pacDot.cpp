//Pacman
#include "pacDot.h"
//Engine
#include "Component/Transform/huruTransform.h"
#include "Component/SpriteRenderer/huruSpriteRenderer.h"
#include "Resource/huruTexture.h"
#include "Resource/huruResources.h"


namespace pac
{
	Dot::Dot()
	{
		mTransform = AddComponent<Transform>();

		mRenderer = AddComponent<SpriteRenderer>();
		graphics::Texture* texture = Resources::Find<graphics::Texture>(L"Dot");
		mRenderer->SetTexture(texture);
	}

	Dot::~Dot()
	{

	}

	void Dot::Initialize()
	{
		GameObject::Initialize();
	}

	void Dot::Update()
	{
		GameObject::Update();
	}

	void Dot::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Dot::Collect()
	{
		mCollected = true;
	}
}