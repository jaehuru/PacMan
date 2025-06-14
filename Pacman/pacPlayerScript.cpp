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
#include "pacTileScript.h"



namespace pac
{
	PlayerScript::PlayerScript() :
		mState(PlayerScript::eState::Alive),
		mAnimator(nullptr)
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

		mPrevPosition = GetOwner()->GetComponent<Transform>()->GetPosition();

		switch (mState)
		{
		case eState::Alive:
			move();
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
		if (other->GetOwner()->GetLayerType() == ToEngineLayerType(ePacLayerType::Tile))
		{
			GetOwner()->GetComponent<Transform>()->SetPosition(mPrevPosition);
		}

		Script::OnCollisionEnter(other);
	}

	void PlayerScript::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == ToEngineLayerType(ePacLayerType::Tile))
		{
			GetOwner()->GetComponent<Transform>()->SetPosition(mPrevPosition);
		}

		Script::OnCollisionStay(other);
	}

	void PlayerScript::OnCollisionExit(Collider* other)
	{
		Script::OnCollisionExit(other);
	}

	void PlayerScript::move()
	{
		auto transform = GetOwner()->GetComponent<Transform>();
		Vector2 direction = { 0.f, 0.f };

		if (Input::GetKey(eKeyCode::Left))
			direction.x -= 1.f;
		if (Input::GetKey(eKeyCode::Right))
			direction.x += 1.f;
		if (Input::GetKey(eKeyCode::Up))
			direction.y -= 1.f;
		if (Input::GetKey(eKeyCode::Down))
			direction.y += 1.f;

		if (direction.x != 0.f || direction.y != 0.f)
		{
			// normalize direction
			direction = direction.normalize();

			float speed = 60.f; // 필요하면 멤버 변수로 분리
			transform->SetPosition(transform->GetPosition() + direction * speed * Time::DeltaTime());
		}
	}

	void PlayerScript::Dead()
	{

	}
}

