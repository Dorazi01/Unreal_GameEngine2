// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingTestActor.generated.h"

UCLASS()
class SHOOTINGCPP_API ACodingTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodingTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 number1 = 10;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//int32 number1 = 10;

	
	
	int32 number2 = 30;
	
	
	
	//FString name = "Jung Woo Young";
	UPROPERTY(EditInstanceOnly)
	FString name = TEXT("정우영");

	UPROPERTY(EditAnywhere)
	bool isReady = true;
	bool isFinished = false;

	UFUNCTION(BlueprintPure)
	int32 Add(int32 num1, int32 num2);

};
