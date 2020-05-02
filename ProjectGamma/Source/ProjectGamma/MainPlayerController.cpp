// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay(); 
	
	if (HUDOverlayAsset)
	{
		// Set HUDOverlay to the item selected via drop down menu in Blueprint
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}

	HUDOverlay->AddToViewport(); 
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);
}
