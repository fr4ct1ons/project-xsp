// Fill out your copyright notice in the Description page of Project Settings.


#include "TransitionEffect.h"

// Sets default values
ATransitionEffect::ATransitionEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransitionFromNewToOldPPC = CreateDefaultSubobject<UPostProcessComponent>(TEXT("TransitionFromNewToOldPPC"));
	TransitionFromOldToNewPPC = CreateDefaultSubobject<UPostProcessComponent>(TEXT("TransitionFromOldToNewPPC"));
}

// Called when the game starts or when spawned
void ATransitionEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATransitionEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATransitionEffect::SetTranstionWeight(float newWeight, bool isNewToOld)
{
	if (isNewToOld)
	{
		TransitionFromNewToOldPPC->BlendWeight = newWeight;
	}
	else
	{
		TransitionFromOldToNewPPC->BlendWeight = newWeight;
	}
}

void ATransitionEffect::SetTransitionActive(bool isActive, bool isNewToOld)
{
	if (isNewToOld)
	{
		TransitionFromNewToOldPPC->bEnabled = isActive;
	}
	else
	{
		TransitionFromOldToNewPPC->bEnabled = isActive;
	}
}
