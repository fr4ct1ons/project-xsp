// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorUtilityStaticTimeTracker.h"

void UEditorUtilityStaticTimeTracker::ExternalSetup(bool newIsFutureWorld, UEditorUtilityStaticTimeTracker* newOther)
{
	bIsFutureWorld = newIsFutureWorld;
	Other = newOther;
}
