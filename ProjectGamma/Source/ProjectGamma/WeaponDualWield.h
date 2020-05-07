// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponDualWield.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGAMMA_API AWeaponDualWield : public AWeaponBase
{
	GENERATED_BODY()

	AWeaponDualWield();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
	class USkeletalMeshComponent* SkeletalMesh02;

	
	virtual void Equip(AMain* Char) override;
	
};
