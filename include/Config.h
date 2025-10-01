#pragma once
namespace MPL::Config
{
    struct Config
    {
        std::string sSearchFile;
    };
    class StatData : public REX::Singleton<StatData>
    {
    public:
        inline void LoadConfig()
        {
            auto cfg = rfl::toml::load<Config>("Data/SKSE/Plugins/LightingUtil.toml");
            if (cfg)
            {
                this->conf = *cfg;
            }
            else
            {
                logger::error("Error {}, using defaults", cfg.error().what());
                this->conf.sSearchFile = "ATLM.esp";
                rfl::toml::save("Data/SKSE/Plugins/LightingUtil.toml", this->conf);
            }
        };
        RE::BGSLightingTemplate* Lookup(std::string s);
        std::unordered_map<std::string, RE::FormID> cache;
        std::unordered_set<std::string> misses;
        Config conf;
    };
}  // namespace MPL::Config