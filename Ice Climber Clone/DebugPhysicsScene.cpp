#include "DebugPhysicsScene.h"
#include "Random.h"

void DebugPhysicsScene::Load()
{
	const int OBJECTCOUNT = 15;
	for (int i = 0; i < OBJECTCOUNT; i++)
	{
		GameObject* go = new GameObject();
		go->_transform->_position = Vector2D(Random::Range(0, Screen::_width),Random::Range(0,Screen::_height));
		SpriteRenderer* sr = go->AddComponent<SpriteRenderer>();
		sr->_sprite = Sprite::Create("Assets/Sprites/UI/gameOver.png");
		AABBCollider* col =  go->AddComponent<AABBCollider>();
		col->ApplySpriteSize(sr->_sprite);
		Rigidbody* rb = go->AddComponent<Rigidbody>();
		rb->_velocity = Vector2D(Random::Range(-100, 100), Random::Range(-100, 100));
	}

	GameObject* go = new GameObject();
	go->_transform->_position = Vector2D::Zero();
	go->_transform->_pivot = Vector2D(0, 1);
	AABBCollider* col = go->AddComponent<AABBCollider>();
	col->SetScale(Vector2D(Screen::_width, 16));

	go = new GameObject();
	go->_transform->_position = Vector2D::Zero();
	go->_transform->_pivot = Vector2D(1, 1);
	col = go->AddComponent<AABBCollider>();
	col->SetScale(Vector2D(16, Screen::_height));

	go = new GameObject();
	go->_transform->_position = Vector2D(Screen::_width, 0);
	go->_transform->_pivot = Vector2D(0, 1);
	col = go->AddComponent<AABBCollider>();
	col->SetScale(Vector2D(16, Screen::_height));
}