#include "pacTileScript.h"

namespace pac
{
	TileScript::TileScript()
	{

	}

	TileScript::~TileScript()
	{

	}

	void TileScript::Initialize()
	{
		Script::Initialize();
	}

	void TileScript::Update()
	{
		Script::Update();
	}

	void TileScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void TileScript::Render(HDC hdc)
	{
		Script::Render(hdc);
	}

	void TileScript::OnCollisionEnter(Collider* other)
	{
		Script::OnCollisionEnter(other);
	}

	void TileScript::OnCollisionStay(Collider* other)
	{
		Script::OnCollisionStay(other);
	}

	void TileScript::OnCollisionExit(Collider* other)
	{
		Script::OnCollisionExit(other);
	}
}
