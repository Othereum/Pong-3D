#pragma once
#include "Paddle.hpp"

namespace p3d
{
	class AAiPaddle : public APaddle
	{
	public:
		AAiPaddle(World& world, AActor& target);

	protected:
		void OnUpdate(Float delta_seconds) override;

	private:
		AActor& target_;
	};
}
