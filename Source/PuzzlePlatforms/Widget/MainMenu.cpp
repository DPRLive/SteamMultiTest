// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::GoHostMenu);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::GoJoinMenu);

	if (!ensure(CancelJoinMenuButton != nullptr)) return false;
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::BackMainMenu);

	if (!ensure(JoinButton2 != nullptr)) return false;
	JoinButton2->OnClicked.AddDynamic(this, &UMainMenu::JoinClient);

	if (!ensure(QuitGame != nullptr)) return false;
	QuitGame->OnClicked.AddDynamic(this, &UMainMenu::QuitClicked);

	if (!ensure(HostCancel != nullptr)) return false;
	HostCancel->OnClicked.AddDynamic(this, &UMainMenu::BackMainMenu);

	if (!ensure(HostHostButton != nullptr)) return false;
	HostHostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	return true;
}

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UServerRow> ServerRowBPClass(TEXT("/Game/MenuSystem/BP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;
	ServerRow = ServerRowBPClass.Class;
}

void UMainMenu::HostServer() {
	UE_LOG(LogTemp, Warning, TEXT("HOST! HOST! HOST!"));

	if (MenuInterface == nullptr) return;
	MenuInterface->Host(ServerHostName->GetText().ToString());
}

void UMainMenu::GoHostMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(HostMenuWidget != nullptr)) return;
	MenuSwitcher->SetActiveWidget(HostMenuWidget);
}

void UMainMenu::GoJoinMenu() {
	UE_LOG(LogTemp, Warning, TEXT("JOIN! JOIN! JOIN!"));

	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenuWidget != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenuWidget);
	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshServerList();
	}
}

void UMainMenu::BackMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenuWidget != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenuWidget);
}

void UMainMenu::JoinClient()
{
	if (SelectedIndex.IsSet() && MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Select index : %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index not set"));
	}
}

void UMainMenu::QuitClicked()
{
	if (MenuInterface == nullptr) return;
	MenuInterface->QuitAGame();
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Teardown();
}

void UMainMenu::SetServerList(TArray<FServerData> ServerDatas)
{
	if (!ensure(SessionList != nullptr)) return;
	SessionList->ClearChildren();

	uint32 i = 0;
	for (const FServerData& ServerData : ServerDatas)
	{
		UServerRow* Row = CreateWidget<UServerRow>(this, ServerRow);
		if (!ensure(Row != nullptr)) return;

		Row->ServerName->SetText(FText::FromString(ServerData._Name));
		Row->HostUserName->SetText(FText::FromString(ServerData._HostUserName));
		FString CurrentPlayers = FString::FromInt(ServerData._CurrentPlayers) + "/";
		FString MaxPlayers = FString::FromInt(ServerData._MaxPlayers);
		Row->Players->SetText(FText::FromString(CurrentPlayers + MaxPlayers));
		Row->Setup(this, i);
		i++;

		SessionList->AddChild(Row);
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	for (int32 i = 0; i < SessionList->GetChildrenCount(); i++)
	{
		auto Row = Cast<UServerRow>(SessionList->GetChildAt(i)); 
		if (Row != nullptr)
		{
			Row->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}
