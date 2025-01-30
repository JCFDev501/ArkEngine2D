#pragma once


namespace ArksEngine
{
	class GameObject;
	class Event;
}


namespace ArksEngineComponents
{
	//The Component base class, used as a foundation for all other components.
	class Component
	{
	public:
		ArksEngine::GameObject* mGameObj;

		virtual void Init() {}
		// Updates the component's state given the time passed since the last update (deltaTime).
		virtual void Update(double deltaTime) {}
		// Renders the component.
		virtual void Render(float xOffset) {}
		// Handles events with a deltaTime parameter.
		virtual void EventHandler(const ArksEngine::Event& event) {}

		virtual ~Component() = default;
	};
}


