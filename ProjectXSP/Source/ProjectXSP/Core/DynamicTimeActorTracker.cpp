// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicTimeActorTracker.h"

// Sets default values for this component's properties
UDynamicTimeActorTracker::UDynamicTimeActorTracker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDynamicTimeActorTracker::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (IsValid(LinkedOtherActor))
	{
		LinkedOther = LinkedOtherActor->GetComponentByClass<UDynamicTimeActorTracker>();
		if (!IsValid(LinkedOther))
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Red, "Other Actor does not have tracker component!.");
		}
	}
}


// Called every frame
void UDynamicTimeActorTracker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDynamicTimeActorTracker::ChangePast()
{
	if (bIsFutureWorld)
	{
		if (IsValid(LinkedOther))
			LinkedOther->PastChanged.ExecuteIfBound(this);
	}
}

bool UDynamicTimeActorTracker::IsFutureWorld()
{
	return bIsFutureWorld;
}

