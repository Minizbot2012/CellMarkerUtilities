#include <Config.h>
#include <Hooks.h>
#include <memory>
namespace MPL::Config
{
    void LoadConfigs()
    {
        if (!std::filesystem::exists(ConfigFolder))
        {
            logger::error("Config directory is missing");
            return;
        }
        auto dc = MPL::Config::DataContainer::GetSingleton();
        std::vector<RoomMarker> pairs;
        for (auto ent : std::filesystem::directory_iterator(ConfigFolder))
        {
            if (ent.path().filename().extension() == ".json")
            {
                logger::info("Loading config file {}", ent.path().filename().string());
                pairs.clear();
                auto gl = glz::read_file_json(pairs, ent.path().string(), std::string{});
                dc->Markers.insert(dc->Markers.begin(), pairs.begin(), pairs.end());
            }
        }
        logger::info("Loaded {} Entries", dc->Markers.size());
    }
}  // namespace MPL::Config