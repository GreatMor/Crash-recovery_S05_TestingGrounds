// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class O5_TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPatrolRoute();
	  
public:

	TArray<AActor*> GetPatrollingPointer()const;


private:
	UPROPERTY(EditInstanceOnly, Category = "PatrollingPoints")
	TArray<AActor*> PatrollingPointer;
};

