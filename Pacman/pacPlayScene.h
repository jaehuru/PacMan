#pragma once

#include "Scene/huruScene.h"
#include "Common/CommonInclude.h"

namespace pac
{
	class Player;

	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		void	Initialize() override;
		void	Update() override;
		void	LateUpdate() override;
		void	Render(HDC hdc) override;

		void	OnEnter() override;
		void	OnExit() override;

	private:
		Player* mPlayer;
	};
}
