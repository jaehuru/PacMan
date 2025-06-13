#pragma once

#include "Scene/huruScene.h"

namespace pac
{
	class Player;

	class PlayScene : public ::huru::Scene
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
