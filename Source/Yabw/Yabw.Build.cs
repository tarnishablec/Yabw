// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// ReSharper disable UseCollectionExpression

public class Yabw : ModuleRules
{
	public Yabw(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			[
				// ... add public include paths required here ...
			]
		);


		PrivateIncludePaths.AddRange(
			[
				// ... add other private include paths required here ...
			]
		);


		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
				"GameplayCameras",
				"EnhancedInput",
				"Wynaut"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			[
				// ... add any modules that your module loads dynamically here ...
			]
		);
	}
}