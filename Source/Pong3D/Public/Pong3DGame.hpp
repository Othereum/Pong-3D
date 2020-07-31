#pragma once
#include "Actors/Actor.hpp"
#include "Pong3D.hpp"

namespace p3d
{
	class APong3DGame : public AActor
	{
	public:
		DELETE_CPMV(APong3DGame);
		
		explicit APong3DGame(World& world);
		~APong3DGame();

		void AddPlayerScore();
		void AddAiScore();

		AActor &ball_, &player_, &ai_;
		
	protected:
		void OnBeginPlay() override;
		void OnUpdate(Float delta_seconds) override;

	private:
		void OnScoreChanged() const;
		void StartGame();
		void PrintScore() const;
		
		int player_score_ = 0, ai_score_ = 0;
	};
}
