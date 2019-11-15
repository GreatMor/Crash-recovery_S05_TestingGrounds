// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiel.h"
#include "Math/UnrealMathUtility.h"
#include "HAL/Platform.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATiel::ATiel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATiel::PlaceActors(TSubclassOf<AActor> ToSpown, int MinSpawn, int MaxSpawn, float Radius)
{
	int NumberToSpawn = FMath::FRandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < 5; i++)
	{
		FVector SpawnPoint;
		bool found = FindEmtyLocation(SpawnPoint, Radius);

		if (found)
		{
			PlaceActor(ToSpown, SpawnPoint);
		}
	}
}
bool ATiel::FindEmtyLocation(FVector& OutLocation, float Radius)
{
	FVector Min(0, -2000, 0);//	Size Relative to Pivot
	FVector Max(4000, 2000, 0);//	Max size BP_Tile
	FBox Bounds(Min, Max);
	const int MAX_ATTEMPTS = 100;
	
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(CandidatePoint, Radius))
		{
			OutLocation = CandidatePoint;
			return true;
		}		
	}
	return false;
}

void ATiel::PlaceActor(TSubclassOf<AActor> ToSpown, FVector SpawnPoint)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpown);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
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

bool ATiel::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		Location + Radius,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);

	UE_LOG(LogTemp, Warning, TEXT("HitResult %s ;"), *HitResult.ToString())

	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;//if it intersects, then the color red is otherwise green
	DrawDebugCapsule(
		GetWorld(),
		Location,
		0,
		Radius,
		FQuat::Identity,
		ResultColor,
		true, 
		100);
	
	return !HasHit;
}

