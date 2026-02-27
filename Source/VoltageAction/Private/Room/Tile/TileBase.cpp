#include "Room/Tile/TileBase.h"

ATileBase::ATileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// メッシュコンポーネントを作成してルートコンポーネントに設定
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	// コリジョンコンポーネントを作成
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);

	// ポーンとの衝突を有効
	BoxComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
}

void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	
	// メッシュの初期設定
	if (MeshComp)
	{
		// メッシュのコリジョンを無効化
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// コリジョンの初期設定
	SetupCollisionFromMesh();
}

void ATileBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

    SetupCollisionFromMesh();
}

void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// マテリアルの設定
void ATileBase::SetTileMaterial(UMaterialInterface* Material)
{
	if (MeshComp && Material)
	{
		MeshComp->SetMaterial(0, Material);
	}
}

// メッシュからコリジョンを設定
void ATileBase::SetupCollisionFromMesh()
{
    if (IsValid(MeshComp) == false)
        return;

    UStaticMesh* StaticMesh = MeshComp->GetStaticMesh();
    if (StaticMesh == nullptr)
        return;

    // メッシュのローカルBounds
    const FBoxSphereBounds Bounds = StaticMesh->GetBounds();

    // BoxExtent は「半サイズ」
    FVector BoxExtent = Bounds.BoxExtent;

    const FVector LocalCenter = Bounds.Origin;

    // Meshの相対Transformを反映
    const FVector MeshScale = MeshComp->GetRelativeScale3D();

	BoxComp->SetRelativeLocation(MeshComp->GetRelativeLocation() + LocalCenter);

	BoxComp->SetRelativeRotation(MeshComp->GetRelativeRotation());

    BoxComp->SetBoxExtent(BoxExtent * MeshScale);
}

