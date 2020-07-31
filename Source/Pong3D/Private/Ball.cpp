#include "Ball.hpp"
#include "Pong3DGame.hpp"
#include "Components/MeshComponent.hpp"
#include "Components/SphereComponent.hpp"
#include "World.hpp"

namespace p3d
{
	constexpr auto kXSpeed = 400_f;
	constexpr auto kYSpeed = 400_f;
	constexpr auto kSize = 10_f;
	
	ABall::ABall(World& world, APong3DGame& game)
		:AActor{world},
		game_{game},
		mesh_{*AddComponent<MeshComponent>()},
		velocity_{kXSpeed}
	{
		SetRootComponent(&mesh_);
		mesh_.SetMesh(u8"../Engine/Assets/Cube.omesh"sv);
		mesh_.SetRelScale({All{}, kSize});
	}

	void ABall::OnUpdate(Float delta_seconds)
	{
		auto get_new_pos = [&] { return GetPos() + velocity_ * delta_seconds; };
		auto invert_x = [&]
		{
			velocity_[0] = -velocity_[0];
			velocity_[1] = Rand(-kYSpeed, kYSpeed);
		};
		auto pause = [&]
		{
			SetUpdateEnabled(false);
			GetWorld().GetTimerManager().SetTimer(0.5_f, [&] { SetUpdateEnabled(true); });
			SetPos({});
		};
		
		const auto new_pos = get_new_pos();
		const auto x_limit = kXLimit - kSize;
		const auto min_dist = (kPaddleWidth + kSize) / 2;
		constexpr auto reset_offset = 100_f;
		
		if (new_pos[0] > x_limit)
		{
			if (Abs(new_pos[1] - game_.ai_.GetPos()[1]) > min_dist)
			{
				game_.AddPlayerScore();
				pause();
				SetPos({reset_offset, 0});
			}
			invert_x();
		}
		else if (new_pos[0] < -x_limit)
		{
			if (Abs(new_pos[1] - game_.player_.GetPos()[1]) > min_dist)
			{
				game_.AddAiScore();
				pause();
				SetPos({-reset_offset, 0});
			}
			invert_x();
		}
		
		const auto y_limit = kYLimit - kSize;
		if (Abs(new_pos[1]) > y_limit) velocity_[1] = -velocity_[1];
		
		SetPos(get_new_pos());
	}
}
