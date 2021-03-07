//slate menu widget

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class SMainMenu: public SCompoundWidget
{

public:

	//reference hud
	SLATE_BEGIN_ARGS(SMainMenu) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class APlayerHUD>, OwningHUD)
	
	SLATE_END_ARGS()

	//widget construction function
	void Construct(const FArguments& InArgs);


	FReply OnPlayClicked() const;
	FReply OnQuitClicked() const;

	//hud that created this widget
	TWeakObjectPtr<class APlayerHUD> OwningHUD;

	//widget supports keyboard focus.
	virtual bool SupportsKeyboardFocus() const override { return true; };
};
