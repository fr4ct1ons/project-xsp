// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectXSPGameMode.h"
#include "ProjectXSPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectXSPGameMode::AProjectXSPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

float AProjectXSPGameMode::GetScreenPercentage() const
{
	FVector2D Result = FVector2D( 1, 1 );
	float currentRes = GSystemResolution.ResY;
	float multiplier = 1.0f;

	if(RayTracingEnabled)
	{
		return 75.0f;
	}
	
	multiplier = currentRes / static_cast<float>(DesiredHeight);

	return (1/multiplier) * 100.0f;
}
