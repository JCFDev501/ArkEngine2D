#pragma once
#include "../ArksEngine.h"
#include "../Game.h"


class GameArea : public ArksEngine::Scene
{
	Game* m_pGame = nullptr;

public:
	GameArea(Game* pOwner);
	~GameArea() = default;


	/**
	 * \brief Enters our scene
	 */
	void Enter() override;


	/**
	 * \brief Exits our scene
	 */
	void Exit() override;

	void SpawnEnemyOutsideScreen(const ArksEngine::GameObject* enemy) const;

};

