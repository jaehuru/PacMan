//Pacman
#include "pacPellet.h"
//Engine
#include "Component/SpriteRenderer/huruSpriteRenderer.h"


namespace pac
{
	Pellet::Pellet(Vector2 pos)
	{

	}

	void Pellet::Initialize()
	{
		GameObject::Initialize();
	}

	void Pellet::Update()
	{
		GameObject::Update();
	}

	void Pellet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Pellet::Collect()
	{
	}
}
