#include <Config.h>
#include <Hooks.h>

void OnInit(SKSE::MessagingInterface::Message* a_msg)
{
    switch (a_msg->type)
    {
    case SKSE::MessagingInterface::kPostPostLoad:
        MPL::Config::LoadConfigs();
        break;
    default:
        break;
    }
}

extern "C" DLLEXPORT auto SKSEPlugin_Version = []() {
    SKSE::PluginVersionData v;
    v.PluginVersion({ 1, 0, 0, 0 });
    v.PluginName("MarkerPatcher");
    v.AuthorName("mini");
    v.UsesAddressLibrary();
    v.UsesNoStructs();
    return v;
}();

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
    SKSE::Init(a_skse);
    logger::info("Game version : {}", a_skse->RuntimeVersion().string());
    MPL::Hooks::Install();
    SKSE::GetMessagingInterface()->RegisterListener(OnInit);
    return true;
}