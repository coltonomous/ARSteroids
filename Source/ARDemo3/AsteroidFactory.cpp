#include "AsteroidFactory.h"


// Sets default values
AAsteroidFactory::AAsteroidFactory()
{
    bodiesToSpawn = 250;
    minRadius = 2000.f;
    maxRadius = 15000.f;
}


// Called when the game starts or when spawned
void AAsteroidFactory::BeginPlay()
{
    Super::BeginPlay();
    
    for(int i = 0; i < this->bodiesToSpawn; i++){
        SpawnSingleBody();
    }
}


// Spawns a single asteroid at a random location within the spawn zone
void AAsteroidFactory::SpawnSingleBody()
{
    float degrees = FMath::RandRange(0.f, 359.f);
    float spawnZone = FMath::RandRange(this->minRadius, this->maxRadius);
    
    float sinDegrees = FMath::Sin(degrees);
    float cosDegrees = FMath::Cos(degrees);
    
    float xRange = cosDegrees * spawnZone;
    float yRange = sinDegrees * spawnZone;
    float zRange = FMath::RandRange(-20000.f, 20000.f);
    
    FVector spawnLocation = FVector(xRange, yRange, zRange);
    FRotator spawnRotation = FRotator(0.f, 0.f, 0.f);
    FActorSpawnParameters spawnInfo;
    
    GetWorld()->SpawnActor<AAsteroid>(spawnLocation, spawnRotation, spawnInfo);
}

