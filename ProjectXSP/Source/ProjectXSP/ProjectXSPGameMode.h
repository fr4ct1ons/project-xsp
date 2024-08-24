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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
   	int32 DesiredHeight = 360;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RayTracingEnabled = false;

public:
	AProjectXSPGameMode();
	
	UFUNCTION(BlueprintCallable)
    float GetScreenPercentage() const;
};



