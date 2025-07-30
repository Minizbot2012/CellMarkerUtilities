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
        std::vector<RoomMarkerData> pairs;
        for (auto ent : std::filesystem::directory_iterator(ConfigFolder))
        {
            if (ent.path().filename().extension() == ".json")
            {
                logger::info("Loading config file {}", ent.path().filename().string());
                pairs.clear();
                auto gl = glz::read_file_json(pairs, ent.path().string(), std::string{});
                for (auto itm : pairs)
                {
                    auto loc = itm.form.find(":");
                    auto MarkerForm = itm.form.substr(0, loc);
                    auto MarkerMod = itm.form.substr(loc + 1);
                    auto loc_it = itm.lightingTemplate.find(":");
                    auto LightingTemplateForm = itm.lightingTemplate.substr(0, loc_it);
                    auto LightingTemplateMod = itm.lightingTemplate.substr(loc_it + 1);
                    auto data = RoomMarker{ LightingTemplateMod, strtoul(LightingTemplateForm.c_str(), nullptr, 16) };
                    auto data_key = std::format("{:x}:{}", strtoul(MarkerForm.c_str(), nullptr, 16), MarkerMod);
                    dc->Markers.insert({data_key, data });
                }
            }
        }
        logger::info("Loaded {} Entries", dc->Markers.size());
    }
}  // namespace MPL::Config