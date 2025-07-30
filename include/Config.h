#pragma once
#include "glaze/glaze.hpp"
#include <filesystem>
namespace MPL::Config
{
    struct RoomMarkerData
    {
        std::string form;
        std::string lightingTemplate;
    };
    class DataContainer : public REX::Singleton<DataContainer>
    {
    public:
        std::vector<RoomMarkerData> Markers;
    };
    
    static std::string ConfigFolder = "./Data/SKSE/MarkerData/";
    void LoadConfigs();
}  // namespace MPL::Config
