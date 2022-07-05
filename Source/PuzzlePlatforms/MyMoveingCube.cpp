// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMoveingCube.h"

AMyMoveingCube::AMyMoveingCube()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMyMoveingCube::AddActivePlatforms()
{
	ActiveTriggers++;
}

void AMyMoveingCube::RemoveActivePlatforms()
{
	ActiveTriggers--;
	if (ActiveTriggers < 0) ActiveTriggers = 0;
}

void AMyMoveingCube::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		GlobalStartLocation = GetActorLocation();
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	}
}

void AMyMoveingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ActiveTriggers > 0 && HasAuthority())
	{
		float Length = (GlobalTargetLocation - GlobalStartLocation).Size();
		float NowLength = (GetActorLocation() - GlobalStartLocation).Size();
		if (NowLength > Length)
		{
			FVector temp = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = temp;
		}
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
}