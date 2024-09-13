// Fill out your copyright notice in the Description page of Project Settings.


#include "OthersidePreview.h"

#include "Camera/CameraComponent.h"

// Sets default values
AOthersidePreview::AOthersidePreview()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	Collider->InitCapsuleSize(40, 80);
	Collider->SetEnableGravity(false);
	Collider->SetGenerateOverlapEvents(true);
	
	RootComponent = Collider;
	
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture"));
	SceneCapture->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AOthersidePreview::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOthersidePreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Player != nullptr)
	{
		SetActorLocation(Player->GetActorLocation() + (Swapped ? -Offset : Offset));
		SceneCapture->SetWorldRotation(Player->GetFirstPersonCameraComponent()->GetComponentRotation());
	}
	
	Collider->GetOverlappingComponents(OverlappedActors);
	if(OverlappedActors.Num() > 0)
	{
		Blocked = true;
	}
	else
	{
		Blocked = false;
	}

	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Magenta, TEXT("Colliders: " + FString::FromInt(Blocked)));
}

void AOthersidePreview::Populate(AProjectXSPCharacter* newPlayer, FVector newLocation, FVector newOffset)
{
	Player = newPlayer;

	Offset = newOffset;
	SetActorLocation(newLocation);
	
}

const bool AOthersidePreview::IsBlocked()
{
	return Blocked;
}

