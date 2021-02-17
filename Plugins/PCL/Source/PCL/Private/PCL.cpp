// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCL.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "PCLLibrary/ExampleLibrary.h"

THIRD_PARTY_INCLUDES_START
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <boost/shared_ptr.hpp>
THIRD_PARTY_INCLUDES_END

DECLARE_LOG_CATEGORY_EXTERN(PCLLog, Display, All);
DEFINE_LOG_CATEGORY(PCLLog);

#define LOCTEXT_NAMESPACE "FPCLModule"

void FPCLModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	UE_LOG(PCLLog, Display, TEXT("################################### \n"));
	UE_LOG(PCLLog, Display, TEXT("## Starting Point Cloud Renderer... \n"));
	UE_LOG(PCLLog, Display, TEXT("################################### \n"));

	FPCLModule::LoadPCDFile();

	/*
	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("PCL")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/PCLLibrary/Win64/ExampleLibrary.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/PCLLibrary/Mac/Release/libExampleLibrary.dylib"));
#endif // PLATFORM_WINDOWS

	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ExampleLibraryHandle)
	{
		// Call the test function in the third party library that opens a message box
		ExampleLibraryFunction();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
	*/
}

void FPCLModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	//FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	//ExampleLibraryHandle = nullptr;
}

int FPCLModule::LoadPCDFile() {

	pcl::PointCloud <pcl::PointXYZ> cloud;
	if (pcl::io::loadPLYFile("D:\\Unreal Projects\\UE_4_25\\NewPCLPlugin\\Plugins\\PCL\\Source\\PCL\\Private\\Laurana50k.ply", cloud) == -1)		//Dummy function call - please change
	{
		UE_LOG(PCLLog, Error, TEXT("Couldn't read ply file.\n"));
	
		return (-1);
	}

	auto w = FString::FromInt(cloud.width * cloud.height);
	UE_LOG(PCLLog, Display, TEXT("Succesfully loaded %s data points."), *w);

	return (1);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPCLModule, PCL)
