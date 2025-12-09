// Fill out your copyright notice in the Description page of Project Settings.


#include "HpItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AHpItem::AHpItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

	SetRootComponent(boxComp);

	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	meshComp->SetupAttachment(boxComp);

	boxComp->SetCollisionProfileName(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AHpItem::BeginPlay()
{
	Super::BeginPlay();

	/*
	int32 drawResult = FMath::RandRange(1, 100);

	if (drawResult <= traceRate) {


		//월드 공간에 APlayerPawn클래스로 된 액터를 모두 검색한다?

		//Object.FindObjectsOfType<T>()와 똑같이 구현가능

		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player) {

			if (player->GetName().Contains(TEXT("BP_PlayerPawn"))) {
				dir = player->GetActorLocation() - GetActorLocation();
				dir.Normalize();
			}
		}
	}*/
	
		dir = GetActorForwardVector();
		//아이템은 무조건 아래로 떨어짐


	

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AHpItem::OnItemOverlap);




}

// Called every frame
void AHpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;

	SetActorLocation(newLocation);
}


void AHpItem::OnItemOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	{
	
		if (player) {
				player->TakeHeal(1);
				Destroy();
		}
	}
}
