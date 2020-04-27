// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OpenSwitch.generated.h"

UCLASS()
class PROJECTGAMMA_API AOpenSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenSwitch();

	/** Overlap volume for functionality to be triggered */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OpenSwitch")
	class UBoxComponent* TriggerBox;

	/** Floor switch for character to step one */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OpenSwitch")
	class UStaticMeshComponent* FloorSwitch;

	/** Door to move when triggered */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OpenSwitch")
	UStaticMeshComponent* DoorMesh01;

	/** Door to move when triggered */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OpenSwitch")
	UStaticMeshComponent* DoorMesh02; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OpenSwitch")
	bool bIsDoorMesh02Set;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OpenSwitch")
	bool bIsFloorSwitchMeshSet;

	/** Initial location for the Door01Mesh */
	UPROPERTY(BlueprintReadWrite, Category = "OpenSwitch")
	FVector InitialDoor01Location;

	/** Initial location for the Door02Mesh */
	UPROPERTY(BlueprintReadWrite, Category = "OpenSwitch")
	FVector InitialDoor02Location;

	/** Initial location for the FloorSwitch Mesh */
	UPROPERTY(BlueprintReadWrite, Category = "OpenSwitch")
	FVector InitialSwitchLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "OpenSwitch")
	void OpenDoor(); 

	UFUNCTION(BlueprintImplementableEvent, Category = "OpenSwitch")
	void CloseDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "OpenSwitch")
	void RaiseFloorSwitch();

	UFUNCTION(BlueprintImplementableEvent, Category = "OpenSwitch")
	void LowerFloorSwitch();

	UFUNCTION(BlueprintCallable, Category = "OpenSwitch")
	void UpdateDoor01Location(FVector DoorDirection); 

	UFUNCTION(BlueprintCallable, Category = "OpenSwitch")
	void UpdateFloorSwitchLocation(float Value);

	// UFUNCTION(BlueprintCallable, Category = "OpenSwitch")
	// void UpdateDoor02Location(float Z);

};

