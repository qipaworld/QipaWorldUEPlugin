// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class QipaWorldUEPlugin : ModuleRules
{
	public QipaWorldUEPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "AudioModulation",
                "GeometryCollectionEngine",
                "ChaosSolverEngine",
                "StateTreeModule", 
                "GameplayStateTreeModule",
                "AIModule",
                "NavigationSystem",
                 "OnlineSubsystem",
                  "OnlineSubsystemUtils",
                  "OnlineServicesInterface",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"ApplicationCore",
                "DeveloperSettings",
				"UMG",
                "Niagara",
                "NiagaraAnimNotifies",
                "InputCore",
                "EnhancedInput",
                "Text3D",
                "MetasoundEngine",
                "NavigationSystem",
                "AppFramework",
                "AudioModulation",
                 "GameplayAbilities", "GameplayTags", "GameplayTasks"
                //"RHI",
				// ... add private dependencies that you statically link with here ...	
			}
            );
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        SetupIrisSupport(Target);

    }
}
