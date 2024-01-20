// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CryptReider : ModuleRules
{
	public CryptReider(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
