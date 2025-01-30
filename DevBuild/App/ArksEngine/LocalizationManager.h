#pragma once
#include <unordered_map>
#include <string>

// The supported languages for this game
enum SupportedLanguages
{
	English,
	French,
	Italian,
	German,
	Spanish
};

// Token that can be used for a word that is supported by my translation manager
enum Token
{
	No_Token_Req,
	MAIN,
	PLAY,
	OPTIONS,
	QUIT,
	DIFFICULTY,
	VOLUME,
	BACK,
	HINTS,
	PERMADEATH,
	RESPAWN,
	EASY,
	NORMAL,
	HARD,
	MUTE,
	MONO,
	STEREO,
	SFX,
	MUSIC,
	VOICE,
	INPUT_,
	PAUSE,
	CONTINUE,
	SONGS

};

namespace ArksEngine
{
	class Core;

	class LocalizationManager
	{
		ArksEngine::Core* m_pOwner = nullptr;
		const char* m_pLanguageFile = nullptr;

		// Current language we are displaying
		SupportedLanguages m_currentLanguage = English;

		// Hash maps for supported languages
		std::unordered_map<std::string, std::string> m_englishMap;
		std::unordered_map<std::string, std::string> m_frenchMap;
		std::unordered_map<std::string, std::string> m_italianMap;
		std::unordered_map<std::string, std::string> m_germanMap;
		std::unordered_map<std::string, std::string> m_spanishMap;

	public:
		LocalizationManager(ArksEngine::Core* pOwner, const char* file_name);
		~LocalizationManager() = default;

		void SetCurrentLanguage(SupportedLanguages language);
		SupportedLanguages GetCurrentLanguage() const { return m_currentLanguage; }
		std::string GetTranslation(Token token);

		Token StringToToken(const std::string& token) const;

	private:
		void Init();

		static std::string TokenToString(Token token);
	};
}


