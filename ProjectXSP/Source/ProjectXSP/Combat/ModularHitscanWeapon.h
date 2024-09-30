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

	bool TryGetPlayerHolder(AProjectXSPCharacter*& OutPlayer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Range = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MagazineCapacity = 7;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int CarriedAmmoCapacity = 35;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentMagazine = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentCarriedAmmo = 0;

	virtual void BeginPlay();

public:
	const bool CanShoot();

	const bool CanReload();

	bool TryReload();
};
