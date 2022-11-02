using UnrealBuildTool;


public class CowboyCore : ModuleRules
{
    public CowboyCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "AIModule" });
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
