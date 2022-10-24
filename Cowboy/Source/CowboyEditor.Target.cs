using UnrealBuildTool;

public class CowboyEditorTarget : TargetRules
{
    public CowboyEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange( new string[] { "CowboyCore" });
    }
}
