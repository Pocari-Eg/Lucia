// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lucia : ModuleRules
{
	public Lucia(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" ,"UMG", "GameplayTasks",
			"NavigationSystem", "AIModule","FMODStudio","LevelSequence","MovieScene","SpinePlugin"});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
