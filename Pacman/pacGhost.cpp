//Pacman
#include "pacGhost.h"
#include "pacGhostScript.h"
#include "pacGameManager.h"
//Engine
#include "Component/Animator/huruAnimator.h"
#include "Component/SpriteRenderer/huruSpriteRenderer.h"

namespace pac
{
	Ghost::Ghost() :
		mAnimator(nullptr),
		mSpriteRenderer(nullptr)
	{
		mAnimator = AddComponent<Animator>();
		//mSpriteRenderer = AddComponent<SpriteRenderer>();
		SetLayerType(ToEngineLayerType(ePacLayerType::Ghost));
		GameManager::GetInstance().RegisterGhost(this);
	}

	Ghost::~Ghost()
	{

	}

	void Ghost::Initialize()
	{
		GameObject::Initialize();
	}

	void Ghost::Update()
	{
		GameObject::Update();
	}

	void Ghost::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Ghost::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}