// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArenaPlayer.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UCapsuleComponent;

UCLASS()
class ARENA_API AArenaPlayer : public ACharacter
{
	GENERATED_BODY()
	
	
	//skeletal mesh for fps
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;
	
	//capsule component
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	UCapsuleComponent* TriggerCapsule;	

	//camera comp
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"));
	UCameraComponent* FPCameraComp;


public:
	// Sets default values for this character's properties
	AArenaPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);
	void LookUpAtRate(float Value);
	
	//crouch decs: check "Can Crouch" in editor in CharacterMovementComponent details pane.
	void StartCrouch();
	void StopCrouch();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpAtRate;
	
	//return FPSMesh subobject
	USkeletalMeshComponent* GetFPSMesh() const { return FPSMesh; }

	//return FPCameraComp subobject
	UCameraComponent* GetFPCameraComp() const { return FPCameraComp; }
	
};
