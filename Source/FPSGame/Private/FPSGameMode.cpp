// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpoint, Actors);

		if (Actors.Num() > 0)
		{
			AActor* NewTargetViewpoint = Actors[0];
			APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());
			if (PlayerController)
			{
				PlayerController->SetViewTargetWithBlend(NewTargetViewpoint, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpoint is nullptr. Please update it in %s"), *GetName());
		}
	}

	OnMissionCompleted(InstigatorPawn);
}
