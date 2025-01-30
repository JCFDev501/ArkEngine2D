#pragma once
#include <any>
#include <functional>
#include <map>
#include <string>
#include <unordered_map>

namespace ArksEngine
{
	class Event;
	class Core;

	class EventManager
	{
		using Listener = std::function<void(const Event&)>;

		ArksEngine::Core* m_pOwner;

		std::vector<ArksEngine::Event> mEventList;
		std::unordered_map<std::string, std::multimap<int, Listener>> mListeners;

	public:
		EventManager(ArksEngine::Core* pOwner);
		~EventManager() = default;

		void Trigger_Event(const std::string& eventName, const std::vector<std::any>& args);

		void Add_Listener(const std::string& eventName, Listener listener, int priority = 0);

		void Remove_Listeners(const std::string& eventName);
	};

}


