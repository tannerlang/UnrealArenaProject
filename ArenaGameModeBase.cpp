//Arena


#include "ArenaGameModeBase.h"
#include "ArenaPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "ArenaPlayerController.h"
#include "PlayerHUD.h"

//Constructor
AArenaGameModeBase::AArenaGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerClass(TEXT("/Classes_Game/Arena/ArenaPlayer"));
	if (PlayerClass.Class != NULL)
	{
		DefaultPawnClass = PlayerClass.Class;
	}
	//use ArenaPlayerController
	PlayerControllerClass = ArenaPlayerController::StaticClass();
	HUDClass = APlayerHUD::StaticClass();
}

