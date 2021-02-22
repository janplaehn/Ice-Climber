#include "component.h"
#include "gameObject.h"
#include "Plaehngine.h"

//Todo: Add AnimationComponent
//Todo: Add AudioSource Components


Component::Component(Plaehngine* engine, GameObject* go)
{
	_engine = engine;
	_gameObject = go;
}