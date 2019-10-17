// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RhymeGameMode.h"
#include "RhymePlayerController.h"
#include "RhymeCharacter.h"
#include "UObject/ConstructorHelpers.h"

const uint8 SCORE_CHANGE_DELTA = 10;

TSubclassOf<AInputNoteBlock> InputNoteBlockInstanceClass;
float lastInputNodeBlockAdded = 0;

ARhymeGameMode::ARhymeGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = ARhymePlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> CameraPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/CameraCharacter"));
	if (CameraPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = CameraPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AInputNoteBlock> InputNoteBlockInstancePawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/InputNoteBlockInstance"));
	InputNoteBlockInstanceClass = InputNoteBlockInstancePawnBPClass.Class;
}

void ARhymeGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	lastInputNodeBlockAdded -= (this->tempo / 60.0f) * DeltaTime;

	if (lastInputNodeBlockAdded <= 0.0f) {
		this->AddNewNoteBlock();
	}

	this->UpdateCurrentInputNoteBlocks(DeltaTime);
}

void ARhymeGameMode::UpdateCurrentInputNoteBlocks(float DeltaTime)
{
	for (auto inputNoteBlockPtr : this->noteBlocks) {
		if (!inputNoteBlockPtr.IsValid()) {
			continue;
		}

		AInputNoteBlock* inputNoteBlock = inputNoteBlockPtr.Get();
		inputNoteBlock->Move(DeltaTime * 60.0f * this->GetTempo());

		if (inputNoteBlock->GetActorLocation().X <= -100.0f) {
			this->noteBlocks.Remove(inputNoteBlockPtr);
			inputNoteBlock->Destroy();
		}
	}
}

void ARhymeGameMode::AddNewNoteBlock()
{
	if (InputNoteBlockInstanceClass == NULL) {
		return;
	}

	FActorSpawnParameters spawnInfo;
	FVector spawnLocation = FVector(5000.f, 0.0f, 0.0f);
	AInputNoteBlock* inputNodeBlock = GWorld->SpawnActor<AInputNoteBlock>(InputNoteBlockInstanceClass, spawnLocation, FRotator::ZeroRotator, spawnInfo);
	this->noteBlocks.Add(inputNodeBlock);
	lastInputNodeBlockAdded = 1.0f;
}

float ARhymeGameMode::GetTempo()
{
	return tempo;
}

bool ARhymeGameMode::CheckInputForValidNotes(uint8 notesCurrentlyPressed)
{
	for (auto inputNoteBlockPtr : noteBlocks) {
		if (!inputNoteBlockPtr.IsValid()) {
			continue;
		}

		AInputNoteBlock* inputNoteBlock = inputNoteBlockPtr.Get();
		if (!inputNoteBlock->IsReadyForNotePress()) {
			continue;
		}

		if ((uint8)inputNoteBlock->GetNotes() == notesCurrentlyPressed) {
			score += SCORE_CHANGE_DELTA;
			gameHUD->PlayCorrectNoteAnimation();
		}
		else {
			score += SCORE_CHANGE_DELTA;
			gameHUD->PlayWrongNoteAnimation();
		}

		gameHUD->UpdateScore(score);
		return true;
	}

	return false;
}