// Fill out your copyright notice in the Description page of Project Settings.


#include "SideRunnerCharacter.h"

#include "SRAttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASideRunnerCharacter::ASideRunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->CrouchedHalfHeight = 55.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 300.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	AttributeComponent = CreateDefaultSubobject<USRAttributeComponent>(TEXT("AttributeComponent"));

	bIsFacingRight = true;
	bIsCrouching = false;
}

void ASideRunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ASideRunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCharacterFaceDirection();
}

void ASideRunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ASideRunnerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASideRunnerCharacter::Fire);
}

void ASideRunnerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);


		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void ASideRunnerCharacter::Fire()
{
	if (ProjectileClass)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
		{
			/*float PositionX;
			float PositionY;
			PC->GetMousePosition(PositionX, PositionY);

			float TargetPitch = -UKismetMathLibrary::DegAtan2(PositionY - BaseFirePosition.Y, PositionX - BaseFirePosition.X);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::SanitizeFloat(TargetPitch));*/

			FVector WorldLocation;
			FVector WorldDirection;
			PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
			FVector WorldLocationOffset = WorldLocation + WorldDirection * 100000.0f;

			FVector ActorLocation = GetActorLocation();

			FVector AimPoint;
			AimPoint.X = ActorLocation.X;
			AimPoint.Y = (ActorLocation.X - WorldLocation.X) * (WorldLocationOffset.Y - WorldLocation.Y) / (WorldLocationOffset.X - WorldLocation.X) + WorldLocation.Y;
			AimPoint.Z = (ActorLocation.X - WorldLocation.X) * (WorldLocationOffset.Z - WorldLocation.Z) / (WorldLocationOffset.X - WorldLocation.X) + WorldLocation.Z;

			FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, AimPoint);

			FTransform SpawnTM(SpawnRotation, ActorLocation);

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Instigator = this;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParameters);
		}
	}

}

void ASideRunnerCharacter::UpdateCharacterFaceDirection()
{
	//Re-rotate Character face direction
	float TargetRotationYaw = 0.0f;
	bIsFacingRight = true;
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		int32 SizeX;
		int32 SizeY;
		PC->GetViewportSize(SizeX, SizeY);

		float MouseX;
		float MouseY;
		PC->GetMousePosition(MouseX, MouseY);

		float CameraY = FollowCamera->GetRelativeLocation().Y;

		float Min = CameraY + SizeX / 2.0f;
		float Max = CameraY + (float)SizeX;

		if (!UKismetMathLibrary::InRange_FloatFloat((CameraY + MouseX), Min, Max))
		{
			TargetRotationYaw = 180.f;
			bIsFacingRight = false;
		}

		float CurrentRotationYaw = GetMesh()->GetRelativeRotation().Yaw;
		GetMesh()->SetRelativeRotation(FRotator(0.0f, FMath::FInterpTo(CurrentRotationYaw, TargetRotationYaw, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 5.0f), 0.0f));
	}
}

USRAttributeComponent* ASideRunnerCharacter::GetAttributeComponent() const
{
	return AttributeComponent;
}
