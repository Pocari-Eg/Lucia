// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeObject.h"
#include"../PlayerSource/IreneAttackInstance.h"
#include "../PlayerSource/IreneCharacter.h"

// Sets default values
AAttributeObject::AAttributeObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}

	//콜리전 영역 설정
	Trigger->SetCapsuleHalfHeight(75.0f);
	Trigger->SetCapsuleRadius(55.0f);

	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
	//현재 콜리전을 Object로 설정 
	Trigger->SetCollisionProfileName(TEXT("Object"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	SetObject(EState::e_Disabled, EAttributeKeyword::e_None);
}

void AAttributeObject::SetObject(EState NewState, EAttributeKeyword NewAttribute)
{
	State = NewState;
	Attribute = NewAttribute;
}

EAttributeKeyword AAttributeObject::GetAttribute()
{
	return Attribute;
}

// Called when the game starts or when spawned
void AAttributeObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAttributeObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//트리거의 콜리전 충돌시 실행 
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AAttributeObject::OnAttackedOverlap);
}

void AAttributeObject::OnAttackedOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STARRYLOG(Warning, TEXT("Hit"));
	if (State != EState::e_Constant) {

		auto Irene = Cast<AIreneCharacter>(OtherActor);  // 부딫힌 오브젝트를 해당 캐릭터로 캐스팅 
		if (Irene != nullptr) {

			//속성에 따라 공격 가능 체크 
			switch (Irene->IreneAttack->GetAttribute())
			{
			case EAttributeKeyword::e_Fire:
				SetObject(EState::e_Activate, EAttributeKeyword::e_Fire);
				break;
			case EAttributeKeyword::e_Water:
				SetObject(EState::e_Activate, EAttributeKeyword::e_Water);
				break;
			case EAttributeKeyword::e_Thunder:
				SetObject(EState::e_Activate, EAttributeKeyword::e_Thunder);
				break;
			default:
				break;
			}
		}

		OnAnswerCheck.Broadcast();
	}
}



