#include "Engine.hpp"
#include "Pong3DGame.hpp"

DEFINE_GAME_MODULE(Pong 3D);

GAME_API void GameMain(oeng::Engine& engine)
{
	engine.GetWorld().SpawnActor<p3d::APong3DGame>();
}
