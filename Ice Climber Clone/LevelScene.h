#pragma once
#include "Scene.h"

class PlayerBehaviour;

class LevelScene : public Scene
{
public:
	virtual void Load() override;

protected:
	void LoadBackground();
	void LoadMusic();
	std::shared_ptr<PlayerBehaviour> LoadPlayer();
	void LoadTopis();
	void LoadNitpickers();
	void LoadMainStage();
	void LoadBonusStage(std::shared_ptr<PlayerBehaviour> player);
	void LoadStageCollider(Vector2D position, Vector2D pivot, Vector2D scale);
	void LoadUI(std::shared_ptr<PlayerBehaviour> player);
	void LoadEggplant(Vector2D position);
	void LoadCloud(Vector2D position, bool moveRight);
	void LoadTimer(std::shared_ptr<PlayerBehaviour> player, Vector2D position);
	void LoadCondor();
};