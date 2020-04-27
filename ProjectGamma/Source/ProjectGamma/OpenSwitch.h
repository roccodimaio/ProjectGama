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
};

