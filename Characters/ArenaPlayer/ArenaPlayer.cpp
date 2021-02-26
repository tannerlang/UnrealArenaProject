// Create Character Pawn
	//getplayercontroller
		//AutoPossessPlayer = EAutoReceiveInput::Player0;
	//create movement
		//non-rigid body physics
		//character movement component
			//setup CharacterMovementComponent properties.
	//create mesh
		//skeletal mesh component
		//skeletal mesh animation
			//root motion params for CharacterMovementComponent.
	//create collision
		//capsule component
			//trigger capsule
			//collisions with static mesh
	//create camera component	
		//setup fov
		

#include "ArenaPlayer.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
AArenaPlayer::AArenaPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//default possess.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	BaseTurnRate = 45.0f;
	BaseLookUpAtRate = 45.0f;
}

// Called when the game starts or when spawned
void AArenaPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArenaPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AArenaPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//parent class wrapper to use the character default jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AArenaPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AArenaPlayer::MoveRight);

	//for mouse input
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//for controller input
	PlayerInputComponent->BindAxis("TurnAtRate", this, &AArenaPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpAtRate", this, &AArenaPlayer::LookUpAtRate);
}

//Forward definition, how this character moves forward.
void AArenaPlayer::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

//Move right def, how this character moves left to right
void AArenaPlayer::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

//turnatrate def, how this character turns
void AArenaPlayer::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

//lookupatrate def, how this character loops up and down
void AArenaPlayer::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}