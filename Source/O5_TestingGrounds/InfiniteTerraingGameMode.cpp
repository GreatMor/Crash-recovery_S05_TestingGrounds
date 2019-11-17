// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteTerraingGameMode.h"
#include "Runtime/NavigationSystem/Public/NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerraingGameMode::AInfiniteTerraingGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>("NavMeshBoundsVolume");
}
void AInfiniteTerraingGameMode::PopulateBoundsVolumePool()
{
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void AInfiniteTerraingGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Fond Actor : %s "), *VolumeToAdd->GetName());
}
