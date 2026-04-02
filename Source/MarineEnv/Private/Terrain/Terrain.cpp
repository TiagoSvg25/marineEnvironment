#include "Terrain/Terrain.h"

// Implementação do construtor (Símbolo externo ATerrain::ATerrain resolvido)
ATerrain::ATerrain()
{
    // Inicializa o componente procedural
    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = ProceduralMesh;
}

// Implementação do BeginPlay (Símbolo externo ATerrain::BeginPlay resolvido)
void ATerrain::BeginPlay()
{
    Super::BeginPlay();
}