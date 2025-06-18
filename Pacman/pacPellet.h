#pragma once

#include "GameObject/huruGameObject.h"

namespace pac
{
	class Pellet : public GameObject
	{
    public:
        Pellet() = default;
        Pellet(Vector2 pos);
        
        void        Initialize() override;
        void        Update() override;
        void        Render(HDC hdc) override;
        
        void        Collect();
        bool        IsCollected()   const { return mCollected; }

    private:
        bool        mCollected = false;
        float       mBlinkTimer = 0.0f;
	};
}

