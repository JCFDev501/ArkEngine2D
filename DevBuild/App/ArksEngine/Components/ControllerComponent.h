#pragma once
#include "Component.h"


namespace ArksEngine
{
	class Input;
}

namespace ArksEngineComponents
{
	class PhysicsComponent;

	class ControllerComponent : public Component
	{
		ArksEngine::Input* m_pInput;

		ArksEngineComponents::PhysicsComponent* m_pPhysics;
	
	public:
		ControllerComponent(ArksEngine::Input* pInput);

		void Update(double deltaTime) override;

		void Init() override;

		[[nodiscard]] ArksEngine::Input* GetInput() const { return m_pInput; }
	private:
		void Process() const;
		
	};
}




