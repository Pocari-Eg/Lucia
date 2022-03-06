// Fill out your copyright notice in the Description page of Project Settings.


#include "TestObject.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>

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
	Trigger->SetCapsuleHalfHeight(85.0f);
	Trigger->SetCapsuleRadius(65.0f);

	Trigger->SetCollisionProfileName(TEXT("Object"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	

	

	//ui 설정
	AttributeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ATTRIBUTEWIDGET"));
	AttributeWidget->SetupAttachment(Mesh);
	AttributeWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 95.0f));
	AttributeWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	AttributeWidget->SetWidgetSpace(EWidgetSpace::World);

	AttributeWidget2 = CreateDefaultSubobject<UWidgetComponent>(TEXT("ATTRIBUTEWIDGET2"));
	AttributeWidget2->SetupAttachment(Mesh);
	AttributeWidget2->SetRelativeLocation(FVector(0.0f, 0.0f, 95.0f));
	AttributeWidget2->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	AttributeWidget2->SetWidgetSpace(EWidgetSpace::World);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Developers/Pocari/Collections/Widget/BP_AttributesWidget.BP_AttributesWidget_C"));

	if (UI_HUD.Succeeded()) {

		AttributeWidget->SetWidgetClass(UI_HUD.Class);
		AttributeWidget->SetDrawSize(FVector2D(20.0f, 20.0f));
		AttributeWidget2->SetWidgetClass(UI_HUD.Class);
		AttributeWidget2->SetDrawSize(FVector2D(20.0f, 20.0f));
	}

	
}

void ATestObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AttributeWidget->AddLocalRotation(FRotator(0.0f, 100.0f * DeltaTime, 0.0f));
	AttributeWidget2->AddLocalRotation(FRotator(0.0f, 100.0f * DeltaTime, 0.0f));

}

// Called when the game starts or when spawned
void ATestObject::BeginPlay()
{
	Super::BeginPlay();


	auto Widget = Cast<UIreneAttributeWidget>(AttributeWidget->GetUserWidgetObject());
	if (nullptr != Widget)
	{
		Widget->BindCharacterAttribute(Attribute);
	}
	auto Widget2 = Cast<UIreneAttributeWidget>(AttributeWidget2->GetUserWidgetObject());
	if (nullptr != Widget2)
	{
		Widget2->BindCharacterAttribute(Attribute);
	}
}

void ATestObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Warning, TEXT("SPAWN"));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATestObject::OnAttackedOverlap);
}

void ATestObject::OnAttackedOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));

	auto Player = Cast<AIreneCharacter>(OtherActor);  // 부딫힌 오브젝트를 해당 캐릭터로 캐스팅 

	if (Player->GetAttribute() == Attribute)  // 키워드가 같으면 
	{
		UE_LOG(LogTemp, Warning, TEXT("KeyWord Same"));


		//FVector2D random = FMath::RandPointInCircle(300.0f); //중심 기준 300반경의 원 안에 랜덤 포인트
		//UE_LOG(LogTemp, Warning, TEXT("CreateBox x : %f y : %f"), random.X, random.Y); // 

		//if (FMath::Abs(random.X) < 50.0f)
		//{
		//	random.X > 0.0f ? random.X += 50.0f : random.X -= 50.0f;
		//}
		//if (FMath::Abs(random.Y) < 50.0f)
		//{
		//	random.Y > 0.0f ? random.Y += 50.0f : random.Y -= 50.0f;
		//}
		//UE_LOG(LogTemp, Warning, TEXT("CreateBox x : %f y : %f"), random.X, random.Y); // 

		//GetWorld()->SpawnActor<ATestObject>(GetActorLocation() + FVector(random, 0.0f), FRotator::ZeroRotator); // 새 엑터 생성

		Destroy();
	}
}

// Called every frame

