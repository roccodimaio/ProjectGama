// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Pickup UMETA(DisplayName = "Pickup"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_MAX UMETA(DisplayName = "DefaultMAX")
};


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_OneHandWeapon UMETA(DisplayName = "OneHandWeapon"),
	EWT_TwoHandHeavyWeapon UMETA(DisplayName = "TwoHandHeavyWeapon"),
	EWT_TwoHandLightWeapon UMETA(DisplayName = "TwoHandLightWeapon"),
	EWT_DualWieldWeapon UMETA(DisplayName = "DualWieldWeapon"),
	EWT_OneHandAndShield UMETA(DisplayName = "OneHandAndSheild"),
	EWT_StaffWeapon UMETA(DisplayName = "StaffWeapon"),
	EWT_OneHandGun UMETA(DisplayName = "OneHandGun"),
	EWT_TwoHandGun UMETA(DisplayName = "TwoHandGun"),
	EWT_MAX UMETA (DisplayName = "Default_MAX")
};

/**
 * 
 */
UCLASS()
class PROJECTGAMMA_API AWeaponBase : public AItem
{
	GENERATED_BODY()

public:

	AWeaponBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	EWeaponState WeaponState; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	EWeaponType WeaponType; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles")
	bool bWeaponParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundCue* OnEquipSound;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
	class USkeletalMeshComponent* SkeletalMesh;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void Equip(class AMain* Char);

	FORCEINLINE void SetWeaponState(EWeaponState State) { WeaponState = State; }
	FORCEINLINE EWeaponState GetWeaponState() { return WeaponState; }

	FORCEINLINE void SetWeaponType(EWeaponType Type) { WeaponType = Type; }
	FORCEINLINE EWeaponType GetWeaponType() { return WeaponType; }

};
