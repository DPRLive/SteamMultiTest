// Fill out your copyright notice in the Description page of Project Settings.


#include "VolumeTrigger.h"

// Sets default values
AVolumeTrigger::AVolumeTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TiggerVolume"));

	if (!ensure(TriggerVolume != nullptr)) return;
	RootComponent = TriggerVolume;
}

// Called when the game starts or when spawned
void AVolumeTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AVolumeTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AVolumeTrigger::OnOverlapEnd);
}

// Called every frame
void AVolumeTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVolumeTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (auto elem : MyCubeArr)
	{
		elem->AddActivePlatforms();
	}
}

void AVolumeTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (auto elem : MyCubeArr)
	{
		elem->RemoveActivePlatforms();
	}
}

