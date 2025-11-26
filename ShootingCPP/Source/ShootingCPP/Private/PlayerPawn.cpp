// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "Components/ArrowComponent.h"
#include "Bullet.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));

	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));

	meshComp->SetupAttachment(boxComp);


	FVector boxSize = FVector(50.f, 50.f, 50.f);
	boxComp->SetBoxExtent(boxSize);



	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Position"));
	firePosition->SetupAttachment(boxComp);


	// 이 줄은 연습용으로 사용해봄 :: boxComp->SetGenerateOverlapEvents(true); 로도 가능함
	(*boxComp).SetGenerateOverlapEvents(true);

	boxComp->SetCollisionObjectType(ECC_GameTraceChannel1);
	//ObjectType를 1번 채널로 설정함


	//모든 채널을 충돌없음으로 설정하고,
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);


	//에너미와는 충돌 이벤트를 체크한다.
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);



}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (!world)
		return;

	TObjectPtr<APlayerController> pc = world->GetFirstPlayerController();


	if (pc != nullptr) {
		//TObjectPtr은 선언에만 가능
		TObjectPtr<UEnhancedInputLocalPlayerSubsystem> subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());


		if (subsys != nullptr) {

			subsys->AddMappingContext(imc_playerInput, 0);
		}

	}

	
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector dir = FVector(0, h, v);

	dir.Normalize();

	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;

	SetActorLocation(newLocation,true);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	TObjectPtr<UEnhancedInputComponent> enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	if (enhancedInputComponent != nullptr) {
		
		enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputHorizontal);
		enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Completed, this, &APlayerPawn::OnInputHorizontal);
		enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputVertical);
		enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Completed, this, &APlayerPawn::OnInputVertical);


		enhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Started, this, &APlayerPawn::Fire);

	}




}



void APlayerPawn::OnInputHorizontal(const FInputActionValue& value) {
	//float hor = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("Horizontal: %.2f"), hor);
	h = value.Get<float>();
}

void APlayerPawn::OnInputVertical(const FInputActionValue& value) {
	//float ver = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("Vertical: %.2f"), ver);
	v = value.Get<float>();
}


void APlayerPawn::Fire() {
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());

	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);

}