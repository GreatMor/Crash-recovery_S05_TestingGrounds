// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"
#include "GameFramework/Actor.h"
#include "Tiel.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;

};

class UActorPool;

UCLASS()
class O5_TESTINGGROUNDS_API ATiel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATiel();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceActors(TSubclassOf<AActor> ToSpown, int MinSpaw=1, int MaxSpawn=1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceAIPawn(TSubclassOf<APawn> ToSpawn, int MinSpaw = 1, int MaxSpawn = 1, float Radius = 500);

protected:
	// Called when the game starts or when spawned
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtend;//	Size Relative to Pivot

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtend;//	Max size BP_Tile

public:	

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);	

private:
	void PositionNavMeshBoundsVolume();

	TArray<FSpawnPosition>RandomSpawnPosition( int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	bool FindEmtyLocation(FVector& OutLocation, float Radius);

	template<class T>
	void RanbomlyPlacrActors(TSubclassOf<T> ToSpown, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	void PlaceActor(TSubclassOf<AActor> ToSpown, FSpawnPosition SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpown, FSpawnPosition SpawnPosition);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	UActorPool* Pool;

	AActor* NavMeshBoundsVolume;
};
