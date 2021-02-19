// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class PCL : ModuleRules
{
	public PCL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnableExceptions = true;
		bUseRTTI = true;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				Path.Combine(ModuleDirectory, "Public")
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				Path.Combine(ModuleDirectory, "Private")
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Core",
				"Slate",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		string thirdPartyPath = ModuleDirectory.Substring(0, ModuleDirectory.LastIndexOf("\\") + 1) + "ThirdParty";
		string OpenCVPath = Path.Combine(thirdPartyPath, "OpenCVLibrary");
		string BoostPath = Path.Combine(thirdPartyPath, "Boost");
		string PCLPath = Path.Combine(thirdPartyPath, "PCL_181");
		string EigenPath = Path.Combine(thirdPartyPath, "Eigen");

		PublicIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(OpenCVPath,"include"),
				Path.Combine(BoostPath,"include","boost-1_64"),
				Path.Combine(EigenPath,"eigen3"),
				Path.Combine(PCLPath,"include","pcl-1.8")
			});

		// Libs path
		PublicAdditionalLibraries.AddRange(
			new string[]
			{
				Path.Combine(OpenCVPath,"lib","x64","opencv_world451.lib"),
                //boost Lib
                Path.Combine(BoostPath, "lib\\libboost_chrono-vc141-mt-1_64.lib"),
				Path.Combine(BoostPath, "lib\\libboost_date_time-vc141-mt-1_64.lib"),
				Path.Combine(BoostPath, "lib\\libboost_filesystem-vc141-mt-1_64.lib"),
				Path.Combine(BoostPath, "lib\\libboost_iostreams-vc141-mt-1_64.lib"),
				Path.Combine(BoostPath, "lib\\libboost_system-vc141-mt-1_64.lib"),
				Path.Combine(BoostPath, "lib\\libboost_thread-vc141-mt-1_64.lib"),
                //PCL Lib
                Path.Combine(PCLPath, "lib\\pcl_common_release.lib"),
				Path.Combine(PCLPath, "lib\\pcl_io_release.lib"),
				Path.Combine(PCLPath, "lib\\pcl_io_ply_release.lib"),
				Path.Combine(PCLPath, "lib\\pcl_octree_release.lib"),
				Path.Combine(PCLPath, "lib\\pcl_ml_release.lib")
		});

		//Ensure that the DLLs are staged along with the executable
		//RuntimeDependencies.Add("$(PluginDir)/Binaries/Win64/k4a.dll");
		//RuntimeDependencies.Add("$(PluginDir)/Binaries/Win64/k4abt.dll");
		//RuntimeDependencies.Add("$(PluginDir)/Binaries/Win64/depthengine_2_0.dll");
		// RuntimeDependencies.Add("$(PluginDir) / Binaries / Win64 /opencv_world451.dll");

		RuntimeDependencies.Add(Path.Combine(OpenCVPath, "dll", "opencv_world451.dll"));

		PublicDefinitions.Add(string.Format("WITH_PCL_BINDING={0}", 1));
		PublicDefinitions.Add(string.Format("WITH_BOOST_BINDING={0}", 1));
		PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS=1");
		PublicDefinitions.Add("BOOST_DISABLE_ABI_HEADERS=1");

	}
}
