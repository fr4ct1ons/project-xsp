// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h" 
#include "../CommonDelegates.h"
#include "DynamicTimeActorTracker.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPastChangedSignature, UDynamicTimeActorTracker*, PastComponent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXSP_API UDynamicTimeActorTracker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDynamicTimeActorTracker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsFutureWorld;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDynamicTimeActorTracker> LinkedOther;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> LinkedOtherActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ChangePast();

	UPROPERTY()
	FPastChangedSignature PastChanged;

	bool IsFutureWorld();
};
