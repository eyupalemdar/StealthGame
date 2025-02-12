// Copyright© 2020-2021 AlemdarLabs, All Rights Reserved

#include "FPSGameState.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionCompleted_Implementation(APawn* InstigatorPawn, bool bMissionSuccessful)
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; Iterator++)
	{
		AFPSPlayerController* FPSPlayerController = Cast<AFPSPlayerController>(Iterator->Get());
		if (FPSPlayerController)
		{
			FPSPlayerController->OnMissinCompleted(InstigatorPawn, bMissionSuccessful);

			APawn* Pawn = FPSPlayerController->GetPawn();
			if (Pawn && Pawn->IsLocallyControlled())
			{
				Pawn->DisableInput(nullptr);
			}
		}
	}
}
