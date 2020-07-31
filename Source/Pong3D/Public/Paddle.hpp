#pragma once
#include "Actors/Actor.hpp"
#include "Pong3D.hpp"

namespace p3d
{
	class APaddle : public AActor
	{
	public:
		explicit APaddle(World& world);

	protected:
		void MoveRight(Float f) const noexcept;
		Float speed_ = 300_f;
		
	private:
		MeshComponent& mesh_;
	};
}
