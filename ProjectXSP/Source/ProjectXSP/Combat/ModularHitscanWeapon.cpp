// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularHitscanWeapon.h"

#include "Camera/CameraComponent.h"

void AModularHitscanWeapon::Interact()
{
	FHitResult HitResult;
	
	AProjectXSPCharacter* outPlayer = nullptr;
	FVector OriginPoint;
	FVector EndPoint;
	
	if(TryGetPlayerHolder(outPlayer))
	{

		if(outPlayer != nullptr)
		{
			OriginPoint = outPlayer->GetFirstPersonCameraComponent()->GetComponentLocation();
			EndPoint = outPlayer->GetFirstPersonCameraComponent()->GetComponentLocation() + outPlayer->GetFirstPersonCameraComponent()->GetForwardVector();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Failed to get player.");
		}
	}
	else
	{
		OriginPoint = GetActorLocation();
		EndPoint = GetActorLocation() + GetActorForwardVector();
	}
	
	GetWorld()->LineTraceSingleByChannel(HitResult, OriginPoint, EndPoint, ECC_Visibility );
	if(HitResult.bBlockingHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Hit Point:" + HitResult.GetActor()->GetName());
	}

	Super::Interact();
}

bool AModularHitscanWeapon::TryGetPlayerHolder(AProjectXSPCharacter* OutPlayer)
{
	OutPlayer = Cast<AProjectXSPCharacter>(Holder);

	
	if(OutPlayer == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Failure getting player!");
		return false;
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "Got player!");

	return true;
}


