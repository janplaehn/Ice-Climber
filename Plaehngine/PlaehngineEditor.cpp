#include "PlaehngineEditor.h"
#include "EditorSceneView.h"
#include "Input.h"
#include "ApplicationState.h"

void PlaehngineEditor::Init()
{
	Input::WatchKey(SDL_SCANCODE_P);
	EditorSceneView::Init();
}

void PlaehngineEditor::Run()
{
	if (ApplicationState::IsRunning()) {
		return;
	}
	if (Input::GetKeyStatus(SDL_SCANCODE_P) == Input::PRESSED) {
		ApplicationState::Start();
		return;
	}
	
	EditorSceneView::Run();
}
