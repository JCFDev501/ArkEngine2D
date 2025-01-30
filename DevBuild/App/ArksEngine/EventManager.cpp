#include "EventManager.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <map>
#include <any>

#include "Event.h"

ArksEngine::EventManager::EventManager(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
{
}


void ArksEngine::EventManager::Trigger_Event(const std::string& eventName, const std::vector<std::any>& args)
{
    // Create the event
    Event event(eventName, args);

    // Add it to the event list
    mEventList.push_back(event);

    // Find the listeners for this event
    auto listeners = mListeners[eventName];

    // Trigger all listeners
    for (const auto& [priority, listener] : listeners)
    {
        listener(event);
    }

    // Remove the event from the event list
    mEventList.erase(std::remove_if(mEventList.begin(), mEventList.end(), [&event](const Event& e)
        {
            return e.GetName() == event.GetName();
        }), mEventList.end());
}

void ArksEngine::EventManager::Add_Listener(const std::string& eventName, Listener listener, int priority)
{
    mListeners[eventName].insert({ priority, listener });
}

void ArksEngine::EventManager::Remove_Listeners(const std::string& eventName)
{
    auto it = mListeners.find(eventName);
    if (it != mListeners.end()){
        it->second.clear();
    }
}
