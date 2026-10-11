// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerHUDSubsystem.generated.h"

// Use this for updating stat bars (i.e health, stamina & energy)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentStatUpdatedSignature, float, newStat, float, maxStat);

/**
 * 
 */
UCLASS()
class PROJECTXSP_API UPlayerHUDSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnCurrentStatUpdatedSignature OnHealthUpdated;
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnCurrentStatUpdatedSignature OnStaminaUpdated;
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnCurrentStatUpdatedSignature OnEnergyUpdated;
};
