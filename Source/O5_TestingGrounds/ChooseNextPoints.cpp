// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextPoints.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BehaviorTreeTypes.h "

EBTNodeResult::Type UChooseNextPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the patroll route
	auto AIController = OwnerComp.GetAIOwner();// getting AI Owner
	auto ControllerPawn = AIController->GetPawn();// getting control pawn
	auto PatrolRoute = ControllerPawn->FindComponentByClass<UPatrolRoute>();

	auto PatrolPoints = PatrolRoute->GetPatrollingPointer();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("is missing patrol pointers"));
		return EBTNodeResult::Failed;
	}

	//Set next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);//	current index
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	//UE_LOG(LogTemp, Warning, TEXT("Task c++"))
	return EBTNodeResult::Succeeded;
}

