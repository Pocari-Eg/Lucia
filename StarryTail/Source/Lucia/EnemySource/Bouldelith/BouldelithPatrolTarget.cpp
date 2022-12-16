// Fill out your copyright notice in the Description page of Project Settings.


#include "BouldelithPatrolTarget.h"

// Sets default values
ABouldelithPatrolTarget::ABouldelithPatrolTarget()
{
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
	Collision->SetCollisionProfileName(TEXT("NoCollision"));

	RootComponent = Collision;
}



