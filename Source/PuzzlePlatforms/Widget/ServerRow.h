// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

private:
	uint32 _Index = 0;

	class UMainMenu* _Menu;
	
	UPROPERTY(meta = (BindWidget))
		class UButton* RowButton;

	UFUNCTION()
		void SetMainMenuIndex();
public:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Players;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* HostUserName;

	void Setup(UMainMenu* Menu, uint32 Index);

	UPROPERTY(BlueprintReadOnly)
		bool Selected;
};
