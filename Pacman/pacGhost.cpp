//Pacman
#include "pacGhost.h"
#include "pacGhostScript.h"
#include "pacGameManager.h"
//Engine
#include "Component/Animator/huruAnimator.h"

namespace pac
{
	Ghost::Ghost() :
		mAnimator(nullptr)
	{
		mAnimator = AddComponent<Animator>();
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