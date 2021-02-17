// Fill out your copyright notice in the Description page of Project Settings.


#include "PCL_Component.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UPCL_Component::UPCL_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//todo
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
			//pcl::io::loadPLYFile("D:\\Unreal Projects\\UE_4_25\\NewPCLPlugin\\Plugins\\PCL\\Source\\PCL\\Private\\Laurana50k.ply", cloud);
			pcl::io::loadPLYFile("D:\\Unreal Projects\\UE_4_25\\NewPCLPlugin\\Plugins\\PCL\\Source\\PCL\\Private\\test_ply.ply", cloud);
			FTransform trans;
			trans.SetRotation(FQuat(0.0, 0.0, 0.0, 0.0));
			trans.SetScale3D(FVector(1.0, 1.0, 1.0));
			TArray<pcl::PointXYZ> currPoints;
			for (pcl::PointXYZ i : cloud.points)
			{
				if (i.x == 0.0f && i.y == 0.0f && i.z == 0.0f)
				{
					continue;
				}

				FVector pointLoc = FVector(i.x, i.y, i.z) * locPointMultiplier;

				// add initial 2 points
				if (currPoints.Num() < 2)
				{
					trans.SetLocation(pointLoc);
					UE_LOG(LogTemp, Warning, TEXT("--%d,--%d,--%d"), pointLoc.X, pointLoc.Y, pointLoc.Z);
					world->SpawnActor<APCL_Actor>(PCL_Actor, trans);
					currPoints.Add(i);
					continue;
				}

				// max amount of spawned actors
				if (currPoints.Num() > maxPoints)
				{
					return;
				}

				// don't add points if too close to another point to reduce amount of actors
				for (int32 idx = 0; idx != currPoints.Num(); ++idx)
				{
					auto& point = currPoints[idx];

					float distance = (FVector(point.x, point.y, point.z) - FVector(i.x, i.y, i.z)).Size();

					UE_LOG(LogTemp, Warning, TEXT("dist: %f"), distance);
					if (distance > minDistance)
					{
						trans.SetLocation(pointLoc);
						UE_LOG(LogTemp, Warning, TEXT("--%d,--%d,--%d"), pointLoc.X, pointLoc.Y, pointLoc.Z);
						world->SpawnActor<APCL_Actor>(PCL_Actor, trans);
						currPoints.Add(i);
						break;
					}
				}
			}
		}
	}
}
