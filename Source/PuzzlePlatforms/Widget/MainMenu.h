// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MenuInterface.h"
#include "MenuWidget.h"
#include "ServerRow.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString _Name;
	uint16 _CurrentPlayers;
	uint16 _MaxPlayers;
	FString _HostUserName;
};

UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	GENERATED_BODY()

protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
		UWidget* MainMenuWidget;

	UPROPERTY(meta = (BindWidget))
		UWidget* HostMenuWidget;

	UPROPERTY(meta = (BindWidget))
		UWidget* JoinMenuWidget;

	UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
		UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
		UButton* JoinButton2;

	UPROPERTY(meta = (BindWidget))
		UButton* CancelJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitGame;
	
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* SessionList;

	UPROPERTY(meta = (BindWidget))
		UButton* HostCancel;

	UPROPERTY(meta = (BindWidget))
		UButton* HostHostButton;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* ServerHostName;

	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void GoHostMenu();

	UFUNCTION()
		void GoJoinMenu();

	UFUNCTION()
		void BackMainMenu();

	UFUNCTION()
		void JoinClient();

	UFUNCTION()
		void QuitClicked();

	TSubclassOf<UServerRow> ServerRow;

	TOptional<uint32> SelectedIndex;
public:
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	void SetServerList(TArray<FServerData> ServerDatas);
	void SelectIndex(uint32 Index);
	void UpdateChildren();
};
