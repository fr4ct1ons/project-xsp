// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeldInteractable.h"
#include "ProjectXSP/ProjectXSPCharacter.h"
#include "../CommonDelegates.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootingCooldown = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFullAuto = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCoolingDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReloading = false;

	virtual void BeginPlay();

	UPROPERTY(BlueprintAssignable)
	FBaseDelegate OnShoot;

	UPROPERTY(BlueprintAssignable)
	FBaseDelegate OnReloadStart;

	UPROPERTY(BlueprintAssignable)
	FBaseDelegate OnReloadComplete;
	

	UFUNCTION(BlueprintCallable)
	bool TryGetPlayerHolder(AProjectXSPCharacter*& OutPlayer);

	UFUNCTION(BlueprintCallable)
	void CompleteReload();

	
	FTimerHandle ReloadTimerHandle;

public:
	const bool CanShoot();

	const bool CanReload();

	bool TryInstantReload();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool NeedsReload();
	void TryReload();
};
