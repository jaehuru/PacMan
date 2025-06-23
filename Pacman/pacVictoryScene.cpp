//Pacman
#include "pacVictoryScene.h"
#include "pacEnum.h"
//Engine
#include "GameObject/huruGameObject.h"
#include "Object/huruObject.h"
#include "Component/Animator/huruAnimator.h"

namespace pac
{
	VictoryScene::VictoryScene()
	{

	}

	VictoryScene::~VictoryScene()
	{

	}

	void VictoryScene::Initialize()
	{
        GameObject* victoryGO = object::Instantiate<GameObject>(ToEngineLayerType(ePacLayerType::Player), Vector2(558.f, 258.f));
        Animator* animator = victoryGO->AddComponent<Animator>();
		animator->CreateAnimationByFolder(L"VictoryAnimation", L"../Resources/img/winner", Vector2::Zero, 1.f);
        animator->PlayAnimation(L"VictoryAnimation", false);

		Scene::Initialize();
	}
}
