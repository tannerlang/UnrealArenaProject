//Widget for speed to be displayed on player HUD.

//In Widget Designer set add text box
//add Module of UTextBlock to build.cs i think
//Here, create function to get velocity value
	//access designer textbox

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerSpeed.generated.h"

//forward declaration
class UTextBlock;

UCLASS()
class ARENA_API UPlayerSpeed : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	//UPROPERTY BindWidget allows to bind to a widget of the same name in a blueprint subclass of UPlayerSpeed at runtime.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Speedometer;




private:

};
