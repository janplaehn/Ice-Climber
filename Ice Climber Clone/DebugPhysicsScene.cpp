#include "DebugPhysicsScene.h"
#include "Random.h"

void DebugPhysicsScene::Load()
{
	const int OBJECTCOUNT = 15;
	for (int i = 0; i < OBJECTCOUNT; i++)
	{
		std::shared_ptr<GameObject> go = GameObject::Create();
		go->_transform->_position = Vector2D(Random::Range(0, Screen::_width),Random::Range(0,Screen::_height));
		std::shared_ptr <SpriteRenderer> sr = go->AddComponent<SpriteRenderer>();
		sr->_sprite = Sprite::Create("Assets/Sprites/UI/gameOver.png");
		std::shared_ptr <AABBCollider> col =  go->AddComponent<AABBCollider>();
		col->ApplySpriteSize(sr->_sprite);
		std::shared_ptr <Rigidbody> rb = go->AddComponent<Rigidbody>();
		rb->_velocity = Vector2D(Random::Range(-100, 100), Random::Range(-100, 100));
	}

	std::shared_ptr<GameObject> go = GameObject::Create();
	go->_transform->_position = Vector2D::Zero();
	go->_transform->_pivot = Vector2D(0, 1);
	std::shared_ptr<AABBCollider> col = go->AddComponent<AABBCollider>();
	col->SetScale(Vector2D(Screen::_width, 16));

	go = GameObject::Create();
	go->_transform->_position = Vector2D::Zero();
	go->_transform->_pivot = Vector2D(1, 1);
	col = go->AddComponent<AABBCollider>();
	col->SetScale(Vector2D(16, Screen::_height));

	go = GameObject::Create();
	go->_transform->_position = Vector2D(Screen::_width, 0);
	go->_transform->_pivot = Vector2D(0, 1);
	col = go->AddComponent<AABBCollider>();
	col->SetScale(Vector2D(16, Screen::_height));
}