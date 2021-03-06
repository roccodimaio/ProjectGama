// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Trap.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGAMMA_API ATrap : public AItem
{
	GENERATED_BODY()

public:

	ATrap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 PhysicalStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 ManaStrength; 

	bool bIsPhysicalAttack;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
};
