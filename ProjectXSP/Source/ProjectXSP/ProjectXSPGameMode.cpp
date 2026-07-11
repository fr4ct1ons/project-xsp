// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectXSPGameMode.h"

#include "ProjectXSPPlayerController.h"
#include "UserSettingsXSP.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Kismet/KismetStringLibrary.h"

AProjectXSPGameMode::AProjectXSPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AProjectXSPGameMode::BeginPlay()
{
	TObjectPtr<UUserSettingsXSP> userSettings = UUserSettingsXSP::GetUserSettingsXSP();
	UKismetInternationalizationLibrary::SetCurrentCulture(userSettings->GetCurrentCulture());
	Player = static_cast<AProjectXSPCharacter*>(UGameplayStatics::GetActorOfClass(GetWorld(), AProjectXSPCharacter::StaticClass()));
	OthersidePreview = static_cast<AOthersidePreview*>(UGameplayStatics::GetActorOfClass(GetWorld(), AOthersidePreview::StaticClass()));

	TObjectPtr<UUserSettingsXSP> settings = UUserSettingsXSP::GetUserSettingsXSP();
	bRayTracedLightingEnabled = settings->GetDefaultStylingEnabled()? false : settings->GetRayTracedLightingEnabled();
	bRayTracedReflectionsEnabled = settings->GetDefaultStylingEnabled()? false : settings->GetRayTracedReflectionsEnabled();
	settings->RefreshRenderScale();
	settings->RefreshAfterUpdatingRT();
	settings->SetAntiAliasMethod(settings->GetAntiAliasMethod());
	Super::BeginPlay();
}

bool AProjectXSPGameMode::CanTeleport() const
{
	return !OthersidePreview->IsBlocked();
}

void AProjectXSPGameMode::SwapPlayerWorld()
{
	FVector playerLocation = Player->GetActorLocation();
	Player->SetActorLocation(OthersidePreview->GetActorLocation());
	OthersidePreview->SetActorLocation(playerLocation);
	OthersidePreview->Swapped = !OthersidePreview->Swapped;
}

void AProjectXSPGameMode::RequestSwapAnimation()
{
	StartSwap();
}

float AProjectXSPGameMode::GetScreenPercentage() const
{
	TObjectPtr<UUserSettingsXSP> settings = UUserSettingsXSP::GetUserSettingsXSP();

	if (!settings->GetDefaultStylingEnabled())
	{
		return settings->GetRenderScale();
	}
	
	FVector2D Result = FVector2D( 1, 1 );
	float currentRes = GSystemResolution.ResY;
	float multiplier = 1.0f;

	if(bRayTracedLightingEnabled)
	{
		return 75.0f;
	}
	
	multiplier = currentRes / static_cast<float>(DesiredHeight);

	return (1/multiplier) * 100.0f;
}

void AProjectXSPGameMode::InvertPausedState()
{
	TObjectPtr<AProjectXSPPlayerController> pc = Cast<AProjectXSPPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	if (!pc->IsPaused())
	{
		pc->SetInputMode(FInputModeGameAndUI());
		pc->SetPause(true);
		pc->SetShowMouseCursor(true);
		OnPaused();
	}
	else
	{
		pc->SetInputMode(FInputModeGameOnly());
		pc->SetShowMouseCursor(false);
		OnUnpaused();
	}
}
