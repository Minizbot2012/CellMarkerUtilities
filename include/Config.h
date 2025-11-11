#pragma once
namespace MPL::Config
{
    struct Config
    {
        std::string sSearchFile;
    };
    struct UMMPair {
        std::unordered_map<std::string, RE::FormID> modded;
        std::unordered_map<std::string, RE::FormID> unmodded;
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
        }
        void PostProcess();
        UMMPair Templates;
        UMMPair Imagespaces;
        Config conf;
    };
}  // namespace MPL::Config