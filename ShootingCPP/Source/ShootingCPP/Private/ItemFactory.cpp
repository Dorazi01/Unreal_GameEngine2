// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFactory.h"
#include "HpItem.h"

// Sets default values
AItemFactory::AItemFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentTime > delayTime) {
		currentTime = 0.0f;


		// ->의 화살표 연산자는 c#의 점연산자와 똑같은 역할을 수행함,
		// C++에서도 점 연산자가 있지만, (*Getworld)().SpawnActor로 작성하기 번거로운 점이 존재함
		AHpItem* spawnActor = GetWorld()->SpawnActor<AHpItem>(item, GetActorLocation(), GetActorRotation());

	}
	else {
		currentTime += DeltaTime;


	}

}

