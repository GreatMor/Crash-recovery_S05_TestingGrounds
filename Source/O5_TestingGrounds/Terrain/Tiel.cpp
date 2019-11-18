// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiel.h"
#include "Math/UnrealMathUtility.h"
#include "HAL/Platform.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"


// Sets default values
ATiel::ATiel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinExtend = FVector(0, -2000, 0);
	MaxExtend = FVector(4000, 2000, 0);
}

void ATiel::SetPool(UActorPool* InPool)
{
	//UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(InPool->GetName()));
	Pool = InPool;
	
	PositionNavMeshBoundsVolume();
}

void ATiel::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Not enough actors in pool."), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out: {%s}"), *GetName(), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
}

void ATiel::PlaceActors(TSubclassOf<AActor> ToSpown, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::FRandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		
		bool found = FindEmtyLocation(SpawnPoint, Radius * RandomScale);
		if (found)
		{
			float RandomRotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpown, SpawnPoint, RandomRotation, RandomScale);
		}
	}
}

bool ATiel::FindEmtyLocation(FVector& OutLocation, float Radius)
{
	FBox Bounds(MinExtend, MaxExtend);
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

void ATiel::PlaceActor(TSubclassOf<AActor> ToSpown, FVector SpawnPoint, float Rotation, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpown);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, Rotation, 0));
	Spawned->SetActorScale3D(FVector(Scale,Scale,Scale));
}
void ATiel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATiel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATiel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Pool->Return(NavMeshBoundsVolume);
}


bool ATiel::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation + Radius,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);

	//FColor ResultColor = HasHit ? FColor::Red : FColor::Green;//if it intersects, then the color red is otherwise green
	//DrawDebugCapsule(
	//	GetWorld(),
	//	GlobalLocation,
	//	0,
	//	Radius,
	//	FQuat::Identity,
	//	ResultColor,
	//	true, 
	//	100);
	
	return !HasHit;
}


