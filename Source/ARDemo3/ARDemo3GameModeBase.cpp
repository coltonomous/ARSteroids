#include "ARDemo3GameModeBase.h"
#include "MyPawn.h"
#include "MyPlayerController.h"

AARDemo3GameModeBase::AARDemo3GameModeBase()
{
    DefaultPawnClass = AMyPawn::StaticClass();
    PlayerControllerClass = AMyPlayerController::StaticClass();
    
    //static ConstructorHelpers::FObjectFinder<UUserWidget> HUDTemplate(TEXT("/Game/Resources/Menus/HUD.HUD_C"));
    //if(HUDTemplate.Succeeded()){
        //ChangeMenuWidget(HUDTemplate);
    //}
}


// Called when the game starts
void AARDemo3GameModeBase::BeginPlay()
{
    Super::BeginPlay();
    this->score = 0;
    ChangeMenuWidget(StartingWidgetClass);
}


// Retrieves the current score
int AARDemo3GameModeBase::GetScore() const
{
    return this->score;
}


// Retrieves current asteroids in level - for slider in settings menu
int AARDemo3GameModeBase::GetAsteroids() const
{
    int count = 0;
    for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        if(ActorItr->GetClass()->GetName().Compare(FString(TEXT("Asteroid"))) == 0){
            count ++;
        }
    }
    return count;
}


// Increments the global score counter
void AARDemo3GameModeBase::UpdateScore()
{
    this->score += 1;
}


// Replaces existing menu widget with new one
void AARDemo3GameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if(CurrentWidget != nullptr){
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    
    if(NewWidgetClass != nullptr){
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        
        if(CurrentWidget != nullptr){
            CurrentWidget->AddToViewport();
        }
    }
}
