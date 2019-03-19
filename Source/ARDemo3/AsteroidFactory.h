#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidFactory.generated.h"


// This class defines the behavior of the asteroid factory. The entire purpose of this
// class is to dynamically spawn asteroids at runtime.
UCLASS()
class ARDEMO3_API AAsteroidFactory : public AActor
{
    // Required UE4 macro for unreal header code
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    AAsteroidFactory();
    
    // Spanws bodies based on passed int - controlled by menu slider
    UFUNCTION(BlueprintCallable, Category = "Spawn")
    void SpawnBodies(int bodies);
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Spawns asteroid at random location
    void SpawnSingleBody();
    
    UPROPERTY(EditAnywhere)
    int bodiesToSpawn;
    
    UPROPERTY(EditAnywhere, Category="SpawningRadius")
    float minRadius;
    
    UPROPERTY(EditAnywhere, Category="SpawningRadius")
    float maxRadius;
};
