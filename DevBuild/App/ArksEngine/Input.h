#pragma once
#include "unordered_map"

struct MouseClickLocation
{
	int m_x = 0;
	int m_y = 0;

	void Rest()
	{
		m_x = 0;
		m_y = 0;
	}
};

struct MouseHoverLocation
{
	int m_x = 0;
	int m_y = 0;
};

namespace ArksEngine
{
	class Core;

	class Input
	{
		ArksEngine::Core* m_pOwner; //  This is a Ptr to the Core
		std::unordered_map<int, bool> mInputMap; // This is A HashMap for the keys
		bool mQuit; // A boolean for Quitting

		MouseClickLocation mouseClickLocation = { 0, 0 };
		MouseHoverLocation mouseHoverLocation = { 0, 0 };
	public:
		
		enum KeyCode
		{
			// Letters (A-Z)
			KeyCode_A,
			KeyCode_B,
			KeyCode_C,
			KeyCode_D,
			KeyCode_E,
			KeyCode_F,
			KeyCode_G,
			KeyCode_H,
			KeyCode_I,
			KeyCode_J,
			KeyCode_K,
			KeyCode_L,
			KeyCode_M,
			KeyCode_N,
			KeyCode_O,
			KeyCode_P,
			KeyCode_Q,
			KeyCode_R,
			KeyCode_S,
			KeyCode_T,
			KeyCode_U,
			KeyCode_V,
			KeyCode_W,
			KeyCode_X,
			KeyCode_Y,
			KeyCode_Z,

			// Numbers (0-9)
			KeyCode_Zero,
			KeyCode_One,
			KeyCode_Two,
			KeyCode_Three,
			KeyCode_Four,
			KeyCode_Five,
			KeyCode_Six,
			KeyCode_Seven,
			KeyCode_Eight,
			KeyCode_Nine,

			// Symbols and punctuation
			KeyCode_Space,
			KeyCode_Slash,        // /
			KeyCode_Backslash,    // 
			KeyCode_Period,       // .
			KeyCode_Comma,        // ,
			KeyCode_Semicolon,    // ;
			KeyCode_Colon,        // :
			KeyCode_Apostrophe,   // '
			KeyCode_Quote,        // "
			KeyCode_Minus,        // -
			KeyCode_Equals,       // =
			KeyCode_Plus,         // +
			KeyCode_Exclamation,  // !
			KeyCode_At,           // @
			KeyCode_Hash,         // #
			KeyCode_Dollar,       // $
			KeyCode_Percent,      // %
			KeyCode_Caret,        // ^
			KeyCode_Ampersand,    // &
			KeyCode_Asterisk,     // *
			KeyCode_LeftParen,    // (
			KeyCode_RightParen,   // )
			KeyCode_QuestionMark, // ?
			KeyCode_LessThan,     // <
			KeyCode_GreaterThan,  // >
			KeyCode_Tilde,        // ~
			KeyCode_Backtick,     // `
			KeyCode_LeftBracket,  // [
			KeyCode_RightBracket, // ]
			KeyCode_LeftCurly,    // {
			KeyCode_RightCurly,   // }
			KeyCode_Pipe,         // |
			KeyCode_Underscore,   // _

			// Function keys (F1-F12)
			KeyCode_F1,
			KeyCode_F2,
			KeyCode_F3,
			KeyCode_F4,
			KeyCode_F5,
			KeyCode_F6,
			KeyCode_F7,
			KeyCode_F8,
			KeyCode_F9,
			KeyCode_F10,
			KeyCode_F11,
			KeyCode_F12,

			// Modifier keys
			KeyCode_Shift,
			KeyCode_Ctrl,
			KeyCode_Alt,
			KeyCode_CapsLock,

			// Navigation keys
			KeyCode_UpArrow,
			KeyCode_DownArrow,
			KeyCode_LeftArrow,
			KeyCode_RightArrow,
			KeyCode_Home,
			KeyCode_End,
			KeyCode_PageUp,
			KeyCode_PageDown,

			// Other control keys
			KeyCode_Enter,
			KeyCode_Backspace,
			KeyCode_Tab,
			KeyCode_Esc,
			KeyCode_Delete,
			KeyCode_Insert,

			// Mouse buttons
			Left_Click,
			Right_Click,
			Middle_Click,

			// Last
			Last
		};


	private:
		void ResetInput(); // We need to clear previous input
		void AddKey(int key, bool pressed); // Lets us add more inputs

	public:
		Input(ArksEngine::Core* pOwner); // This is a constructor for our Input
		~Input() = default; // A default De-constructor
		void ProcessInput(); // Preprocess our input
		bool GetKeyPressed(KeyCode keyCode); // Checks to see if A key is pressed
		bool GetTwoKeysPressed(KeyCode keyCode, KeyCode keycode2); // Checks to see if 2 keys are Pressed
		bool IsKeyHeld(KeyCode keyCode);
		MouseClickLocation GetMouseClickLocation() const { return mouseClickLocation; }
		MouseHoverLocation GetMouseHoverLocation() const { return mouseHoverLocation; }
		
	};
}


