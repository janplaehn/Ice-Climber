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
	PlayerBehaviour* LoadPlayer();
	void LoadTopis();
	void LoadNitpickers();
	void LoadMainStage();
	void LoadBonusStage(PlayerBehaviour* player);
	void LoadStageCollider(Vector2D position, Vector2D pivot, Vector2D scale);
	void LoadUI(PlayerBehaviour* player);
	void LoadEggplant(Vector2D position);
	void LoadCloud(Vector2D position, bool moveRight);
	void LoadTimer(PlayerBehaviour* player, Vector2D position);
	void LoadCondor();
};