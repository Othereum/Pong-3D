#include "Paddle.hpp"
#include "Ball.hpp"
#include "World.hpp"
#include "Components/MeshComponent.hpp"

namespace p3d
{
	APaddle::APaddle(World& world)
		:AActor{world},
		mesh_{*AddComponent<MeshComponent>()}
	{
		SetRootComponent(&mesh_);
		mesh_.SetMesh(u8"../Engine/Assets/Cube.omesh"sv);
		mesh_.SetRelScale({10, kPaddleWidth, 30});
	}

	void APaddle::MoveRight(Float f) const noexcept
	{
		f = Clamp(f, -1, 1);
		auto pos = GetPos();
		constexpr auto limit = kYLimit - kPaddleWidth/2;
		pos[1] = Clamp(pos[1] + f * speed_ * GetWorld().GetDeltaSeconds(), -limit, limit);
		SetPos(pos);
	}
}
