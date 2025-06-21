//Pacman
#include "pacPlayerScript.h"
#include "pacGameManager.h"
#include "pacTile.h"
#include "pacTileManager.h"
#include "pacPellet.h"
#include "pacGhost.h"
#include "pacGhostScript.h"
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
		mTransform(nullptr),
		mTileManager(nullptr),
		mCurrentTile(Vector2::Zero),
		mTargetTile(Vector2::Zero),
		mCurrentDir(Vector2::Zero),
		mNextDir(Vector2::Zero),
		mSpeed(50.f),
		mCurrentAnimName(L""),
		mPortalCoolTime(0.0f),
		mPortals{ }
	{

	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();

		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
			if (mAnimator)
			{
				mAnimator->CreateAnimationByFolder(L"Move_Left", L"../Resources/img/pacman/left", Vector2::Zero, 0.1f);
				mAnimator->CreateAnimationByFolder(L"Move_Down", L"../Resources/img/pacman/down", Vector2::Zero, 0.1f);
				mAnimator->CreateAnimationByFolder(L"Move_Right", L"../Resources/img/pacman/right", Vector2::Zero, 0.1f);
				mAnimator->CreateAnimationByFolder(L"Move_Up", L"../Resources/img/pacman/up", Vector2::Zero, 0.1f);

				mAnimator->PlayAnimation(L"Move_Left", true);
				mCurrentAnimName = L"Move_Left";
			}
		}

		mTileManager = GameManager::GetInstance().GetTileManager();
		mPortals = mTileManager->GetPortalTiles();
	}

	void PlayerScript::Update()
	{
		if (mState == eState::Dead)
		{
			Dead();
			return;
		}

		HandleInput();
		ProcessTileNavigation();
		CollectedItem();
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
		if (Input::GetKey(eKeyCode::Up))			mNextDir = DIR_UP;
		else if (Input::GetKey(eKeyCode::Down))		mNextDir = DIR_DOWN;
		else if (Input::GetKey(eKeyCode::Left))		mNextDir = DIR_LEFT;
		else if (Input::GetKey(eKeyCode::Right))	mNextDir = DIR_RIGHT;
	}

	bool PlayerScript::CanMove(Vector2 from, Vector2 dir)
	{
		Vector2 to = from + dir;

		if (to.x < 0 || to.y < 0)	return false;

		int idxX = static_cast<int>(to.x);
		int idxY = static_cast<int>(to.y);
		int index = define::GetLinearIndex(idxX, idxY);

		auto& map = mTileManager->GetTileMap();

		wchar_t buf[128];
		swprintf(buf, 128,
			L"CanMove: from(%.0f,%.0f)->to(%.0f,%.0f) idx(%d,%d) tileIndex=%d\n",
			from.x, from.y, to.x, to.y, idxX, idxY, index);
		OutputDebugString(buf);

		if (index < 0 || index >= static_cast<int>(map.size()))
			return false;

		Tile* tile = map[index];
		if (!tile)	return false;

		return tile->GetTileType() != Tile::eTileType::Wall && tile->GetTileType() != Tile::eTileType::Jail;
	}

	void PlayerScript::Dead()
	{

	}

	void PlayerScript::ProcessTileNavigation()
	{
		Vector2 pos = mTransform->GetPosition();
		int idxX = static_cast<int>(pos.x / Tile::Size.x);
		int idxY = static_cast<int>(pos.y / Tile::Size.y);
		mCurrentTile = Vector2((float)idxX, (float)idxY);
		Vector2 center = SnapToTileCenter(mCurrentTile);

		if ((center - pos).length() < 0.1f)
		{
			mTransform->SetPosition(center);

			if (mPortalCoolTime <= 0.0f)
			{
				if (IsOnPortalTile())
				{
					TeleportToOtherPortal();
					mPortalCoolTime = 0.08f;
					return;
				}
			}
			else
				mPortalCoolTime -= Time::DeltaTime();


			if (CanMove(mCurrentTile, mNextDir))
				mCurrentDir = mNextDir;

			if (CanMove(mCurrentTile, mCurrentDir))
				mTargetTile = mCurrentTile + mCurrentDir;
			else
				mCurrentDir = Vector2::Zero;
		}

		if (mCurrentDir == Vector2::Zero)
			return;

		Vector2 move = mCurrentDir * mSpeed * Time::DeltaTime();
		Vector2 nextPos = mTransform->GetPosition() + move;
		Vector2 toCenter = center - nextPos;

		mTransform->SetPosition(
			((mCurrentDir.x != 0 && fabs(toCenter.x) < fabs(move.x)) || 
				(mCurrentDir.y != 0 && fabs(toCenter.y) < fabs(move.y)))
			? center : nextPos);

		UpdateAnimation();
	}

	Vector2 PlayerScript::SnapToTileCenter(Vector2 tilePos)
	{
		return Vector2
		(
			tilePos.x * Tile::Size.x + Tile::Size.x * 0.5f,
			tilePos.y * Tile::Size.y + Tile::Size.y * 0.5f
		);
	}

	bool PlayerScript::IsOnPortalTile()
	{
		for (Tile* portal : mPortals)
			if (portal->GetIndex() == mCurrentTile)
				return true;
		return false;
	}

	void PlayerScript::TeleportToOtherPortal()
	{
		if (mPortals.size() != 2) return;

		// 현재 포탈 인덱스 찾기
		int current = (mPortals[0]->GetIndex() == mCurrentTile) ? 0 : 1;
		int other = 1 - current;

		// 반대 포탈 타일의 중앙 위치로 순간이동
		Vector2 targetTile = mPortals[other]->GetIndex();
		Vector2 targetCenter = SnapToTileCenter(targetTile);
		mTransform->SetPosition(targetCenter);
	}

	void PlayerScript::UpdateAnimation()
	{
		wstring newAnim;
		if (mCurrentDir == DIR_RIGHT)      newAnim = L"Move_Right";
		else if (mCurrentDir == DIR_LEFT)  newAnim = L"Move_Left";
		else if (mCurrentDir == DIR_UP)    newAnim = L"Move_Up";
		else if (mCurrentDir == DIR_DOWN)  newAnim = L"Move_Down";

		if (!newAnim.empty() && newAnim != mCurrentAnimName && mAnimator)
		{
			mAnimator->PlayAnimation(newAnim, true);
			mCurrentAnimName = newAnim;
		}
	}

	void PlayerScript::CollectedItem()
	{
		CollectedDot();
		CollectedPellet();
	}

	void PlayerScript::CollectedDot()
	{
		Vector2 playerPos = mTransform->GetPosition();
		int idxX = static_cast<int>(playerPos.x / Tile::Size.x);
		int idxY = static_cast<int>(playerPos.y / Tile::Size.y);

		Tile* tile = mTileManager->GetTile(idxX, idxY);
		if (tile && tile->GetTileType() == Tile::eTileType::Path && tile->HasDot())
		{
			tile->SetHasDot(false);  
			// TODO: 점수 올리기, 사운드 재생 등 추가 가능
		}
	}

	void PlayerScript::CollectedPellet()
	{
		Vector2 playerPos = mTransform->GetPosition();
		int idxX = static_cast<int>(playerPos.x / Tile::Size.x);
		int idxY = static_cast<int>(playerPos.y / Tile::Size.y);

		Tile* tile = mTileManager->GetTile(idxX, idxY);
		
		Pellet* pellet = tile->FindChildOfType<Pellet>();
		if (pellet)
		{
			object::Destroy(pellet);

			const vector<Ghost*> ghosts = GameManager::GetInstance().GetGhosts();
			for (auto ghost : ghosts)
			{
				if (ghost)
				{
					GhostScript* ghostscript = ghost->GetComponent<GhostScript>();
					if (ghostscript)
						ghostscript->BeginNerf();
				}
			}
		}

		
	}
}