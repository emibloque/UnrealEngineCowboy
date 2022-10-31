using UnrealBuildTool;

public class CowboyTarget : TargetRules
{
    public CowboyTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange( new string[] { "CowboyCore" });
    }
}
