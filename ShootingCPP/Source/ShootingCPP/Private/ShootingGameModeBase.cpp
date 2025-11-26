// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "Components/TextBlock.h"
#include "MenuWidget.h"
#include <Kismet/GameplayStatics.h>

void AShootingGameModeBase::BeginPlay() {

	Super::BeginPlay();

	if (mainWidget != nullptr) {
		mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);


		if (mainUI != nullptr) {
			mainUI->AddToViewport();
		}

	}





}




void AShootingGameModeBase::AddScore(int32 point) {
	currentScore += point;
	PrintScore();
}


void AShootingGameModeBase::PrintScore() {

	if (mainUI != nullptr) {

		mainUI->scoreData->SetText(FText::AsNumber(currentScore));
	}

}

void AShootingGameModeBase::ShowMenu() {

	if (menuWidget != nullptr) {

		menuUI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

		if (menuUI != nullptr) {
			menuUI->AddToViewport();

			UGameplayStatics::SetGamePaused(GetWorld(), true);


			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);




		}


	}



}