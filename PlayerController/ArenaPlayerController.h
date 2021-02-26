// Fill out your copyright notice in the Description page of Project Settings.

//derive from APlayerController
//setup inputs
	//define handler function
		//delegate implementation to pawn during runtime, when possessing
//store persistant player info through game
	//score
//setup camera properties for when unposess
//setup hud

//tell GameMode to use custom player controller

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArenaPlayerController.generated.h"

UCLASS()

class ARENA_API ArenaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ArenaPlayerController();
	~ArenaPlayerController();

protected:

	virtual void SetupInputComponent(class UInputComponent* InInputComponent);

	void MoveForward(float Value);


};
