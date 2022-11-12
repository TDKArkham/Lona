// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindAttackLocation.h"

#include "AIController.h"
#include "SRAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FindAttackLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIC = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (AIC && Blackboard)
	{
		ASRAICharacter* OwnerCharacter = Cast<ASRAICharacter>(AIC->GetPawn());
		if (OwnerCharacter && OwnerCharacter->LocationsToGo.Num() > 0)
		{
			int32 Index = FMath::RandRange(0, OwnerCharacter->LocationsToGo.Num() - 1);
			
			Blackboard->SetValueAsVector(KeySelector.SelectedKeyName, OwnerCharacter->LocationsToGo[Index]);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
