#pragma once
#include <any>
#include <string>
#include <vector>


namespace ArksEngine
{
    class Event {
    public:
        Event(std::string name, std::vector<std::any> args = {}) : mName(std::move(name)), mArgs(std::move(args)) {}
        [[nodiscard]] const std::string& GetName() const { return mName; }
        [[nodiscard]] const std::vector<std::any>& GetArgs() const { return mArgs; }

    private:
        std::string mName;
        std::vector<std::any> mArgs;
    };
}
