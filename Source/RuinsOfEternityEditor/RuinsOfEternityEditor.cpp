#include "RuinsOfEternityEditor.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FRuinsOfEternityEditorModule, RuinsOfEternityEditor)

void FRuinsOfEternityEditorModule::StartupModule()
{
    UE_LOG(LogTemp, Warning, TEXT("RuinsOfEternityEditor module has been loaded"));
}

void FRuinsOfEternityEditorModule::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("RuinsOfEternityEditor module has been unloaded"));
}
