#include "Settings.h"
#include "Engine.h"


void Settings::ToggleFullscreen() {
    isFullscreen = !isFullscreen;
    Engine::GetInstance()->getSceneModule()->SetPendingFullscreen(isFullscreen);
}