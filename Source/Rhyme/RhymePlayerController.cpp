// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RhymePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "RhymeCharacter.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

const uint8 MIN_NOTE_VALUE = 1;
const uint8 MAX_NOTE_VALUE = 15;

TMap<uint8, USoundCue*> soundMap;
USoundCue* note1;
USoundCue* note2;
USoundCue* note3;
USoundCue* note4;
USoundCue* note5;
USoundCue* note6;
USoundCue* note7;
USoundCue* note8;
USoundCue* note9;
USoundCue* note10;
USoundCue* note11;
USoundCue* note12;
USoundCue* note13;
USoundCue* note14;
USoundCue* note15;

ARhymePlayerController::ARhymePlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::None;

	static ConstructorHelpers::FObjectFinder<USoundCue> note1File (TEXT("/Game/TopDownCPP/Audio/Note1"));
	note1 = note1File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note2File(TEXT("/Game/TopDownCPP/Audio/Note2"));
	note2 = note2File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note3File(TEXT("/Game/TopDownCPP/Audio/Note3"));
	note3 = note3File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note4File(TEXT("/Game/TopDownCPP/Audio/Note4"));
	note4 = note4File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note5File(TEXT("/Game/TopDownCPP/Audio/Note5"));
	note5 = note5File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note6File(TEXT("/Game/TopDownCPP/Audio/Note6"));
	note6 = note6File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note7File(TEXT("/Game/TopDownCPP/Audio/Note7"));
	note7 = note7File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note8File(TEXT("/Game/TopDownCPP/Audio/Note8"));
	note8 = note8File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note9File(TEXT("/Game/TopDownCPP/Audio/Note9"));
	note9 = note9File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note10File(TEXT("/Game/TopDownCPP/Audio/Note10"));
	note10 = note10File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note11File(TEXT("/Game/TopDownCPP/Audio/Note11"));
	note11 = note11File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note12File(TEXT("/Game/TopDownCPP/Audio/Note12"));
	note12 = note12File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note13File(TEXT("/Game/TopDownCPP/Audio/Note13"));
	note13 = note13File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note14File(TEXT("/Game/TopDownCPP/Audio/Note14"));
	note14 = note14File.Object;
	static ConstructorHelpers::FObjectFinder<USoundCue> note15File(TEXT("/Game/TopDownCPP/Audio/Note15"));
	note15 = note15File.Object;

	soundMap.Add(1, note1);
	soundMap.Add(2, note2);
	soundMap.Add(3, note3);
	soundMap.Add(4, note4);
	soundMap.Add(5, note5);
	soundMap.Add(6, note6);
	soundMap.Add(7, note7);
	soundMap.Add(8, note8);
	soundMap.Add(9, note9);
	soundMap.Add(10, note10);
	soundMap.Add(11, note11);
	soundMap.Add(12, note12);
	soundMap.Add(13, note13);
	soundMap.Add(14, note14);
	soundMap.Add(15, note15);
}

uint8 ARhymePlayerController::GetNotesCurrentlyPressed()
{
	return this->notesCurrentlyPressed;
}

void ARhymePlayerController::BeginPlay()
{
	GameMode = (ARhymeGameMode*)GetWorld()->GetAuthGameMode();
}

void ARhymePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("PlayNotes", IE_Pressed, this, &ARhymePlayerController::PlayNotesPressed);

	InputComponent->BindAction("One", IE_Pressed, this, &ARhymePlayerController::OneNotePlayed);
	InputComponent->BindAction("Two", IE_Pressed, this, &ARhymePlayerController::TwoNotePlayed);
	InputComponent->BindAction("Three", IE_Pressed, this, &ARhymePlayerController::ThreeNotePlayed);
	InputComponent->BindAction("Four", IE_Pressed, this, &ARhymePlayerController::FourNotePlayed);

	InputComponent->BindAction("One", IE_Released, this, &ARhymePlayerController::OneNoteReleased);
	InputComponent->BindAction("Two", IE_Released, this, &ARhymePlayerController::TwoNoteReleased);
	InputComponent->BindAction("Three", IE_Released, this, &ARhymePlayerController::ThreeNoteReleased);
	InputComponent->BindAction("Four", IE_Released, this, &ARhymePlayerController::FourNoteReleased);
}

void ARhymePlayerController::OneNotePlayed() {
	this->OnNotePlayed(ENotes::ONE);
}

void ARhymePlayerController::TwoNotePlayed()
{
	this->OnNotePlayed(ENotes::TWO);
}

void ARhymePlayerController::ThreeNotePlayed()
{
	this->OnNotePlayed(ENotes::THREE);
}

void ARhymePlayerController::FourNotePlayed()
{
	this->OnNotePlayed(ENotes::FOUR);
}

void ARhymePlayerController::OneNoteReleased()
{
	this->OnNoteReleased(ENotes::ONE);
}

void ARhymePlayerController::TwoNoteReleased()
{
	this->OnNoteReleased(ENotes::TWO);
}

void ARhymePlayerController::ThreeNoteReleased()
{
	this->OnNoteReleased(ENotes::THREE);
}

void ARhymePlayerController::FourNoteReleased()
{
	this->OnNoteReleased(ENotes::FOUR);
}

void ARhymePlayerController::OnNotePlayed(ENotes note)
{
	this->notesCurrentlyPressed += (uint8)note;
}

void ARhymePlayerController::OnNoteReleased(ENotes note)
{
	this->notesCurrentlyPressed -= (uint8)note;
}

void ARhymePlayerController::PlayNotesPressed()
{
	bool playedRightNote = GameMode->CheckInputForValidNotes(this->GetNotesCurrentlyPressed());

	if (playedRightNote) {
		PlayNoteSound((ENotes)this->GetNotesCurrentlyPressed());
	}
	else {
		PlayWrongNoteSound();
	}
}

void ARhymePlayerController::PlayNoteSound(ENotes note)
{
	uint8 noteValue = (uint8)note;
	
	if (noteValue < MIN_NOTE_VALUE || noteValue > MAX_NOTE_VALUE) {
		return;
	}

	UGameplayStatics::SpawnSound2D(this, soundMap[noteValue], 1.0f);
}

void ARhymePlayerController::PlayWrongNoteSound()
{

}
