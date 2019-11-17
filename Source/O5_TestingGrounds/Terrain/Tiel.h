// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tiel.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);

private:
	bool FindEmtyLocation(FVector& OutLocation, float Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpown, FVector SpawnPoint, float Rotation, float Scale);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	UActorPool* Pool;
};
