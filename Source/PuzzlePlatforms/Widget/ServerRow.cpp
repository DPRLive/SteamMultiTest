// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "MainMenu.h"

#include "Components/Button.h"

void UServerRow::Setup(UMainMenu* Menu, uint32 Index)
{
	_Menu = Menu;
	_Index = Index;

	if (!ensure(RowButton != nullptr)) return;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::SetMainMenuIndex);
}

void UServerRow::SetMainMenuIndex()
{
	_Menu->SelectIndex(_Index);
}
