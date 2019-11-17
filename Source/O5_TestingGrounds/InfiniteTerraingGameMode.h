// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "O5_TestingGroundsGameMode.h"
#include "InfiniteTerraingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class O5_TESTINGGROUNDS_API AInfiniteTerraingGameMode : public AO5_TestingGroundsGameMode
{
	GENERATED_BODY()
	
public:

	AInfiniteTerraingGameMode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPool* NavMeshBoundsVolumePool;


private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);

};
  