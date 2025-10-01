#include <Config.h>
namespace MPL::Config
{
    RE::BGSLightingTemplate* StatData::Lookup(std::string s)
    {
        if (this->misses.contains(s))
        {
            return nullptr;
        }
        else if (!this->cache.contains(s))
        {
            auto dh = RE::TESDataHandler::GetSingleton();
            auto file = dh->LookupModByName(this->conf.sSearchFile);
            auto forms = dh->GetFormArray<RE::BGSLightingTemplate>();
            const auto it = std::find_if(std::execution::par, forms.begin(), forms.end(), [&](auto itm) {
                return file->IsFormInMod(itm->GetFormID()) && itm->GetFormEditorID() == s;
            });
            if (it != forms.end())
            {
                this->cache.insert({ s, (*it)->GetFormID() });
                return *it;
            }
            else
            {
                this->misses.insert(s);
                return nullptr;
            }
        }
        else
        {
            return RE::TESForm::LookupByID<RE::BGSLightingTemplate>(this->cache.at(s));
        }
    }
}  // namespace MPL::Config