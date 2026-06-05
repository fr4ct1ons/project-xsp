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

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> Holder;
	UPROPERTY(BlueprintReadOnly)
	FName HolderSocket;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USceneComponent> HolderComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Interact();

	virtual void SetHolder(TObjectPtr<AActor> holder, FName socket);
	virtual void SetHolder(TObjectPtr<AActor> holder, TObjectPtr<USceneComponent> holderComponent);

};
