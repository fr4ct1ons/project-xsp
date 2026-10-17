// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/LightComponent.h"
#include "ProjectXSP/Core/DynamicTimeActorTracker.h"


#include "SceneLight.generated.h"



UCLASS()
class PROJECTXSP_API ASceneLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Setting this variable to true will automatically disable the light instead of dimming them.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTurnOff;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> LightFrame;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> LightBulb;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<ULightComponent> LightComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UDynamicTimeActorTracker> TimeTracker;

	UFUNCTION()
	void OnPastChanged(UDynamicTimeActorTracker* other);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnLightbulbDestroyed();
};
