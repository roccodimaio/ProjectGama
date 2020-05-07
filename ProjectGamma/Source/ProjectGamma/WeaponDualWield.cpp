// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDualWield.h"
#include "Components/SkeletalMeshComponent.h"
#include "Main.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h"


AWeaponDualWield::AWeaponDualWield()
{

	SkeletalMesh02 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh02"));
	SkeletalMesh02->SetupAttachment(GetRootComponent());

	
	
}

void AWeaponDualWield::Equip(AMain* Char)
{

	Super::Equip(Char);

	if (Char)
	{
		//UE_LOG(LogTemp, Warning, TEXT("In WeaponBase Equip - Char"));
		// Ignore camera
		SkeletalMesh02->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

		// Ignore Char
		SkeletalMesh02->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		SkeletalMesh02->SetSimulatePhysics(false);

		// Create SkeletalMeshSocket reference and assign the socket from the Char called RightHandSocket
		const USkeletalMeshSocket* LeftHandSocket = Char->GetMesh()->GetSocketByName("LeftHandSocket");

		FName SocketName = LeftHandSocket->GetFName(); 

		if (LeftHandSocket)
		{
			//UE_LOG(LogTemp, Warning, TEXT("In WeaponBase Equip - Char - RightHandSocket"));
			// Attach WeaponBase to the RightHandSocket on Char
			SkeletalMesh02->AttachToComponent(Char->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftHandSocket"));
			bRotate = false;
		}
	}
}

