// Fill out your copyright notice in the Description page of Project Settings.


#include "HeldInteractable.h"

// Sets default values
AHeldInteractable::AHeldInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AHeldInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHeldInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AHeldInteractable::Interact()
{
	OnInteract();

	
}


void AHeldInteractable::SetHolder(AActor* holder, FName socket)
{
	if(IsValid(holder))
	{
		AttachToActor(holder, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), socket);
		Holder = holder;
		HolderSocket = socket;
	}
	
	Holder = holder;
}

void AHeldInteractable::SetHolder(AActor* holder, USceneComponent* holderComponent)
{
	if(IsValid(holder))
	{
		Holder = holder;
		HolderComponent = holderComponent;
		AttachToComponent(HolderComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}


