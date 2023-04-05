// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Proto3 : ModuleRules
{
	public Proto3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "Navmesh", "NavigationSystem" });
	}
}
