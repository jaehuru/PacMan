#pragma once

#include "Scene/huruScene.h"


namespace pac
{
	class PlayScene : public Scene
	{
	public:
		PlayScene() = default;
		~PlayScene() = default;

		void	Initialize() override;
		void	Update() override;

	private:
		int		mLife = 0;
	};
}
