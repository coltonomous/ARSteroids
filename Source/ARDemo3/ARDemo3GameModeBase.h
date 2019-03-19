#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "EngineUtils.h"
#include "ARDemo3GameModeBase.generated.h"


// This class acts as a game mode manager and defines global behaviors for the game.
UCLASS()
class ARDEMO3_API AARDemo3GameModeBase : public AGameModeBase
{
    // Required UE4 macro for unreal header code
    GENERATED_BODY()
    
public:
    AARDemo3GameModeBase();
    
    // Replaces menu widget
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
    
    // Retrieves score
    UFUNCTION(BlueprintCallable, Category = "Score")
    int GetScore() const;
    
    // Retrieves number of asteroids in level
    UFUNCTION(BlueprintCallable, Category = "Asteroids")
    int GetAsteroids() const;
    
    // Increments score
    UFUNCTION(Category = "Score")
    void UpdateScore();
    
protected:
    
    // Master function for setting initial state; 
    virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
    int score;
    
    // Starting widget
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
    TSubclassOf<UUserWidget> StartingWidgetClass;
    
    // Instance of starting widget
    UPROPERTY()
    UUserWidget* CurrentWidget;
};
