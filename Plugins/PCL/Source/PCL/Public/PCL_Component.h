// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/IPluginManager.h"
//#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "PCL_Actor.h"
#include "PCL_Library.h"
#include "PCL_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PCL_API UPCL_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPCL_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
		TArray<FVector> LoadPCL();
	UPROPERTY(EditAnywhere)
		float locPointMultiplier = 100;
	//UPROPERTY(EditAnywhere)
		//FString fileLocation = FPaths::Combine(*(IPluginManager::Get().FindPlugin("PCL")->GetBaseDir()), TEXT("Source/PCL/Private/test_ply.ply"));

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APCL_Actor> PCL_Actor;

private:
	pcl::PointCloud <pcl::PointXYZ> cloud;
		
};
