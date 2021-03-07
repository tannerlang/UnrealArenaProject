// APlayerHUD
//creating a speedometer
	//create widget to return the velocity of the player.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	


public:
	
	void ShowMenu();
	void RemoveMenu();


protected:
	//store ref to menu
	TSharedPtr<class SMainMenu> MenuWidget;
	//contain in this container to add and remove menu from speed.
	TSharedPtr<class SWidget> MenuWidgetContainer;						

	virtual void BeginPlay() override;


};
