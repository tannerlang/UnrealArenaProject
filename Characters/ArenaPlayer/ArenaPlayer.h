//Arena.h

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

	bool IsWalking();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpAtRate;

	//crouch decs: check "Can Crouch" in editor in CharacterMovementComponent details pane.
	UFUNCTION()
	void StartCrouch();

	UFUNCTION()
	void StopCrouch();

	//walk decs
	UFUNCTION()
	void StartWalk();

	UFUNCTION()
	void StopWalk();

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MaxCrouchspeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float DefaultSpeed;

	//used to set the Ground Friction value
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float SlowStop;

	//used to set braking deceleration walking value
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float ConstantDecel;

	//used to set JumpZVelocity
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float JumpSpeed;

	//used to set AirControl
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float AirMovement;

	//to set a new gravity default
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Grav;

	
	
	//refactor strafing and forward movement to where a strafe and mouse movement to that direction can slightly maintain forward velocity in midair, 
	//print on screen debug message, get velocity.
		//eventually transfer it over as a option in the hud. but for now, just using debug helper.
	//modify CharacterMovementComponent::CalcVelocity() ???s
		//limit the velocity that is the proction of the current velocity on acceleration
		//no air friction on landing friction (bhop basics), and dont tick friction on landing frame, use DotProduct with
	//start anims

public:
	//return FPSMesh subobject
	USkeletalMeshComponent* GetFPSMesh() const { return FPSMesh; }

	//return FPCameraComp subobject
	UCameraComponent* GetFPCameraComp() const { return FPCameraComp; }

private:

	bool bIsWalking;
};
