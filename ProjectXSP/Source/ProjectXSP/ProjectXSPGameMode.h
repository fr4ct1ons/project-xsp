// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectXSPGameMode.generated.h"

UCLASS(minimalapi)
class AProjectXSPGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
   	int32 desiredHeight = 360;

public:
	AProjectXSPGameMode();
	
	UFUNCTION(BlueprintCallable)
    float GetScreenPercentage() const;
};



