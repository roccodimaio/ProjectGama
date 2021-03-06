// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"
#include "Main.h"

ATrap::ATrap()
{
	Damage = 15;

	Level = 1; 

	PhysicalStrength = 10; 

	ManaStrength = 0;

	bIsPhysicalAttack = true; 
}

void ATrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	UE_LOG(LogTemp, Warning, TEXT("Trap::OnOverlapBegin"));

	if (OtherActor)
	{
		AMain* Main = Cast<AMain>(OtherActor);
		    
		if (Main)
		{
			Main->DecrementHealth(Damage, PhysicalStrength, ManaStrength, Level, bIsPhysicalAttack);

			Destroy();
		}
	}
	
}

void ATrap::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT("Trap::OnOverlapEnd"));
}
