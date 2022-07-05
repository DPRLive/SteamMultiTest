// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(InGameCancelButton != nullptr)) return false;
	InGameCancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelMenu);

	if (!ensure(IntGameMainMenuButton != nullptr)) return false;
	IntGameMainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitMenu);

	return true;
}

void UInGameMenu::CancelMenu()
{
	Teardown();
}

void UInGameMenu::QuitMenu()
{
	if (MenuInterface != nullptr)
	{
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}