// Fill out your copyright notice in the Description page of Project Settings.


#include "TestObject.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"


// Sets default values
ATestObject::ATestObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//박찬영
	//테스트 오브젝트의 초기 설정
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

	

	//속성 UI 설정
	AttributeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ATTRIBUTEWIDGET"));
	AttributeWidget->SetupAttachment(Mesh);
	AttributeWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	AttributeWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	AttributeWidget->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_ATTRIBUTEWIDGET(TEXT("/Game/Developers/Pocari/Collections/Widget/BP_AttributesWidget.BP_AttributesWidget_C"));

	if (UI_ATTRIBUTEWIDGET.Succeeded()) {

		AttributeWidget->SetWidgetClass(UI_ATTRIBUTEWIDGET.Class);
		AttributeWidget->SetDrawSize(FVector2D(20.0f, 20.0f));
	
	}

	//초기 HP 설정
	MaxHP = 300.0f;
	CurrentHP = MaxHP;
	//HP Bar UI 설정 
	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HpBarWidget->SetupAttachment(Mesh);
	HpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	HpBarWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	HpBarWidget->SetWidgetSpace(EWidgetSpace::World);
	
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBARWIDGET(TEXT("/Game/Developers/Pocari/Collections/Widget/BP_HPBar.BP_HPBar_C"));

	if (UI_HPBARWIDGET.Succeeded()) {

		HpBarWidget->SetWidgetClass(UI_HPBARWIDGET.Class);
		HpBarWidget->SetDrawSize(FVector2D(150, 50.0f));

	}
}

void ATestObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
	//플레이어의 카메라 좌표와 현재 위젯의 좌표를 통해 위젯이 카메라를 바라보도록 
	FRotator CameraRot=UKismetMathLibrary::FindLookAtRotation(AttributeWidget->GetComponentTransform().GetLocation(), 
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());

	// Yaw 값만 변환하여 위젯이 카메라를 따라옴
	AttributeWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw,0.0f));
	HpBarWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
}

// Called when the game starts or when spawned
void ATestObject::BeginPlay()
{
	Super::BeginPlay();

	//위젯에 속성에 따른 색 설정
	auto AttributeUI = Cast<UIreneAttributeWidget>(AttributeWidget->GetUserWidgetObject());
	if (nullptr != AttributeUI)
	{
		AttributeUI->BindCharacterAttribute(Attribute);
	}
	//Hp bar 위젯 초기 세팅
	auto HPBarUI = Cast<UHPBarWidget>(HpBarWidget->GetUserWidgetObject());
	if (nullptr != HPBarUI)
	{
		HPBarUI->BindObjectHp(this);
	}

	STARRYLOG_S(Error);
}

void ATestObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//트리거의 콜리전 충돌시 실행 
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATestObject::OnAttackedOverlap);
}

//hp 설정
void ATestObject::SetHp(float ATK)
{

	CurrentHP -= ATK;
	//HP변화 델리게이트를 호출 
	OnHpChanged.Broadcast();
	STARRYLOG(Error, TEXT("HP : %f"), CurrentHP);
	if (CurrentHP <= 0.0f)
	{
		//몬스터 스폰
		SpawnEenmy();

		//hp가 0 미만이되면 파괴
		Destroy();
	}
	
}

void ATestObject::OnAttackedOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STARRYLOG(Warning, TEXT("Hit"));

	auto Player = Cast<AIreneCharacter>(OtherActor);  // 부딫힌 오브젝트를 해당 캐릭터로 캐스팅 



	//속성에 따라 공격 가능 체크 
	switch (Attribute)
	{
	case EAttributeKeyword::e_Fire:

		if (Player->GetAttribute() == EAttributeKeyword::e_Water)
		{
			SetHp(Player->GetATK());
		}
		break;
	case EAttributeKeyword::e_Water:
		if (Player->GetAttribute() == EAttributeKeyword::e_Thunder)
		{
			SetHp(Player->GetATK());
		}
		break;
	case EAttributeKeyword::e_Thunder:
		if (Player->GetAttribute() == EAttributeKeyword::e_Fire)
		{
			SetHp(Player->GetATK());
		}
		break;
	default:
		break;
	}
}

void ATestObject::SpawnEenmy()
{


	FVector2D random = FMath::RandPointInCircle(300.0f); //중심 기준 300반경의 원 안에 랜덤 포인트
	UE_LOG(LogTemp, Warning, TEXT("CreateBox x : %f y : %f"), random.X, random.Y); //

	// 랜덤 좌표의 절댓값이 50보다 작으면 50을 더해서 중심보다 멀어지도록
	if (FMath::Abs(random.X) < 50.0f)
	{
		random.X > 0.0f ? random.X += 50.0f : random.X -= 50.0f;
	}
	if (FMath::Abs(random.Y) < 50.0f)
	{
		random.Y > 0.0f ? random.Y += 50.0f : random.Y -= 50.0f;
	}
	UE_LOG(LogTemp, Warning, TEXT("CreateBox x : %f y : %f"), random.X, random.Y); //

	GetWorld()->SpawnActor<AEnemy>(GetActorLocation() + FVector(random, 0.0f), FRotator::ZeroRotator); // 새 엑터 생성


}

float ATestObject::GetHpRatio()
{
	//현재 HP를 0.0~1.0의 비율로 변환하여 반환
	return (CurrentHP < KINDA_SMALL_NUMBER) ? 0.0f : CurrentHP / MaxHP;
}

// Called every frame

