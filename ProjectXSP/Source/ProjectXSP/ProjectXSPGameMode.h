// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectXSPCharacter.h"
#include "Core/OthersidePreview.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectXSPCharacter.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "CommonDelegates.h"
#include "ProjectXSPGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTransitionEffectUpdate, float, Strength, float, RawStrength, bool, IsNewToOld);

UCLASS(minimalapi)
class AProjectXSPGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DesiredHeight = 360;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RayTracingEnabled = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsNewWorld = true;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> CornerA; //To be set in blueprint.
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> CornerB; //To be set in blueprint.

	UPROPERTY(BlueprintReadWrite)
	FVector OffsetVector; //To be set in blueprint.

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AProjectXSPCharacter> Player;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AOthersidePreview> OthersidePreview;

	UFUNCTION(BlueprintPure)
	bool CanTeleport() const;

	UFUNCTION(BlueprintImplementableEvent)
	void StartSwap();

public:
	AProjectXSPGameMode();
	
	UFUNCTION(BlueprintCallable)
	float GetScreenPercentage() const;

	UFUNCTION(BlueprintCallable)
	void SwapPlayerWorld();

	UFUNCTION(BlueprintCallable)
	void RequestSwapAnimation();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FTransitionEffectUpdate OnTransitionEffectUpdate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FBaseDelegate OnTransitionStarted;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FBaseDelegate OnTransitionCompleted;
};



