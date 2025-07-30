#include <Config.h>
namespace MPL::Hooks
{
    struct InitOBJ
    {
        using Target = RE::TESObjectREFR;
        static inline void thunk(Target* a_ref)
        {
            func(a_ref);
            if (a_ref->extraList.HasType(RE::ExtraDataType::kRoomRefData))
            {
                auto data_container = MPL::Config::DataContainer::GetSingleton();
                auto comp = std::format("{:x}:{}", a_ref->GetLocalFormID(), a_ref->sourceFiles.array->front()->GetFilename());
                auto marker = std::find_if(std::execution::par, data_container->Markers.begin(), data_container->Markers.end(), [&](auto md) { return md.form == comp; });
                if (marker != data_container->Markers.end())
                {
                    logger::info("Patching ref {:x} file: {}", a_ref->GetFormID(), a_ref->sourceFiles.array->front()->GetFilename());
                    auto* lightingTmpl = GetFormForString<RE::BGSLightingTemplate>(marker->lightingTemplate);
                    if (lightingTmpl != nullptr)
                    {
                        auto edr = a_ref->extraList.GetByType<RE::ExtraRoomRefData>();
                        if (edr != nullptr && edr->data != nullptr)
                        {
                            logger::info("OLD Template FORMID: {:x}, FILE: {}", edr->data->lightingTemplate->GetFormID(), edr->data->lightingTemplate->sourceFiles.array->front()->GetFilename());
                            edr->data->lightingTemplate = lightingTmpl;
                            logger::info("NEW Template FORMID: {:x}, FILE: {}", edr->data->lightingTemplate->GetFormID(), edr->data->lightingTemplate->sourceFiles.array->front()->GetFilename());
                        }
                        else {
                            logger::info("Error in reference {:x} within file {}", a_ref->GetFormID(), a_ref->sourceFiles.array->front()->GetFilename());
                        }
                    }
                    else {
                        logger::info("{:x} is missing Room Ref Data", a_ref->GetFormID());
                    }
                }
            }
        }
        static inline REL::Relocation<decltype(thunk)> func;
        static inline constexpr std::size_t index{ 0x13 };
    };
    void Install()
    {
        stl::install_hook<InitOBJ>();
    }
}  // namespace MPL::Hooks