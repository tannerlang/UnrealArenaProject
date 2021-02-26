// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaPlayerController.h"
#include "Actor.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Arena/ArenaPlayer.h"
#include "ArenaGameModeBase.h"

ArenaPlayerController::ArenaPlayerController()
{
}

ArenaPlayerController::~ArenaPlayerController()
{
}

//define handler function
		//delegate implementation to pawn during runtime, when possessing
void ArenaPlayerController::SetupInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupInputComponent();

	InInputComponent->BindAxis("Forward", this, &ArenaPlayerController::MoveForward);
}

//define forward
void ArenaPlayerController::MoveForward(float Value)
{
	
	auto player = Cast<AArenaPlayer>(this->GetCharacter());
	if (player)
	{
		player->MoveForward(Value);
	}
}