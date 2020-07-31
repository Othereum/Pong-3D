#pragma once
#include "Actors/Actor.hpp"
#include "Pong3D.hpp"

namespace p3d
{
	class ABall : public AActor
	{
	public:
		ABall(World& world, APong3DGame& game);

	protected:
		void OnUpdate(Float delta_seconds) override;
		
	private:
		APong3DGame& game_;
		MeshComponent& mesh_;
		Vec3 velocity_;
	};
}
