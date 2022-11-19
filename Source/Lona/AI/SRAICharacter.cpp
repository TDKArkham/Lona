// Fill out your copyright notice in the Description page of Project Settings.


#include "SRAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Lona/SRAttributeComponent.h"
#include "Perception/PawnSensingComponent.h"

ASRAICharacter::ASRAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AttributeComponent = CreateDefaultSubobject<USRAttributeComponent>(TEXT("AttributeComponent"));
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
}

void ASRAICharacter::BeginPlay()
{
	Super::BeginPlay();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASRAICharacter::OnSeePawn);
	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASRAICharacter::OnHealthChanged);
}

void ASRAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASRAICharacter::OnHealthChanged(AActor* InstigateActor, USRAttributeComponent* OwnerComponent, float NewValue, float Delta)
{
	if (Delta < 0.0f)
	{
		if (NewValue <= 0.0f)
		{
			//Disable Behavior Tree
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				UBrainComponent* Brain = AIC->GetBrainComponent();
				if (Brain)
				{
					Brain->StopLogic("Got Killed");
				}
			}

			//Disable Movement & Collision
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			//SetLifeSpan, Destroy self after 5 sec
			SetLifeSpan(5.0f);
		}
	}
}

void ASRAICharacter::OnSeePawn(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BB = AIC->GetBlackboardComponent();
		if (BB)
		{
			BB->SetValueAsObject("TargetActor", Pawn);
		}
	}
}
