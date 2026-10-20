// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectXSP : ModuleRules
{
	public ProjectXSP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//PrivateDependencyModuleNames.AddRange(new string[] { "Blutility"});
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "UMGEditor", "Blutility", "UnrealEd" });
	}
}
