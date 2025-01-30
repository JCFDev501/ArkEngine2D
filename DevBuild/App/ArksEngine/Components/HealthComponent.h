#pragma once
#include "Component.h"

namespace ArksEngine
{
	class Core;
}

// Very simple Health component
namespace ArksEngineComponents
{
	class HealthComponent : public Component
	{
		ArksEngine::Core* m_pOwner;

		float m_maxHp = 100.0f;
		float m_minHp = 0.0f;
		float mHp = m_maxHp;

		bool m_isDead = false;

	public:
		HealthComponent(ArksEngine::Core* pOwner, float max, float min);

		void Init() override;

		void Update(double deltaTime) override;


		void heal(float amount) { mHp += amount; }
		void damage(float amount) { mHp -= amount; }

		void setMaxHp(float maxHp) { m_maxHp = maxHp; }
		void setMinHp(float minHp) { m_minHp = minHp; }

		[[nodiscard]] float getHp() const { return mHp; }
		[[nodiscard]] float getMaxHp() const { return m_maxHp; }
		[[nodiscard]] float getMinHp() const { return m_minHp; }
		[[nodiscard]] bool isDead() const { return m_isDead; }
	};

}
