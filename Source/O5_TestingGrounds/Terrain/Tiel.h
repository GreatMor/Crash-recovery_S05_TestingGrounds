// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tiel.generated.h"

UCLASS()
class O5_TESTINGGROUNDS_API ATiel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATiel();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceActor(TSubclassOf<AActor> ToSpown, int MinSpawn, int MaxSpawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
