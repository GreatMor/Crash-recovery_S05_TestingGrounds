// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiel.h"
#include "Math/UnrealMathUtility.h"
#include "HAL/Platform.h"

// Sets default values
ATiel::ATiel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATiel::PlaceActor()
{
	FVector Min(0, -2000, 0);//	Size Relative to Pivot
	FVector Max(4000, 2000, 0);//	Max size BP_Tile

	FBox Bounds(Min, Max);

	for (size_t i = 0; i < 5; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds); // 
		UE_LOG(LogTemp, Warning, TEXT("Spawn Point %s"), *SpawnPoint.ToCompactString());
	}
}

// Called when the game starts or when spawned
void ATiel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATiel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

