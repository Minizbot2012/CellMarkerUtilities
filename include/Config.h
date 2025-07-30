#pragma once
#include "glaze/glaze.hpp"
#include <filesystem>
namespace MPL::Config
{
    struct RoomMarker
    {
        std::string lightMod;
        uint32_t formId;
    };
    class DataContainer : public REX::Singleton<DataContainer>
    {
    public:
        std::unordered_map<std::string, RoomMarker> Markers;
    };
    struct RoomMarkerData
    {
        std::string form;
        std::string lightingTemplate;
    };
    static std::string ConfigFolder = "./Data/SKSE/MarkerData/";
    void LoadConfigs();
}  // namespace MPL::Config
