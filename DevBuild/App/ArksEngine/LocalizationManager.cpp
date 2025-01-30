#include "LocalizationManager.h"

#include <fstream>
#include <sstream>

#include "Core.h"
#include "Utillities/Debug_Log.h"

ArksEngine::LocalizationManager::LocalizationManager(ArksEngine::Core* pOwner, const char* file_name)
	:m_pOwner(pOwner)
	,m_pLanguageFile(file_name)
{
	Init();
}


void ArksEngine::LocalizationManager::SetCurrentLanguage(SupportedLanguages language)
{
	m_currentLanguage = language;
}

std::string ArksEngine::LocalizationManager::GetTranslation(Token token)
{
    // Convert the Token enum to its string representation
    std::string tokenStr = TokenToString(token);

    // Retrieve the correct translation based on the current language
    switch (m_currentLanguage)
    {
    case English:
        return m_englishMap[tokenStr];
    case French:
        return m_frenchMap[tokenStr];
    case Italian:
        return m_italianMap[tokenStr];
    case German:
        return m_germanMap[tokenStr];
    case Spanish:
        return m_spanishMap[tokenStr];
    default:
        return "Translation not found";  // Return an error message if language is unsupported
    }
}

void ArksEngine::LocalizationManager::Init()
{
    std::ifstream file(m_pLanguageFile);
    if (!file.is_open())
    {
        m_pOwner->GetDebug_Log()->Error("file not found");
        return;
    }

    std::string line;
    std::string currentLanguage;
    Token currentToken = MAIN;  // Start with the first token

    while (std::getline(file, line))
    {
        // Remove leading/trailing whitespace
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));

        // Skip empty lines or lines with only spaces
        if (line.empty())
            continue;

        // If the line contains a language header, set the current language
        if (line == "ENGLISH" || line == "FRENCH" || line == "ITALIAN" || line == "GERMAN" || line == "SPANISH")
        {
            currentLanguage = line;
            currentToken = MAIN;  // Reset token to start again for the new language
            continue;
        }

        // Insert the translation into the appropriate map based on the current language
        std::string tokenStr = TokenToString(currentToken);

        if (currentLanguage == "ENGLISH")
        {
            m_englishMap[tokenStr] = line;
        }
        else if (currentLanguage == "FRENCH")
        {
            m_frenchMap[tokenStr] = line;
        }
        else if (currentLanguage == "ITALIAN")
        {
            m_italianMap[tokenStr] = line;
        }
        else if (currentLanguage == "GERMAN")
        {
            m_germanMap[tokenStr] = line;
        }
        else if (currentLanguage == "SPANISH")
        {
            m_spanishMap[tokenStr] = line;
        }

        // Move to the next token
        currentToken = static_cast<Token>(currentToken + 1);
    }

    file.close();
}

std::string ArksEngine::LocalizationManager::TokenToString(Token token)
{
    switch (token)
    {
    case MAIN:
        return "MAIN";
    case PLAY:
        return "PLAY";
    case OPTIONS:
        return "OPTIONS";
    case QUIT:
        return "QUIT";
    case DIFFICULTY:
        return "DIFFICULTY";
    case VOLUME:
        return "VOLUME";
    case BACK:
        return "BACK";
    case HINTS:
        return "HINTS";
    case PERMADEATH:
        return "PERMADEATH";
    case RESPAWN:
        return "RESPAWN";
    case EASY:
        return "EASY";
    case NORMAL:
        return "NORMAL";
    case HARD:
        return "HARD";
    case MUTE:
        return "MUTE";
    case MONO:
        return "MONO";
    case STEREO:
        return "STEREO";
    case SFX:
        return "SFX";
    case MUSIC:
        return "MUSIC";
    case VOICE:
        return "VOICE";
    case INPUT_:
        return "INPUT";
	case PAUSE:
		return "PAUSE";
	case CONTINUE:
		return "CONTINUE";
	case SONGS:
		return "SONGS";
    default:
        return "No_Token_Req";
    }
}

Token ArksEngine::LocalizationManager::StringToToken(const std::string& token) const
{
    m_pOwner->GetDebug_Log()->Log(token);

    if (token == "MAIN")
        return MAIN;
    else if (token == "PLAY")
        return PLAY;
    else if (token == "OPTIONS")
        return OPTIONS;
    else if (token == "QUIT")
        return QUIT;
    else if (token == "DIFFICULTY")
        return DIFFICULTY;
    else if (token == "VOLUME")
        return VOLUME;
    else if (token == "BACK")
        return BACK;
    else if (token == "HINTS")
        return HINTS;
    else if (token == "PERMADEATH")
        return PERMADEATH;
    else if (token == "RESPAWN")
        return RESPAWN;
    else if (token == "EASY")
        return EASY;
    else if (token == "NORMAL")
        return NORMAL;
    else if (token == "HARD")
        return HARD;
    else if (token == "MUTE")
        return MUTE;
    else if (token == "MONO")
        return MONO;
    else if (token == "STEREO")
        return STEREO;
    else if (token == "SFX")
        return SFX;
    else if (token == "MUSIC")
        return MUSIC;
    else if (token == "VOICE")
        return VOICE;
    else if (token == "INPUT")
        return INPUT_;
	else if (token == "PAUSE")
		return PAUSE;
	else if (token == "CONTINUE")
		return CONTINUE;
	else if (token == "SONGS")
		return SONGS;
    else
        return No_Token_Req;
}

