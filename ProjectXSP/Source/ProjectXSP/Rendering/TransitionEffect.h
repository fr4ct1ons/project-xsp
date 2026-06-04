// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PostProcessComponent.h"
#include "GameFramework/Actor.h"
#include "TransitionEffect.generated.h"

UCLASS()
class PROJECTXSP_API ATransitionEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransitionEffect();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UPostProcessComponent> TransitionFromNewToOldPPC;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UPostProcessComponent> TransitionFromOldToNewPPC;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetTranstionWeight(float newWeight, bool isNewToOld);
	
	UFUNCTION(BlueprintCallable)
	void SetTransitionActive(bool isActive, bool isNewToOld);

};
