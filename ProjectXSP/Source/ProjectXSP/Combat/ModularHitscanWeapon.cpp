// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularHitscanWeapon.h"

#include "Camera/CameraComponent.h"

void AModularHitscanWeapon::Interact()
{
	if(!CanShoot())
	{
		return;
		/*
		if(!TryInstantReload())
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Not Reloading.");
			return;
		}
		*/
	}
	
	FHitResult HitResult;
	
	AProjectXSPCharacter* outPlayer = nullptr;
	FVector OriginPoint;
	FVector EndPoint;
	
	if(TryGetPlayerHolder(outPlayer))
	{

		if(outPlayer != nullptr)
		{
			OriginPoint = outPlayer->GetFirstPersonCameraComponent()->GetComponentLocation();
			EndPoint = outPlayer->GetFirstPersonCameraComponent()->GetComponentLocation() +
				(outPlayer->GetFirstPersonCameraComponent()->GetForwardVector() * Range);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Error getting player.");
			return;
		}
	}
	else
	{
		OriginPoint = GetActorLocation();
		EndPoint = GetActorLocation() + (GetActorForwardVector() * Range);
	}
	
	GetWorld()->LineTraceSingleByChannel(HitResult, OriginPoint, EndPoint * Range, ECC_Visibility );

	if (FMath::IsNearlyZero(ShootingCooldown))
	{
		FTimerHandle TimerHandle;
		IsCoolingDown = true;
		GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			IsCoolingDown = false;
		}), ShootingCooldown, false);
	}

	CurrentMagazine--;
	OnShoot.Broadcast();
	
	if (NeedsReload())
	{
		TryReload();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Reload is needed - Bullets left:" + CurrentCarriedAmmo);
	}
	
	if(HitResult.bBlockingHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Hit Point:" + HitResult.GetActor()->GetName());
	}

	Super::Interact();
}

bool AModularHitscanWeapon::TryGetPlayerHolder(AProjectXSPCharacter*& OutPlayer)
{
	OutPlayer = static_cast<AProjectXSPCharacter*>(Holder);

	
	if(OutPlayer == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Failure getting player!");
		return false;
	}
	
	return true;
}

void AModularHitscanWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentMagazine = MagazineCapacity;
	CurrentCarriedAmmo = CarriedAmmoCapacity;
}

const bool AModularHitscanWeapon::CanShoot()
{
	if (IsCoolingDown || IsReloading)
	{
		return false;
	}
	
	if(CurrentMagazine <= 0 && MagazineCapacity > 0) 
	{
		return false;
	}

	return true;
	
}

const bool AModularHitscanWeapon::CanReload()
{
	return CurrentMagazine < MagazineCapacity;
}

bool AModularHitscanWeapon::TryInstantReload()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Reloading...");
	
	if(CarriedAmmoCapacity <= 0)
	{
		CurrentMagazine = MagazineCapacity;
		return true;
	}
	
	if(CurrentCarriedAmmo <= 0)
	{
		return false;
	}
	
	int overDrawn = 0;
	CurrentCarriedAmmo -= MagazineCapacity;
	if(CurrentCarriedAmmo < 0) //Ammo was overdrawn
	{
		overDrawn =  FMath::Abs(CurrentCarriedAmmo);
		CurrentCarriedAmmo = 0;
	}
	CurrentMagazine = MagazineCapacity - overDrawn;

	return true;
}

void AModularHitscanWeapon::CompleteReload()
{
	int overDrawn = 0;
	CurrentCarriedAmmo -= MagazineCapacity;
	if(CurrentCarriedAmmo < 0) //Ammo was overdrawn
	{
		overDrawn =  FMath::Abs(CurrentCarriedAmmo);
		CurrentCarriedAmmo = 0;
	}
	CurrentMagazine = MagazineCapacity - overDrawn;

	OnReloadComplete.Broadcast();
}

bool AModularHitscanWeapon::NeedsReload()
{
	if(CurrentMagazine <= 0) 
	{
		return true;
	}

	return false;
}

void AModularHitscanWeapon::TryReload()
{
	if (CurrentMagazine >= MagazineCapacity || CurrentCarriedAmmo <= 0)
	{
		return;
	}
	
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		OnReloadStart.Broadcast();
	}), 0.1f, false);
}
