// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MenuInterface.h"
#include "MenuWidget.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* InGameCancelButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* IntGameMainMenuButton;

	UFUNCTION()
		void CancelMenu();

	UFUNCTION()
		void QuitMenu();
public:

};
