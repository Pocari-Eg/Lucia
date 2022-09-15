// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeObject.h"
#include"../PlayerSource/IreneCharacter.h"
#include"../PlayerSource/PlayerInstance/IreneAttackInstance.h"

AAttributeObject::AAttributeObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = GetCapsuleComponent();
	ObjectMesh->SetupAttachment(RootComponent);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (SM_MESH.Succeeded())
	{
		ObjectMesh->SetStaticMesh(SM_MESH.Object);
	}

	//콜리전 영역 설정
	GetCapsuleComponent()->SetCapsuleHalfHeight(150.0f);
	GetCapsuleComponent()->SetCapsuleRadius(55.0f);


	ObjectMesh->SetRelativeLocation(GetActorLocation()+FVector(0.0f, 0.0f, -185.0f));
	//현재 콜리전을 Object로 설정 
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	ObjectMesh->SetCollisionProfileName(TEXT("NoCollision"));



	bIsObject = true;


}

void AAttributeObject::SetObject(EState NewState, EAttributeKeyword NewAttribute)
{
	STARRYLOG_S(Error);
	State = NewState;
	Attribute = NewAttribute;

	if (State == EState::e_Constant || State == EState::e_Activate)
	{
		IsActive = true;
	}
	else {
		IsActive = false;
	}

	MaterialChange();
}

EAttributeKeyword AAttributeObject::GetAttribute()
{
	return Attribute;
}

 void AAttributeObject::HitCheck(AIreneCharacter* Irene)
{
	STARRYLOG(Warning, TEXT("Hit"));
	if (State != EState::e_Constant) {
		if (Irene != nullptr) {

			//속성에 따라 공격 가능 체크 
			SetObject(EState::e_Activate, EAttributeKeyword::e_Fire);				
		}
	}
	
	OnActiveCheck.Broadcast();
}

 bool AAttributeObject::GetActive()
 {
	 return IsActive;
 }

 void AAttributeObject::TriggerOff()
 {
	 GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
 }

 // Called when the game starts or when spawned
void AAttributeObject::BeginPlay()
{
	Super::BeginPlay();
	MonsterWidget->Activate(false);
	MonsterInfo.M_Max_HP = 9999999.0f;
	SoundInstance->SetHitSound("event:/StarryTail/Enemy/SFX_Hit");
}

void AAttributeObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

