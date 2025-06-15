//Pacman
#include "pacPlayerScript.h"
#include "pacGameManager.h"
//Engine
#include "Helpers/huruInput.h"
#include "Component/Transform/huruTransform.h"
#include "Helpers/huruTime.h"
#include "GameObject/huruGameObject.h"
#include "Component/Animator/huruAnimator.h"
#include "Object/huruObject.h"
#include "Resource/huruResources.h"
#include "Component/Collider/huruCollider.h"
#include "Component/Rigidbody/huruRigidbody.h"
#include "Collision/huruCollisionManager.h"



namespace pac
{
	PlayerScript::PlayerScript() :
		mState(PlayerScript::eState::Alive),
		mAnimator(nullptr),
		mCurrentTile(Vector2::Zero),
		mTargetTile(Vector2::Zero),
		mCurrentDir(Vector2::Zero),
		mNextDir(Vector2::Zero),
		mSpeed(3.f)
	{

	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initialize()
	{

	}

	void PlayerScript::Update()
	{
		if (mAnimator == nullptr)
			mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mState)
		{
		case eState::Alive:
			HandleInput();
			break;
		case eState::Dead:
			Dead();
			break;
		default:
			break;
		}
	}

	void PlayerScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void PlayerScript::Render(HDC hdc)
	{
		Script::Render(hdc);
	}

	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		Script::OnCollisionEnter(other);
	}

	void PlayerScript::OnCollisionStay(Collider* other)
	{
		Script::OnCollisionStay(other);
	}

	void PlayerScript::OnCollisionExit(Collider* other)
	{
		Script::OnCollisionExit(other);
	}

	void PlayerScript::HandleInput()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();

		if (Input::GetKeyDown(eKeyCode::Up))    mNextDir = { 0, -1 };
		if (Input::GetKeyDown(eKeyCode::Down))  mNextDir = { 0, 1 };
		if (Input::GetKeyDown(eKeyCode::Left))  mNextDir = { -1, 0 };
		if (Input::GetKeyDown(eKeyCode::Right)) mNextDir = { 1, 0 };
	}

	void PlayerScript::Dead()
	{

	}

	bool PlayerScript::CanMove(Vector2 from, Vector2 dir)
	{
		return false;
	}
}

