// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCL.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

THIRD_PARTY_INCLUDES_START
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <boost/shared_ptr.hpp>
THIRD_PARTY_INCLUDES_END

DEFINE_LOG_CATEGORY(PCLLog);

#define LOCTEXT_NAMESPACE "FPCLModule"

void FPCLModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	UE_LOG(PCLLog, Display, TEXT("################################### \n"));
	UE_LOG(PCLLog, Display, TEXT("## Starting Point Cloud Renderer... \n"));
	UE_LOG(PCLLog, Display, TEXT("################################### \n"));

	FPCLModule::LoadPCDFile();
}

void FPCLModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle

}

int FPCLModule::LoadPCDFile() {

	pcl::PointCloud <pcl::PointXYZ> cloud;

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("PCL")->GetBaseDir();
	FString plyPath = FPaths::Combine(*BaseDir, TEXT("Source/PCL/Private/Laurana50k.ply"));

	if (pcl::io::loadPLYFile(TCHAR_TO_UTF8(*plyPath), cloud) == -1)
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
