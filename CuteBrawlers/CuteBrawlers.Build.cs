// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CuteBrawlers : ModuleRules
{
	public CuteBrawlers(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.AddRange(new string[] {
			 "CuteBrawlers/Abilities",
			 "CuteBrawlers/Modifiers",
			 "CuteBrawlers/Projectiles",
			 "CuteBrawlers/SpawnActors",
			 "CuteBrawlers/Powerups",
			 "CuteBrawlers"
		 });

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
