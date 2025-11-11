#include <Hooks.h>
namespace MPL::Hooks
{
    struct LoadLT
    {
        using Target = RE::BGSLightingTemplate;
        static inline void thunk(Target* a_ref, RE::TESFile* a_mod)
        {
            func(a_ref, a_mod);
            auto sta = MPL::Config::StatData::GetSingleton();
            if (a_mod->GetFilename() == sta->conf.sSearchFile)
            {
                sta->Templates.modded.insert(std::make_pair(a_ref->GetFormEditorID(), a_ref->GetFormID()));
#ifdef DEBUG
                logger::info("Loaded Modded Template {} {}:{:06X}", a_ref->GetFormEditorID(), a_mod->GetFilename(), a_ref->GetLocalFormID());
#endif
            }
            else
            {
                if (!sta->Templates.unmodded.contains(a_ref->GetFormEditorID()))
                {
                    sta->Templates.unmodded.insert(std::make_pair(a_ref->GetFormEditorID(), a_ref->GetFormID()));
#ifdef DEBUG
                    logger::info("Loaded Unmodded Template {} {}:{:06X}", a_ref->GetFormEditorID(), a_mod->GetFilename(), a_ref->GetLocalFormID());
#endif
                }
            }
        }
        static inline REL::Relocation<decltype(thunk)> func;
        static inline constexpr std::size_t index{ 0x6 };
    };

    struct LoadIMG
    {
        using Target = RE::TESImageSpace;
        static inline void thunk(Target* a_ref, RE::TESFile* a_mod)
        {
            func(a_ref, a_mod);
            auto sta = MPL::Config::StatData::GetSingleton();
            if (a_mod->GetFilename() == sta->conf.sSearchFile)
            {
                sta->Imagespaces.modded.insert(std::make_pair(a_ref->GetFormEditorID(), a_ref->GetFormID()));
#ifdef DEBUG
                logger::info("Loaded Modded Imagespace {} {}:{:06X}", a_ref->GetFormEditorID(), a_mod->GetFilename(), a_ref->GetLocalFormID());
#endif
            }
            else
            {
                if (!sta->Imagespaces.unmodded.contains(a_ref->GetFormEditorID()))
                {
                    sta->Imagespaces.unmodded.insert(std::make_pair(a_ref->GetFormEditorID(), a_ref->GetFormID()));
#ifdef DEBUG
                    logger::info("Loaded Unmodded Imagespace {} {}:{:06X}", a_ref->GetFormEditorID(), a_mod->GetFilename(), a_ref->GetLocalFormID());
#endif
                }
            }
        }
        static inline REL::Relocation<decltype(thunk)> func;
        static inline constexpr std::size_t index{ 0x6 };
    };

    void Install()
    {
        stl::install_hook<LoadLT>();
        stl::install_hook<LoadIMG>();
    }
}  // namespace MPL::Hooks