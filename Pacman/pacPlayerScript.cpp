//Pacman
#include "pacPlayerScript.h"
#include "pacGameManager.h"
#include "pacTile.h"
//Engine
#include "Helpers/huruInput.h"
#include "Component/Transform/huruTransform.h"
#include "Helpers/huruTime.h"
#include "Component/Camera/huruCamera.h"
#include "Renderer/huruRenderer.h"
#include "Component/huruComponent.h"
#include "Component/Animator/huruAnimator.h"
#include "Resource/huruResources.h"



namespace pac
{
	PlayerScript::PlayerScript() :
		mState(PlayerScript::eState::Alive),
		mAnimator(nullptr),
		mCurrentTile(Vector2::Zero),
		mTargetTile(Vector2::Zero),
		mCurrentDir(Vector2::Zero),
		mNextDir(Vector2::Zero),
		mSpeed(80.f),
		mRotationAngle(0.f)
	{

	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initialize()
	{
		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
			if (mAnimator)
			{
				mAnimator->CreateAnimationByFolder(L"Move", L"../Resources/img/pacman", Vector2::Zero, 0.1f);
				mAnimator->PlayAnimation(L"Move", true);
			}
		}

		Script::Initialize();
	}

	void PlayerScript::Update()
	{
		HandleInput();

		if (mState == eState::Dead)
		{
			Dead();
			return;
		}

		Transform* tf = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tf->GetPosition();

		// 현재 위치의 타일 좌표 계산
		int idxX = static_cast<int>(pos.x / Tile::Size.x);
		int idxY = static_cast<int>(pos.y / Tile::Size.y);
		mCurrentTile = Vector2((float)idxX, (float)idxY);

		// 타일 중심과 거리 계산
		Vector2 center = SnapToTileCenter(mCurrentTile);
		Vector2 toCenter = center - pos;

		if (toCenter.length() < 0.1f)
		{
			tf->SetPosition(center);

			// 이동 가능하면 방향 전환
			if (CanMove(mCurrentTile, mNextDir))
			{
				mCurrentDir = mNextDir;
			}

			// 현재 방향으로 이동 가능한 경우, 타겟 타일 갱신
			if (CanMove(mCurrentTile, mCurrentDir))
			{
				mTargetTile = mCurrentTile + mCurrentDir;
			}
			else
			{
				mCurrentDir = Vector2::Zero;
			}
		}

		// 방향에 따른 회전값 설정 (Transform에 세팅)
		if (mCurrentDir == Vector2(1, 0))        // 오른쪽
			mRotationAngle = 0.0f;
		else if (mCurrentDir == Vector2(-1, 0))  // 왼쪽
			mRotationAngle = 180.0f;
		else if (mCurrentDir == Vector2(0, -1))  // 위쪽
			mRotationAngle = -90.0f;
		else if (mCurrentDir == Vector2(0, 1))   // 아래쪽
			mRotationAngle = 90.0f;

		tf->SetRotation(mRotationAngle);

		// 실제 이동
		if (mCurrentDir != Vector2::Zero)
		{
			Vector2 move = mCurrentDir * mSpeed * Time::DeltaTime();
			tf->SetPosition(tf->GetPosition() + move);
		}

		Script::Update();
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
		if (Input::GetKey(eKeyCode::Up))
			mNextDir = DIR_UP;
		else if (Input::GetKey(eKeyCode::Down))
			mNextDir = DIR_DOWN;
		else if (Input::GetKey(eKeyCode::Left))
			mNextDir = DIR_LEFT;
		else if (Input::GetKey(eKeyCode::Right))
			mNextDir = DIR_RIGHT;
	}

	void PlayerScript::Dead()
	{

	}

	Vector2 PlayerScript::SnapToTileCenter(Vector2 tilePos)
	{
		{
			return Vector2(
				tilePos.x * Tile::Size.x + Tile::Size.x * 0.5f,
				tilePos.y * Tile::Size.y + Tile::Size.y * 0.5f
			);
		}
	}

	bool PlayerScript::CanMove(Vector2 from, Vector2 dir)
	{
		Vector2 to = from + dir;

		if (to.x < 0 || to.y < 0)
			return false;

		int idxX = static_cast<int>(to.x);
		int idxY = static_cast<int>(to.y);
		int index = define::GetLinearIndex(idxX, idxY);

		auto& map = GameManager::GetInstance().GetTileMap();
		if (index < 0 || index >= static_cast<int>(map.size()))
			return false;

		Tile* tile = map[index];
		if (tile == nullptr)
			return false;

		return tile->GetTileType() == Tile::eTileType::Path;
	}
}

