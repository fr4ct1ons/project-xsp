// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/Actor.h"
#include "ProjectXSP/ProjectXSPCharacter.h"
#include "OthersidePreview.generated.h"

UCLASS()
class PROJECTXSP_API AOthersidePreview : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOthersidePreview();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Offset = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCapsuleComponent* Collider;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USceneCaptureComponent2D* SceneCapture;

	UPROPERTY(BlueprintReadWrite)
	AProjectXSPCharacter* Player;

	UPROPERTY(BlueprintReadOnly)
	bool Blocked;

	TArray<UPrimitiveComponent*> OverlappedActors;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Populate(AProjectXSPCharacter* newPlayer, FVector newLocation, FVector newOffset);

	UFUNCTION(BlueprintPure)
	const bool IsBlocked();
};
