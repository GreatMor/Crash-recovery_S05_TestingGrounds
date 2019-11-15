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

void ATiel::PlaceActor(TSubclassOf<AActor> ToSpown, int MinSpawn, int MaxSpawn)
{
	FVector Min(0, -2000, 0);//	Size Relative to Pivot
	FVector Max(4000, 2000, 0);//	Max size BP_Tile

	FBox Bounds(Min, Max);

	int NumberToSpawn = FMath::FRandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < 5; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds); // 
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpown);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

// Called when the game starts or when spawned
void ATiel::BeginPlay()
{
	Super::BeginPlay();
	CastSphere(GetActorLocation(), 300);
	CastSphere(GetActorLocation() + FVector(0, 0, 1000),300);
}

// Called every frame
void ATiel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATiel::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		Location + Radius,
		FQuat::Identity,
		ECollisionChannel::ECC_Camera,
		FCollisionShape::MakeSphere(Radius)
	);

	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;//if it intersects, then the color red is otherwise green
	DrawDebugSphere(
		GetWorld(),
		Location,
		Radius,
		20,
		ResultColor,
		true, 100);

	UE_LOG(LogTemp, Warning, TEXT("Collor %i ;"), HasHit)
	return !HasHit;
}

