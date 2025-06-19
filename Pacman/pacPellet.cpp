//Pacman
#include "pacPellet.h"
#include "pacGameManager.h"
// Engine
#include "Component/SpriteRenderer/huruSpriteRenderer.h"
#include "Resource/huruTexture.h"
#include "Helpers/huruTime.h"
#include "Resource/huruResources.h"
#include "Object/huruObject.h"

namespace pac
{
	Pellet::Pellet() :
		mRenderer(nullptr),
		mBlinkTimer(0.f),
		mBlinkInterval(0.1f)
	{

	}

	void Pellet::Initialize()
	{
		mRenderer = AddComponent<huru::SpriteRenderer>();
		mRenderer->SetTexture(GameManager::GetInstance().GetPelletTexture());
		mRenderer->SetVisible(true);

		GameObject::Initialize();
	}

	void Pellet::Update()
	{
		mBlinkTimer += huru::Time::DeltaTime();

		if (mBlinkTimer >= mBlinkInterval)
		{
			mBlinkTimer = 0.0f;
			bool currentVisible = mRenderer->IsVisible();
			mRenderer->SetVisible(!currentVisible);
		}

		GameObject::Update();
	}

	void Pellet::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Pellet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}