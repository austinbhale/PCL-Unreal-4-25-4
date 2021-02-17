// Fill out your copyright notice in the Description page of Project Settings.

#include "PCL.h"
#include "PCL_Component.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UPCL_Component::UPCL_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//PCL_Actor = ConstructorHelpers::FClassFinder<AStaticMeshActor>(TEXT("Blueprint'/Game/BP/MyStaticMeshActor.MyStaticMeshActor'")).Class;
	// ...
}


// Called when the game starts
void UPCL_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPCL_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UPCL_Component::LoadPCL()
{
	if (PCL_Actor)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			//"D:\\Unreal Projects\\UE_4_25\\PCL-Unreal-4-25-4\\Plugins\\PCL\\Source\\PCL\\Private\\Laurana50k.ply"
			if (pcl::io::loadPLYFile("D:\\Unreal Projects\\UE_4_25\\PCL-Unreal-4-25-4\\Plugins\\PCL\\Source\\PCL\\Private\\test_ply.ply", cloud) == -1)
			{
				UE_LOG(PCLLog, Error, TEXT("Couldn't read ply file.\n"));
				return;
			}

			auto w = FString::FromInt(cloud.width * cloud.height);
			UE_LOG(PCLLog, Display, TEXT("Succesfully loaded %s data points."), *w);

			FTransform trans;
			trans.SetRotation(FQuat(0.0, 0.0, 0.0, 0.0));
			trans.SetScale3D(FVector(1.0, 1.0, 1.0));
			//TArray<pcl::PointXYZ> currPoints;
			for (pcl::PointXYZ i : cloud.points)
			{
				FVector pointLoc = FVector(i.x, i.y, i.z) * locPointMultiplier;

				trans.SetLocation(pointLoc);
				UE_LOG(PCLLog, Warning, TEXT("--%d,--%d,--%d"), pointLoc.X, pointLoc.Y, pointLoc.Z);
				world->SpawnActor<APCL_Actor>(PCL_Actor, trans);
			}
		}
	}
}
