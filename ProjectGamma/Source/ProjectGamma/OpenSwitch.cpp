// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AOpenSwitch::AOpenSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	// Set collisions for TriggerBox - QueryOnly detects Overlap Events only.  Will not block or call physics 
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	// Set the ObjectType for TriggerBox to WorldStatic
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

	// Not fire any event when overlap with anything
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	// Fire overlap event when overlap with a Pawn
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// Set size of TriggerBox
	TriggerBox->SetBoxExtent(FVector(62.0f, 62.0f, 32.0f));


	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitch"));
	FloorSwitch->SetupAttachment(GetRootComponent());

	DoorMesh01 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh01"));
	DoorMesh01->SetupAttachment(GetRootComponent());

	DoorMesh02 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh02"));
	DoorMesh02->SetupAttachment(GetRootComponent());

	bIsDoorMesh02Set = false; 
	bIsFloorSwitchMeshSet = false; 
}

// Called when the game starts or when spawned
void AOpenSwitch::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AOpenSwitch::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AOpenSwitch::OnOverlapEnd);

	InitialDoor01Location = DoorMesh01->GetComponentLocation();
	InitialDoor02Location = DoorMesh02->GetComponentLocation();
	InitialSwitchLocation = FloorSwitch->GetComponentLocation(); 
	
}

// Called every frame
void AOpenSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOpenSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin."));
	OpenDoor();
	LowerFloorSwitch();
}

void AOpenSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End."));
	CloseDoor(); 
	RaiseFloorSwitch();
}

void AOpenSwitch::UpdateDoor01Location(FVector DoorDirection)
{
	FVector NewDoor01Location = InitialDoor01Location;
	NewDoor01Location += DoorDirection;
	DoorMesh01->SetWorldLocation(NewDoor01Location); 

	if (bIsDoorMesh02Set)
	{
		FVector NewDoor02Location = InitialDoor02Location;
		NewDoor02Location -= DoorDirection;
		DoorMesh02->SetWorldLocation(NewDoor02Location);
	}
}

void AOpenSwitch::UpdateFloorSwitchLocation(float Value)
{
	FVector NewFloorSwitchLocation = InitialSwitchLocation;
	NewFloorSwitchLocation.Z += Value;
	FloorSwitch->SetWorldLocation(NewFloorSwitchLocation);
	
}
