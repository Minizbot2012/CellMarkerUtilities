#pragma once
#include "glaze/glaze.hpp"
#include <filesystem>
namespace MPL::Config
{
    struct RoomMarker
    {
        std::string form;
        std::string lightingTemplate;
    };
    class DataContainer : public REX::Singleton<DataContainer>
    {
    public:
        std::vector<RoomMarker> Markers;
    };
    
    static std::string ConfigFolder = "./Data/SKSE/MarkerData/";
    void LoadConfigs();
}  // namespace MPL::Config
