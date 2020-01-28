// Fill out your copyright notice in the Description page of Project Settings.


#include "TittleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTittleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BTN_Start = Cast<UButton>(GetWidgetFromName(TEXT("Button_Start")));
	if (BTN_Start == nullptr)
	{
		EGLOG(Error, TEXT("Start Button not initiailize"));
		return;
	}
	BTN_Load= Cast<UButton>(GetWidgetFromName(TEXT("Button_Load")));
	if (BTN_Load == nullptr)
	{
		EGLOG(Error, TEXT("Load Button not initiailize"));
		return;
	}

	BTN_Option= Cast<UButton>(GetWidgetFromName(TEXT("Button_Option")));
	if (BTN_Option == nullptr)
	{
		EGLOG(Error, TEXT("Option Button not initiailize"));
		return;
	}
	BTN_Exit= Cast<UButton>(GetWidgetFromName(TEXT("Button_Exit")));
	if (BTN_Exit == nullptr)
	{
		EGLOG(Error, TEXT("Exit Button not initiailize"));
		return;
	}

	BTN_Start->OnClicked.AddDynamic(this, &UTittleWidget::StartNew);
	BTN_Load->OnClicked.AddDynamic(this, &UTittleWidget::LoadGame);
	BTN_Option->OnClicked.AddDynamic(this, &UTittleWidget::OpenOption);
	BTN_Exit->OnClicked.AddDynamic(this, &UTittleWidget::ExitGame);
}

void UTittleWidget::StartNew()
{
	EGLOG(Warning, TEXT("Click!"));
	EGLOG(Warning, TEXT("Current Game Mode : %s"), *GetWorld()->GetFirstPlayerController()->GetName());
	FName LevelName = TEXT("/Game/MyFolder/Maps/Stage1");
	//FString LevelOption = TEXT("Class'/Script/EscapeGame.EscapeGameGameModeBase_C'");
	UGameplayStatics::OpenLevel(this, LevelName,true);
	GetWorld()->SetGameMode(TEXT("Class'/Script/EscapeGame.EscapeGameGameModeBase_C'"));
	EGLOG(Warning, TEXT("Current Game Mode : %s"), *GetWorld()->GetFirstPlayerController()->GetName());
}

void UTittleWidget::LoadGame()
{
	EGLOG(Warning, TEXT("Click!"));
}

void UTittleWidget::OpenOption()
{
	EGLOG(Warning, TEXT("Click!"));
}

void UTittleWidget::ExitGame()
{
	EGLOG(Warning, TEXT("Click!"));
}
