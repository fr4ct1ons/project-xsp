// Fill out your copyright notice in the Description page of Project Settings.


#include "./SceneLight.h"

// Sets default values
ASceneLight::ASceneLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	LightBulb = CreateDefaultSubobject<UStaticMeshComponent>("LightBulb");
	LightBulb->SetupAttachment(RootComponent);
	
	LightFrame = CreateDefaultSubobject<UStaticMeshComponent>("LightFrame");
	LightFrame->SetupAttachment(RootComponent);

	TimeTracker = CreateDefaultSubobject<UDynamicTimeActorTracker>("TimeTracker"); 
	TimeTracker->PastChanged.BindDynamic(this, &ASceneLight::OnPastChanged);
}

// Called when the game starts or when spawned
void ASceneLight::BeginPlay()
{
	Super::BeginPlay();

	if (!TimeTracker->IsFutureWorld())
	{
		if (bTurnOff)
		{
			LightComponent->DestroyComponent();
		}
		else
		{
			LightComponent->SetIntensity(LightComponent->Intensity/2.f);
		}
	}
}

void ASceneLight::OnPastChanged(UDynamicTimeActorTracker* other)
{
	LightComponent->DestroyComponent();
	LightBulb->DestroyComponent();
	OnLightbulbDestroyed();
}

float ASceneLight::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	LightComponent->DestroyComponent();
	LightBulb->DestroyComponent();
	OnLightbulbDestroyed();

	if (TimeTracker->IsFutureWorld())
	{
		TimeTracker->ChangePast();
	}
	
	return DamageAmount;
}

// Called every frame
void ASceneLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

