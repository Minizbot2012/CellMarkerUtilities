#pragma once
namespace MPL::Hooks
{
    class StatData : public REX::Singleton<StatData>
    {
    public:
        template<class T>
        T* Lookup(std::string s);
        std::unordered_map<std::string, RE::FormID> cache;
        std::string file;
    };

    template <class T>
    T* GetForm(std::string forms);

    void Install();
}  // namespace MPL::Hooks