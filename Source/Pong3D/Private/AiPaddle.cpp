#include "AiPaddle.hpp"

namespace p3d
{
	AAiPaddle::AAiPaddle(World& world, AActor& target)
		:APaddle{world}, target_{target}
	{
		speed_ = 300_f;
	}

	void AAiPaddle::OnUpdate(Float)
	{
		MoveRight(Clamp(target_.GetPos()[1] - GetPos()[1], -1, 1));
	}
}
