// Fill out your copyright notice in the Description page of Project Settings.

//derive from APlayerController
//setup inputs
	//define handler function
		//delegate implementation to pawn during runtime, when possessing
//store persistant player info through game
	//score
//setup camera properties for when unposess
//setup hud
	//speedometer
		//create new widget class
	

//tell GameMode to use custom player controller

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ArenaPlayerController.generated.h"

UCLASS()

class ARENA_API ArenaPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:

	ArenaPlayerController();

	virtual void SetupInputComponent() override;

	void OpenMenu();
};
