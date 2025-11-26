// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModeBase.generated.h"


class UMainWidget;

class UMenuWidget;

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void AddScore(int32 point);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> mainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMenuWidget> menuWidget;

	void ShowMenu();

protected:
	virtual void BeginPlay() override;



private:
	int32 currentScore = 0;
	
	TObjectPtr<UMainWidget> mainUI;


	TObjectPtr<UMenuWidget> menuUI;

	void PrintScore();

	

};
