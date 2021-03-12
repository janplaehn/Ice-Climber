#pragma once
#include "Scene.h"

class PlayScene : public Scene
{
public:
	virtual void Load() override;

private:
	void LoadStageCollider(Vector2D position, Vector2D pivot, Vector2D scale);
};