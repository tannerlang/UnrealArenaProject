//work in progress
	//continue tomorrow 3/6


//run widget on tick.


#include "PlayerSpeed.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"



void UPlayerSpeed::NativeConstruct()
{
	Super::NativeConstruct();

	//speedometer is nullptr since I havent created it in the
	//blueprint subclass
	if (Speedometer != nullptr)
	{
		//need to get this all to be dynamic on tick
		FVector PlayerV = GetOwningPlayer()->GetPawn()->GetVelocity();
		FText TempText = FText::FromString(PlayerV.ToString());
		Speedometer->SetText(TempText);
	}
}

