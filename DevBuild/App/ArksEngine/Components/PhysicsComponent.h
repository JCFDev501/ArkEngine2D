#pragma once
#include "Component.h"
#include "../Utillities/Vector2.h"


namespace ArksEngine
{
	class Event;
	class EventSystem;
	class Core;
}

namespace ArksEngineComponents
{
	class TransformComponent;

	class PhysicsComponent : public Component
	{
		double mSpeed{};

		ArksEngineComponents::TransformComponent* m_pTransform{};
	
		Vector2<int> mDirection;
	
		Vector2<float> mNewPos{};

		bool mFront;

		// This is a Ptr to the Core
		ArksEngine::Core* m_pOwner;

	
	public:
	
		PhysicsComponent(ArksEngine::Core* pOwner);
		~PhysicsComponent() = default;
	
		[[nodiscard]] double GetSpeed() const { return mSpeed; }
		void SetSpeed(double speed) { mSpeed = speed;}

		[[nodiscard]] Vector2<int> GetDirection() const { return mDirection; }
		void SetDirection(float x, float y);

		void Update(double deltaTime) override;

		void Init() override;

		void EventHandler(const ArksEngine::Event& event) override;

		[[nodiscard]] bool GetFront() const { return mFront; }
	

	private:
		void Move(double deltaTime);
	};
}




