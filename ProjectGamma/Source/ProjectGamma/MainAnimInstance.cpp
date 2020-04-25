// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"


void UMainAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner(); // Check what Pawn owns this AnimInstance and assign to Pawn
	}
}

void UMainAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner(); // Check what Pawn owns this AnimInstance and assign to Pawn
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);

		MovementSpeed = LateralSpeed.Size(); // Assigned the magnitude of LateralSpeed to MovementSpeed which is a float

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
	}
}
