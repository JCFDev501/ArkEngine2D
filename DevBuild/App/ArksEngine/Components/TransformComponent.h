#pragma once

#include "Component.h"
#include "../Utillities/Vector2.h"

namespace ArksEngine
{
	class EventSystem;
}

using Vector2F = Vector2<float>;

namespace ArksEngineComponents
{
	class TransformComponent : public Component
	{
		Vector2F mPosition;
		Vector2F mRotation;
		Vector2F mScale;

	public:

		[[nodiscard]] Vector2F GetPosition() const { return mPosition; }
		[[nodiscard]] Vector2F GetRotation() const { return mRotation; }
		[[nodiscard]] Vector2F GetScale() const { return mScale; }

		void SetPosition(float x, float y);
		void SetRotation(float x, float y);
		void SetScale(float x, float y);

		void Init() override;
	};
}



