#include <Hooks.h>
namespace MPL::Hooks
{
    template <class T>
    T* GetForm(std::string edid)
    {
        auto std = StatData::GetSingleton();
        auto form = std->Lookup(edid);
        if (form != nullptr && form->Is(T::FORMTYPE))
        {
            return form->As<T>();
        }
        return nullptr;
    }
    struct InitOBJ
    {
        using Target = RE::TESObjectREFR;
        static inline void thunk(Target* a_ref)
        {
            func(a_ref);
            if (a_ref->extraList.HasType(RE::ExtraDataType::kRoomRefData))
            {
                auto edr = a_ref->extraList.GetByType<RE::ExtraRoomRefData>();
                if (edr->data->lightingTemplate != nullptr)
                {
                    auto itm = GetForm<RE::BGSLightingTemplate>(edr->data->lightingTemplate->GetFormEditorID());
                    if (itm != nullptr)
                    {
                        edr->data->lightingTemplate = itm;
                    }
                }
            }
        }
        static inline REL::Relocation<decltype(thunk)> func;
        static inline constexpr std::size_t index{ 0x13 };
    };
    struct InitWS
    {
        using Target = RE::TESWorldSpace;
        static inline void thunk(Target* a_ref)
        {
            func(a_ref);
            if (a_ref->lightingTemplate != nullptr)
            {
                auto lt = GetForm<RE::BGSLightingTemplate>(a_ref->lightingTemplate->GetFormEditorID());
                if (lt != nullptr)
                {
                    a_ref->lightingTemplate = lt;
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
                auto lt = GetForm<RE::BGSLightingTemplate>(a_ref->lightingTemplate->GetFormEditorID());
                if (lt != nullptr)
                {
                    a_ref->lightingTemplate = lt;
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
    RE::TESForm* StatData::Lookup(std::string s)
    {
        if (!this->cache.contains(s))
        {
            const auto& [map, lock] = RE::TESForm::GetAllForms();
            [[maybe_unused]] const RE::BSReadLockGuard l{ lock };
            if (map)
            {
                const auto it = std::find_if(std::execution::par, map->begin(), map->end(), [&](auto itm) {
                    return itm.second->sourceFiles.array->front()->GetFilename() == this->file && itm.second->GetFormEditorID() == s;
                });
                if (it != map->end())
                {
                    cache.insert({ s, it->first });
                    return it->second;
                }
                else {
                    return nullptr;
                }
            }
            else {
                return nullptr;
            }
        }
        else {
            return RE::TESForm::LookupByID(cache.at(s));
        }
    }
}  // namespace MPL::Hooks