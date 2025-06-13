//Pacman
#include "pacCameraScript.h"
//Engine
#include "Component/Transform/huruTransform.h"
#include "GameObject/huruGameObject.h"
#include "Helpers/huruInput.h"
#include "Helpers/huruTime.h"


namespace pac
{
	CameraScript::CameraScript()
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initialize()
	{
	}

	void CameraScript::Update()
	{
		::huru::Transform* tr = GetOwner()->GetComponent<::huru::Transform>();
		::huru::math::Vector2 pos = tr->GetPosition();

		if (::huru::Input::GetKey(::huru::eKeyCode::Right))
		{
			pos.x += 100.0f * ::huru::Time::DeltaTime();
		}
		if (::huru::Input::GetKey(::huru::eKeyCode::Left))
		{
			pos.x -= 100.0f * ::huru::Time::DeltaTime();
		}
		if (::huru::Input::GetKey(::huru::eKeyCode::Up))
		{
			pos.y -= 100.0f * ::huru::Time::DeltaTime();
		}
		if (::huru::Input::GetKey(::huru::eKeyCode::Down))
		{
			pos.y += 100.0f * ::huru::Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	void CameraScript::LateUpdate()
	{
	}

	void CameraScript::Render(HDC hdc)
	{
	}
}
