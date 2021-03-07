// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaPlayerController.h"
#include "Actor.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "PlayerHUD.h"
#include "Arena/ArenaPlayer.h"


ArenaPlayerController::ArenaPlayerController()
{

}

void ArenaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("OpenMenu", IE_Pressed, this, &ArenaPlayerController::OpenMenu);
	}
}

void ArenaPlayerController::OpenMenu()
{
	if (APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetHUD()))
	{
		PlayerHUD->ShowMenu();
	}
}
