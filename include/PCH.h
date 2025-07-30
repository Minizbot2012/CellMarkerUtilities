#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#define _UNICODE
// clang-format off
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include <REX/REX.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fmt/bin_to_hex.h>
#include <windows.h>
#include <ClibUtil/editorID.hpp>
#include <unordered_set>
// clang-format on
using namespace clib_util;
#ifdef SKYRIM_AE
#    define OFFSET(se, ae) ae
#    define OFFSET_3(se, ae, vr) ae
#elif SKYRIMVR
#    define OFFSET(se, ae) se
#    define OFFSET_3(se, ae, vr) vr
#else
#    define OFFSET(se, ae) se
#    define OFFSET_3(se, ae, vr) se
#endif
#define DLLEXPORT __declspec(dllexport)
namespace logger = SKSE::log;
using namespace std::literals;

template <class T>
T* GetFormForString(std::string forms)
{
    if (forms.contains(":"))
    {
        auto loc = forms.find(":");
        auto formId = strtoul(forms.substr(0, loc), nullptr, 16);
        auto modName = forms.substr(loc + 1);
        auto dh = RE::TESDataHandler::GetSingleton();
        return dh->LookupForm<T>(formId, modName);
    }
    else {
        return RE::TESForm::LookupByEditorID<T>(s);
    }
}

#include "Hooking.h"