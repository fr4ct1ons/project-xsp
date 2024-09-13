// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeldInteractable.h"
#include "ProjectXSP/ProjectXSPCharacter.h"
#include "ModularHitscanWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXSP_API AModularHitscanWeapon : public AHeldInteractable
{
	GENERATED_BODY()
protected:
	virtual void Interact() override;

	bool TryGetPlayerHolder(AProjectXSPCharacter* OutPlayer);
};
