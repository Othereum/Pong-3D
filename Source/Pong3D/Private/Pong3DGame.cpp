#include "Pong3DGame.hpp"
#include "Engine.hpp"
#include "Ball.hpp"
#include "PlayerPaddle.hpp"
#include "AiPaddle.hpp"
#include "Debug.hpp"
#include "Log.hpp"
#include "World.hpp"
#include "Actors/DirLight.hpp"
#include "Actors/SkyLight.hpp"
#include "Camera/CameraActor.hpp"
#include "Actors/MeshActor.hpp"

namespace p3d
{
	[[nodiscard]] static auto SpawnWall(World& world)
	{
		auto wall = world.SpawnActor<AMeshActor>();
		wall->SetMesh(u8"../Engine/Assets/Plane.omesh"sv);
		return wall;
	}
	
	APong3DGame::APong3DGame(World& world)
		:AActor{world},
		ball_{*GetWorld().SpawnActor<ABall>(*this)},
		player_{*GetWorld().SpawnActor<APlayerPaddle>()},
		ai_{*GetWorld().SpawnActor<AAiPaddle>(ball_)}
	{
		world.SpawnActor<ASkyLight>();
		
		const auto sun = world.SpawnActor<ADirLight>();
		sun->SetRot(Quat{UVec3::right, 70_deg} * Quat{UVec3::up, 30_deg});

		constexpr auto wall_x_scale = kXLimit * 2 / 100;

		auto wall = SpawnWall(world);
		wall->SetTrsf({{0, -kYLimit}, {UVec3::forward, 90_deg}, {wall_x_scale, 1}});
		
		wall = SpawnWall(world);
		wall->SetTrsf({{0, kYLimit}, {UVec3::forward, -90_deg}, {wall_x_scale, 1}});

		const auto cam = GetWorld().SpawnActor<ACameraActor>();
		cam->SetTrsf({{-300, 0, 400}, {UVec3::right, 60_deg}});

		player_.SetPos({-kXLimit, 0, 0});
		ai_.SetPos({kXLimit, 0, 0});

		OnScoreChanged();
	}

	APong3DGame::~APong3DGame()
	{
		PrintScore();
	}

	void APong3DGame::AddPlayerScore()
	{
		++player_score_;
		OnScoreChanged();
	}

	void APong3DGame::AddAiScore()
	{
		++ai_score_;
		OnScoreChanged();
	}

	void APong3DGame::OnBeginPlay()
	{
		StartGame();
	}

	void APong3DGame::OnUpdate(Float /*delta_seconds*/)
	{
	}

	void APong3DGame::OnScoreChanged() const
	{
		Engine::Get().GetRenderer().GetWindow().SetTitle(Format(u8"Pong 3D [{}:{}]"sv, player_score_, ai_score_));
	}

	void APong3DGame::StartGame()
	{
	}

	void APong3DGame::PrintScore() const
	{
		log::Info(u8"My score: {}, AI's score: {}"sv, player_score_, ai_score_);
	}
}
