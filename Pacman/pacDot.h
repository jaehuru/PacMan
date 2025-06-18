#pragma once

#include "GameObject/huruGameObject.h"



namespace huru
{
    class Transform;
    class SpriteRenderer;
}

namespace pac
{
	class Dot : public GameObject
	{
    public:
        Dot();
        ~Dot();
        
        void        Initialize() override;
        void        Update() override;
        void        Render(HDC hdc) override;

        void        Collect();
        bool        IsCollected()               const { return mCollected; }


    private:
        Transform*          mTransform = nullptr;
        SpriteRenderer*     mRenderer = nullptr;
        bool                mCollected = false;
	};
}

