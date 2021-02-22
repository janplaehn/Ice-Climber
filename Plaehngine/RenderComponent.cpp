
#include "renderComponent.h"
#include "component.h"
#include "GameObject.h"
#include "Transform.h"
#include "Plaehngine.h"
#include "sprite.h"
#include "Vector2D.h"

void RenderComponent::Update(float dt)
{
	if (!_gameObject->_enabled)
		return;

	if (_sprite)
		_sprite->Draw(_gameObject->_transform);
}

void RenderComponent::Destroy()
{
	if (_sprite != NULL)
		_sprite->Destroy();
	_sprite = NULL;
}