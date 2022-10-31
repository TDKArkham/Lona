// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ParabolaAttack.h"

#include "AIController.h"
#include "Lona/SRProjectile_EnemyParabola.h"

EBTNodeResult::Type UBTTask_ParabolaAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	
	if(ParabolaProjectile)
	{
		AAIController* AIC = OwnerComp.GetAIOwner();
		if(AIC)
		{
			APawn* OwnerPawn = Cast<APawn>(AIC->GetOwner());
			if(OwnerPawn)
			{
				FActorSpawnParameters SpawnParam;
				SpawnParam.Instigator = OwnerPawn;
				SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				GetWorld()->SpawnActor<AActor>(ParabolaProjectile, OwnerPawn->GetActorLocation(), FRotator::ZeroRotator, SpawnParam);

				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}