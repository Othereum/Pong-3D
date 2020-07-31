#include "PlayerPaddle.hpp"
#include "Components/InputComponent.hpp"

namespace p3d
{
	APlayerPaddle::APlayerPaddle(World& world)
		:APaddle{world}
	{
		const auto input = AddComponent<InputComponent>();
		input->BindAxis(u8"MoveRight"sv, [this](Float f) { MoveRight(f); });
	}
}
