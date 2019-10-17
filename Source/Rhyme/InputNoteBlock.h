#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Notes.h"
#include "Components/BoxComponent.h"
#include "InputNoteBlock.generated.h"

UCLASS()
class RHYME_API AInputNoteBlock : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (Bitmask, BitmaskEnum = "ENotes"))
	uint8 notes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* collider;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool readyForNotePress = false;

	virtual void BeginPlay() override;

public:	

	AInputNoteBlock();
	virtual void Tick(float DeltaTime) override;
	virtual ENotes GetNotes();
	virtual void Move(float distance);

	UFUNCTION(BlueprintCallable)
	bool IsReadyForNotePress();

	UFUNCTION(BlueprintCallable)
	bool HasNote(ENotes note);

	UFUNCTION()
	void TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
