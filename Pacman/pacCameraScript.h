#pragma once

#include "Component/Script/huruScript.h"
#include "Component/Transform/huruTransform.h"

namespace pac
{
	class CameraScript : public ::huru::Script
	{
	public:
		CameraScript();
		~CameraScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:

	};
}

