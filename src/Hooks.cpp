#include <Hooks.h>
namespace MPL::Hooks
{
    struct InitOBJ
    {
        using Target = RE::TESObjectREFR;
        static inline RE::NiAVObject* thunk(Target* a_ref, bool a_background)
        {
            auto* edr = a_ref->extraList.GetByType<RE::ExtraRoomRefData>();
            if (edr != nullptr && edr->data->lightingTemplate != nullptr)
            {
                auto* std = MPL::Config::StatData::GetSingleton();
                auto* itm = std->Lookup(edr->data->lightingTemplate->GetFormEditorID());
                if (itm != nullptr)
                {
#ifdef DEBUG
                    logger::info("(INIT) MARKER: {:X}:{} -> {:X}:{} W/ {:X}:{}", a_ref->GetLocalFormID(), a_ref->sourceFiles.array->front()->GetFilename(), edr->data->lightingTemplate->GetLocalFormID(), edr->data->lightingTemplate->sourceFiles.array->front()->GetFilename(), itm->GetLocalFormID(), itm->sourceFiles.array->front()->GetFilename());
#endif
                    edr->data->lightingTemplate = itm;
#ifdef DEBUG
                    logger::info("(INIT) MARKER: {:X}:{} -> {:X}:{}", a_ref->GetLocalFormID(), a_ref->sourceFiles.array->front()->GetFilename(), edr->data->lightingTemplate->GetLocalFormID(), edr->data->lightingTemplate->sourceFiles.array->front()->GetFilename());
#endif
                }
            }
            return func(a_ref, a_background);
        }
        static inline REL::Relocation<decltype(thunk)> func;
        static inline constexpr std::size_t index{ 0x6A };
    };
    struct InitWS
    {
        using Target = RE::TESWorldSpace;
        static inline void thunk(Target* a_ref)
        {
            func(a_ref);
            if (a_ref->lightingTemplate != nullptr)
            {
                auto std = MPL::Config::StatData::GetSingleton();
                auto itm = std->Lookup(a_ref->lightingTemplate->GetFormEditorID());
                if (itm != nullptr)
                {
#ifdef DEBUG
                    logger::info("WORLDSPACE: {:X}:{} REPLACING {:X}:{} W/ {:X}:{}", a_ref->GetLocalFormID(), a_ref->sourceFiles.array->front()->GetFilename(), a_ref->lightingTemplate->GetLocalFormID(), a_ref->lightingTemplate->sourceFiles.array->front()->GetFilename(), itm->GetLocalFormID(), itm->sourceFiles.array->front()->GetFilename());
#endif
                    a_ref->lightingTemplate = itm;
                }
            }
        }
        static inline REL::Relocation<decltype(thunk)> func;
        static inline constexpr std::size_t index{ 0x13 };
    };
    struct InitCell
    {
        using Target = RE::TESObjectCELL;
        static inline void thunk(Target* a_ref)
        {
            func(a_ref);
            if (a_ref->lightingTemplate != nullptr)
            {
                auto std = MPL::Config::StatData::GetSingleton();
                auto itm = std->Lookup(a_ref->lightingTemplate->GetFormEditorID());
                if (itm != nullptr)
                {
#ifdef DEBUG
                    logger::info("CELL: {:X}:{} REPLACING {:X}:{} W/ {:X}:{}", a_ref->GetLocalFormID(), a_ref->sourceFiles.array->front()->GetFilename(), a_ref->lightingTemplate->GetLocalFormID(), a_ref->lightingTemplate->sourceFiles.array->front()->GetFilename(), itm->GetLocalFormID(), itm->sourceFiles.array->front()->GetFilename());
#endif
                    a_ref->lightingTemplate = itm;
                }
            }
        }
        static inline REL::Relocation<decltype(thunk)> func;
        static inline constexpr std::size_t index{ 0x13 };
    };
    void Install()
    {
        stl::install_hook<InitOBJ>();
        stl::install_hook<InitWS>();
        stl::install_hook<InitCell>();
    }
}  // namespace MPL::Hooks