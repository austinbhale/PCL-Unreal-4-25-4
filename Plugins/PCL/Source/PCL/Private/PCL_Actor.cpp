// Fill out your copyright notice in the Description page of Project Settings.


#include "PCL_Actor.h"

// Sets default values
APCL_Actor::APCL_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APCL_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APCL_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

