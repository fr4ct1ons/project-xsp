// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoWorldsToolsFunctions.h"

void UTwoWorldsToolsFunctions::TryConnectActors(AActor* FutureActor, AActor* PastActor, TSubclassOf<UEditorUtilityStaticTimeTracker> TrackerClass)
{
	if(!IsValid(FutureActor) || !IsValid(PastActor))
	{
		return;
	}

	if(IsValid(FutureActor->GetComponentByClass<UEditorUtilityStaticTimeTracker>()))
	{
		return;
	}

	if(IsValid(PastActor->GetComponentByClass<UEditorUtilityStaticTimeTracker>()))
	{
		return;
	}

	TObjectPtr<UEditorUtilityStaticTimeTracker> CompFuture = Cast<UEditorUtilityStaticTimeTracker>(FutureActor->AddComponentByClass(TrackerClass, false, FutureActor->GetTransform(), true));
	TObjectPtr<UEditorUtilityStaticTimeTracker> CompPast   = Cast<UEditorUtilityStaticTimeTracker>(PastActor->AddComponentByClass(TrackerClass, false, FutureActor->GetTransform(), true));

	CompFuture->ExternalSetup(true, CompPast);
	CompFuture->ExternalSetup(false, CompFuture);
}
