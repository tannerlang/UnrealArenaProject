// Create Character Pawn
	//getplayercontroller	X
		//AutoPossessPlayer = EAutoReceiveInput::Player0;	X
	//create movement	X
		//non-rigid body physics
		//character movement component 
			//setup CharacterMovementComponent properties.
	//create mesh
		//skeletal mesh component
		//skeletal mesh animation
			//root motion params for CharacterMovementComponent.
	//create collision	
		//capsule component		X
			//trigger capsule	X
			//collisions with static mesh
	//create camera component	X
		//setup fov		
		

#include "ArenaPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AArenaPlayer::AArenaPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//setup camera
	FPCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCameraComp->SetupAttachment(GetCapsuleComponent());
	FPCameraComp->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));	//cam position
	FPCameraComp->bUsePawnControlRotation = true;	//for control


	//setup first person skeletal mesh
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPS Mesh"));
	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(FPCameraComp);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;
	FPSMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	FPSMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));


	//setup triggercapsule
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);


	//default possess.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//init movmt vals
	BaseTurnRate = 45.0f;
	BaseLookUpAtRate = 45.0f;

	//init movmt vals
	MaxCrouchspeed = 100.f;
	WalkSpeed = 250.f;
	DefaultSpeed = 500.f;
	SlowStop = 1.62f;
	ConstantDecel = GetCharacterMovement()->MaxAcceleration * 0.5;
	JumpSpeed = DefaultSpeed;
	AirMovement = 1;
	
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = MaxCrouchspeed;
	GetCharacterMovement()->GroundFriction = SlowStop;
	GetCharacterMovement()->BrakingDecelerationWalking = ConstantDecel;
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;
	GetCharacterMovement()->AirControl = AirMovement;
	
	
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

	//crouch
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AArenaPlayer::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AArenaPlayer::StopCrouch);

	//walk
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AArenaPlayer::StartWalk);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &AArenaPlayer::StopWalk);

	//move
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

void AArenaPlayer::StartWalk()
{
	if (!bIsCrouched)
	{
		bIsWalking = true;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AArenaPlayer::StopWalk()
{
	if (!bIsCrouched)
	{
		bIsWalking = false;
		GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
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

//startcrouch def
void AArenaPlayer::StartCrouch()
{
	
	GetCharacterMovement()->MaxWalkSpeedCrouched = MaxCrouchspeed;
	Crouch();
	
}

//stop crouch def
void AArenaPlayer::StopCrouch()
{
	UnCrouch();
}

bool AArenaPlayer::IsWalking()
{
	return bIsWalking;
}

