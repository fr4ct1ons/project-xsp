// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectXSPCharacter.h"
#include "Core/OthersidePreview.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectXSPGameMode.generated.h"

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

	UPROPERTY(BlueprintReadWrite)
	AActor* CornerA; //To be set in blueprint.
	
	UPROPERTY(BlueprintReadWrite)
	AActor* CornerB; //To be set in blueprint.

	UPROPERTY(BlueprintReadWrite)
	FVector OffsetVector; //To be set in blueprint.

	UPROPERTY(BlueprintReadOnly)
	AProjectXSPCharacter* Player;
	
	UPROPERTY(BlueprintReadOnly)
	AOthersidePreview* OthersidePreview;

	UFUNCTION(BlueprintPure)
	const bool CanTeleport();

public:
	AProjectXSPGameMode();
	
	UFUNCTION(BlueprintCallable)
    float GetScreenPercentage() const;

	UFUNCTION(BlueprintCallable)
	void SwapPlayerWorld();
};



