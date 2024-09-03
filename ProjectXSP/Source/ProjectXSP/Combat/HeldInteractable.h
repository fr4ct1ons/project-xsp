// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeldInteractable.generated.h"

UCLASS()
class PROJECTXSP_API AHeldInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHeldInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AActor* Holder;
	FName HolderSocket;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact();

	virtual void SetHolder(AActor* holder, FName socket);

};
