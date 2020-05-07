// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Main.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AWeaponBase::AWeaponBase()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	bWeaponParticles = false; 

	WeaponState = EWeaponState::EWS_Pickup;

	WeaponType = EWeaponType::EWT_OneHandWeapon;
}

void AWeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	//UE_LOG(LogTemp, Warning, TEXT("In WeaponBase Overlap"));

	if ((WeaponState == EWeaponState::EWS_Pickup) && OtherActor)
	{

		//UE_LOG(LogTemp, Warning, TEXT("In WeaponBase Overlap - OtherActor"));

		AMain* Main = Cast<AMain>(OtherActor);

		if (Main)
		{
			Main->SetActiveOverlappingItem(this); 
		}
	}
		

}

void AWeaponBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (OtherActor)
	{

		//UE_LOG(LogTemp, Warning, TEXT("In WeaponBase Overlap - OtherActor"));

		AMain* Main = Cast<AMain>(OtherActor);

		if (Main)
		{
			Main->SetActiveOverlappingItem(nullptr);
		}
	}
}

void AWeaponBase::Equip(AMain* Char)
{
	
	//UE_LOG(LogTemp, Warning, TEXT("In WeaponBase Equip"));

	if (Char)
	{
		//UE_LOG(LogTemp, Warning, TEXT("In WeaponBase Equip - Char"));
		// Ignore camera
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

		// Ignore Char
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		SkeletalMesh->SetSimulatePhysics(false);

		// Create SkeletalMeshSocket reference and assign the socket from the Char called RightHandSocket
		const USkeletalMeshSocket* RightHandSocket = Char->GetMesh()->GetSocketByName("RightHandSocket");

		if (RightHandSocket)
		{
			//UE_LOG(LogTemp, Warning, TEXT("In WeaponBase Equip - Char - RightHandSocket"));
			// Attach WeaponBase to the RightHandSocket on Char
			RightHandSocket->AttachActor(this, Char->GetMesh());
			bRotate = false;
			
			Char->SetEquipWeapon(this);
			Char->SetActiveOverlappingItem(nullptr);
		}

		if (OnEquipSound)
		{
			UGameplayStatics::PlaySound2D(this, OnEquipSound);
		}

		if (!bWeaponParticles)
		{
			IdleParticles->Deactivate(); 
		}
		
	}
}
