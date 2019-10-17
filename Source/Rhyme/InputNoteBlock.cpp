#include "InputNoteBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/GameEngine.h"

#define TO_FLAG(Enum) (1 << static_cast<uint32>(Enum))

// Sets default values
AInputNoteBlock::AInputNoteBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInputNoteBlock::BeginPlay()
{
	if (this->collider == NULL) {
		this->collider = AActor::FindComponentByClass<UBoxComponent>();
	}
	
	FString colliderName = UKismetSystemLibrary::GetDisplayName(this->collider);
	
	this->collider->OnComponentBeginOverlap.AddDynamic(this, &AInputNoteBlock::TriggerEnter);
	this->collider->OnComponentEndOverlap.AddDynamic(this, &AInputNoteBlock::TriggerExit);

	this->notes = (uint8)FMath::RandRange(0, 15);

	Super::BeginPlay();
}

// Called every frame
void AInputNoteBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ENotes AInputNoteBlock::GetNotes()
{
	return (ENotes)notes;
}

void AInputNoteBlock::Move(float distance)
{
	FVector location = this->GetActorLocation();
	location.X -= distance;
	this->SetActorLocation(location);
}

bool AInputNoteBlock::IsReadyForNotePress()
{
	return this->readyForNotePress;
}

bool AInputNoteBlock::HasNote(ENotes note)
{
	return (((ENotes)this->notes & note) != (ENotes)0);
}

void AInputNoteBlock::TriggerEnter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (this == OtherActor) {
		return;
	}
	FString otherName = UKismetSystemLibrary::GetDisplayName(OtherActor);
	this->readyForNotePress = true;
}

void AInputNoteBlock::TriggerExit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	this->readyForNotePress = false;
}