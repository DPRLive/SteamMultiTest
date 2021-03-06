// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MenuInterface.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	IMenuInterface* MenuInterface;

public:
	void SetMenuInterface(IMenuInterface* MenuInterFace);
	void Setup();
	void Teardown();
};
