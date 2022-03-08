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

	//������
	//�׽�Ʈ ������Ʈ�� �ʱ� ����
	Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}

	//�ݸ��� ���� ����
	Trigger->SetCapsuleHalfHeight(75.0f);
	Trigger->SetCapsuleRadius(55.0f);

	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
	//���� �ݸ����� Object�� ���� 
	Trigger->SetCollisionProfileName(TEXT("Object"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	

	//�Ӽ� UI ����
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

	//�ʱ� HP ����
	MaxHP = 300.0f;
	CurrentHP = MaxHP;
	//HP Bar UI ���� 
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
  
	//�÷��̾��� ī�޶� ��ǥ�� ���� ������ ��ǥ�� ���� ������ ī�޶� �ٶ󺸵��� 
	FRotator CameraRot=UKismetMathLibrary::FindLookAtRotation(AttributeWidget->GetComponentTransform().GetLocation(), 
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());

	// Yaw ���� ��ȯ�Ͽ� ������ ī�޶� �����
	AttributeWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw,0.0f));
	HpBarWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));
}

// Called when the game starts or when spawned
void ATestObject::BeginPlay()
{
	Super::BeginPlay();

	//������ �Ӽ��� ���� �� ����
	auto AttributeUI = Cast<UIreneAttributeWidget>(AttributeWidget->GetUserWidgetObject());
	if (nullptr != AttributeUI)
	{
		AttributeUI->BindCharacterAttribute(Attribute);
	}
	//Hp bar ���� �ʱ� ����
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

	//Ʈ������ �ݸ��� �浹�� ���� 
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATestObject::OnAttackedOverlap);
}

//hp ����
void ATestObject::SetHp(float ATK)
{

	CurrentHP -= ATK;
	//HP��ȭ ��������Ʈ�� ȣ�� 
	OnHpChanged.Broadcast();
	STARRYLOG(Error, TEXT("HP : %f"), CurrentHP);
	if (CurrentHP <= 0.0f)
	{
		//���� ����
		SpawnEenmy();

		//hp�� 0 �̸��̵Ǹ� �ı�
		Destroy();
	}
	
}

void ATestObject::OnAttackedOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STARRYLOG(Warning, TEXT("Hit"));

	auto Player = Cast<AIreneCharacter>(OtherActor);  // �΋H�� ������Ʈ�� �ش� ĳ���ͷ� ĳ���� 



	//�Ӽ��� ���� ���� ���� üũ 
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


	FVector2D random = FMath::RandPointInCircle(300.0f); //�߽� ���� 300�ݰ��� �� �ȿ� ���� ����Ʈ
	UE_LOG(LogTemp, Warning, TEXT("CreateBox x : %f y : %f"), random.X, random.Y); //

	// ���� ��ǥ�� ������ 50���� ������ 50�� ���ؼ� �߽ɺ��� �־�������
	if (FMath::Abs(random.X) < 50.0f)
	{
		random.X > 0.0f ? random.X += 50.0f : random.X -= 50.0f;
	}
	if (FMath::Abs(random.Y) < 50.0f)
	{
		random.Y > 0.0f ? random.Y += 50.0f : random.Y -= 50.0f;
	}
	UE_LOG(LogTemp, Warning, TEXT("CreateBox x : %f y : %f"), random.X, random.Y); //

	GetWorld()->SpawnActor<AEnemy>(GetActorLocation() + FVector(random, 0.0f), FRotator::ZeroRotator); // �� ���� ����


}

float ATestObject::GetHpRatio()
{
	//���� HP�� 0.0~1.0�� ������ ��ȯ�Ͽ� ��ȯ
	return (CurrentHP < KINDA_SMALL_NUMBER) ? 0.0f : CurrentHP / MaxHP;
}

// Called every frame

