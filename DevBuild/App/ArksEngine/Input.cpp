#include "Input.h"
#include <SDL.h>

#include "Core.h"
#include "Utillities/Debug_Log.h"

ArksEngine::Input::Input(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
	,mQuit(false)
{
	/// <summary>
	/// Loops through our enum and Adds the key
	/// </summary>
	/// <param name="pOwner"></param>
	for (int key = 0; key != Last; ++key)
	{
		AddKey(key, false);
	}

	m_pOwner->GetDebug_Log()->Log("Input Created");
}

/**
 * \brief Resets Input values back to false
 */
void ArksEngine::Input::ResetInput()
{
	for (int key = 0; key < mInputMap.size(); key++)
	{
		mInputMap[key] = false;
	}
}

/**
 * \brief Adds input to our Input un_orderer map
 * \param key KeyCode
 * \param pressed Boolean to check if key was pressed
 */
void ArksEngine::Input::AddKey(int key, bool pressed)
{
	mInputMap.emplace(key, pressed);
}

/**
 * \brief Processes the given input using SDL_PollEvent
 */
void ArksEngine::Input::ProcessInput()
{
	const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);
    SDL_Keymod keyMod = SDL_GetModState();  // Get the modifier keys state (Shift, Ctrl, etc.)

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT:

			// IF THE WINDOW EVENT WAS CLOSE WINDOW	
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
                m_pOwner->SetQuit(true);
			}
			break;

        case SDL_KEYDOWN:
            // Handle Caps Lock toggle
            if (event.key.keysym.scancode == SDL_SCANCODE_CAPSLOCK)
            {
                mInputMap[KeyCode_CapsLock] = !mInputMap[KeyCode_CapsLock]; // Toggle Caps Lock
            }

            // Handle letters A-Z
            for (int scancode = SDL_SCANCODE_A; scancode <= SDL_SCANCODE_Z; ++scancode)
            {
                mInputMap[scancode - SDL_SCANCODE_A + KeyCode_A] = keyboard_state[scancode];
            }

            // Handle numbers 1-9
            for (int scancode = SDL_SCANCODE_1; scancode <= SDL_SCANCODE_9; ++scancode)
            {
                mInputMap[scancode - SDL_SCANCODE_1 + KeyCode_One] = keyboard_state[scancode];
            }

            // Handle the 0 key separately (SDL_SCANCODE_0 comes after SDL_SCANCODE_9)
            mInputMap[KeyCode_Zero] = keyboard_state[SDL_SCANCODE_0];

            // Handle symbol keys (!@#$%^&*(), etc.)
            if (keyboard_state[SDL_SCANCODE_SLASH])
                mInputMap[KeyCode_Slash] = true;
            if (keyboard_state[SDL_SCANCODE_PERIOD])
                mInputMap[KeyCode_Period] = true;
            if (keyboard_state[SDL_SCANCODE_COMMA])
                mInputMap[KeyCode_Comma] = true;
            if (keyboard_state[SDL_SCANCODE_MINUS])
                mInputMap[KeyCode_Minus] = true;
            if (keyboard_state[SDL_SCANCODE_EQUALS])
                mInputMap[KeyCode_Equals] = true;

            // Shift-modified keys (e.g., @, #, $, %, etc.)
            if (keyMod & KMOD_SHIFT)
            {
                if (keyboard_state[SDL_SCANCODE_2]) // Shift + 2 = @
                    mInputMap[KeyCode_At] = true;
                if (keyboard_state[SDL_SCANCODE_3]) // Shift + 3 = #
                    mInputMap[KeyCode_Hash] = true;
                if (keyboard_state[SDL_SCANCODE_4]) // Shift + 4 = $
                    mInputMap[KeyCode_Dollar] = true;
                if (keyboard_state[SDL_SCANCODE_5]) // Shift + 5 = %
                    mInputMap[KeyCode_Percent] = true;
                if (keyboard_state[SDL_SCANCODE_6]) // Shift + 6 = ^
                    mInputMap[KeyCode_Caret] = true;
                if (keyboard_state[SDL_SCANCODE_7]) // Shift + 7 = &
                    mInputMap[KeyCode_Ampersand] = true;
                if (keyboard_state[SDL_SCANCODE_8]) // Shift + 8 = *
                    mInputMap[KeyCode_Asterisk] = true;
                if (keyboard_state[SDL_SCANCODE_SLASH]) // Shift + / = ?
                    mInputMap[KeyCode_QuestionMark] = true;
            }

            // Handle space, backspace, enter, and escape
            if (keyboard_state[SDL_SCANCODE_SPACE])
                mInputMap[KeyCode_Space] = true;
            if (keyboard_state[SDL_SCANCODE_BACKSPACE])
                mInputMap[KeyCode_Backspace] = true;
            if (keyboard_state[SDL_SCANCODE_RETURN])
                mInputMap[KeyCode_Enter] = true;
            if (keyboard_state[SDL_SCANCODE_ESCAPE])
                mInputMap[KeyCode_Esc] = true;

            // Handle function keys F1-F12
            for (int scancode = SDL_SCANCODE_F1; scancode <= SDL_SCANCODE_F12; ++scancode)
            {
                mInputMap[scancode - SDL_SCANCODE_F1 + KeyCode_F1] = keyboard_state[scancode];
            }

            // Handle arrow keys
            if (keyboard_state[SDL_SCANCODE_UP])
                mInputMap[KeyCode_UpArrow] = true;
            if (keyboard_state[SDL_SCANCODE_DOWN])
                mInputMap[KeyCode_DownArrow] = true;
            if (keyboard_state[SDL_SCANCODE_LEFT])
                mInputMap[KeyCode_LeftArrow] = true;
            if (keyboard_state[SDL_SCANCODE_RIGHT])
                mInputMap[KeyCode_RightArrow] = true;

            // Handle navigation keys (home, end, page up, page down)
            if (keyboard_state[SDL_SCANCODE_HOME])
                mInputMap[KeyCode_Home] = true;
            if (keyboard_state[SDL_SCANCODE_END])
                mInputMap[KeyCode_End] = true;
            if (keyboard_state[SDL_SCANCODE_PAGEUP])
                mInputMap[KeyCode_PageUp] = true;
            if (keyboard_state[SDL_SCANCODE_PAGEDOWN])
                mInputMap[KeyCode_PageDown] = true;

            // Handle modifier keys (Shift, Ctrl, Alt)
            if (keyboard_state[SDL_SCANCODE_LSHIFT] || keyboard_state[SDL_SCANCODE_RSHIFT])
                mInputMap[KeyCode_Shift] = true;
            if (keyboard_state[SDL_SCANCODE_LCTRL] || keyboard_state[SDL_SCANCODE_RCTRL])
                mInputMap[KeyCode_Ctrl] = true;
            if (keyboard_state[SDL_SCANCODE_LALT] || keyboard_state[SDL_SCANCODE_RALT])
                mInputMap[KeyCode_Alt] = true;
            break;

        case SDL_KEYUP:
            // Handle key releases in a similar way
            if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
            {
                mInputMap[event.key.keysym.sym - SDLK_a + KeyCode_A] = false;
            }

            // Handle number key releases (1-9)
            if (event.key.keysym.sym >= SDLK_1 && event.key.keysym.sym <= SDLK_9)
            {
                mInputMap[event.key.keysym.sym - SDLK_1 + KeyCode_One] = false;
            }

            // Handle symbol key releases
            if (event.key.keysym.sym == SDLK_SLASH)
                mInputMap[KeyCode_Slash] = false;
            if (event.key.keysym.sym == SDLK_PERIOD)
                mInputMap[KeyCode_Period] = false;
            if (event.key.keysym.sym == SDLK_COMMA)
                mInputMap[KeyCode_Comma] = false;
            if (event.key.keysym.sym == SDLK_MINUS)
                mInputMap[KeyCode_Minus] = false;
            if (event.key.keysym.sym == SDLK_EQUALS)
                mInputMap[KeyCode_Equals] = false;

            // Handle shift-modified symbol key releases
            if (keyMod & KMOD_SHIFT)
            {
                if (event.key.keysym.sym == SDLK_2) // Shift + 2 = @
                    mInputMap[KeyCode_At] = false;
                if (event.key.keysym.sym == SDLK_3) // Shift + 3 = #
                    mInputMap[KeyCode_Hash] = false;
                if (event.key.keysym.sym == SDLK_4) // Shift + 4 = $
                    mInputMap[KeyCode_Dollar] = false;
                if (event.key.keysym.sym == SDLK_5) // Shift + 5 = %
                    mInputMap[KeyCode_Percent] = false;
                if (event.key.keysym.sym == SDLK_6) // Shift + 6 = ^
                    mInputMap[KeyCode_Caret] = false;
                if (event.key.keysym.sym == SDLK_7) // Shift + 7 = &
                    mInputMap[KeyCode_Ampersand] = false;
                if (event.key.keysym.sym == SDLK_8) // Shift + 8 = *
                    mInputMap[KeyCode_Asterisk] = false;
            }

            // Handle space, backspace, enter, and escape key releases
            if (event.key.keysym.sym == SDLK_SPACE)
                mInputMap[KeyCode_Space] = false;
            if (event.key.keysym.sym == SDLK_BACKSPACE)
                mInputMap[KeyCode_Backspace] = false;
            if (event.key.keysym.sym == SDLK_RETURN)
                mInputMap[KeyCode_Enter] = false;
            if (event.key.keysym.sym == SDLK_ESCAPE)
                mInputMap[KeyCode_Esc] = false;

            // Handle function key releases (F1-F12)
            if (event.key.keysym.sym >= SDLK_F1 && event.key.keysym.sym <= SDLK_F12)
            {
                mInputMap[event.key.keysym.sym - SDLK_F1 + KeyCode_F1] = false;
            }

            // Handle the zero key release (SDLK_0)
            if (event.key.keysym.sym == SDLK_0)
            {
                mInputMap[KeyCode_Zero] = false;
            }

            // Handle arrow key releases
            if (event.key.keysym.sym == SDLK_UP)
                mInputMap[KeyCode_UpArrow] = false;
            if (event.key.keysym.sym == SDLK_DOWN)
                mInputMap[KeyCode_DownArrow] = false;
            if (event.key.keysym.sym == SDLK_LEFT)
                mInputMap[KeyCode_LeftArrow] = false;
            if (event.key.keysym.sym == SDLK_RIGHT)
                mInputMap[KeyCode_RightArrow] = false;

            // Handle navigation key releases
            if (event.key.keysym.sym == SDLK_HOME)
                mInputMap[KeyCode_Home] = false;
            if (event.key.keysym.sym == SDLK_END)
                mInputMap[KeyCode_End] = false;
            if (event.key.keysym.sym == SDLK_PAGEUP)
                mInputMap[KeyCode_PageUp] = false;
            if (event.key.keysym.sym == SDLK_PAGEDOWN)
                mInputMap[KeyCode_PageDown] = false;

            // Handle modifier key releases
            if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
                mInputMap[KeyCode_Shift] = false;
            if (event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL)
                mInputMap[KeyCode_Ctrl] = false;
            if (event.key.keysym.sym == SDLK_LALT || event.key.keysym.sym == SDLK_RALT)
                mInputMap[KeyCode_Alt] = false;
            break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// Handle left click
				mInputMap[Left_Click] = true;
				mouseClickLocation = { event.button.x,event.button.y };
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				// Handle right click
				mInputMap[Right_Click] = true;
				mouseClickLocation = { event.button.x,event.button.y };
			}
			break;
		
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// Handle left button release
				mInputMap[Left_Click] = false;
				mouseClickLocation.Rest();
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				// Handle right button release
				mInputMap[Right_Click] = false;
				mouseClickLocation.Rest();
			}
			break;

		case SDL_MOUSEMOTION:
			// Update mouse position on mouse movement
			mouseHoverLocation.m_x = event.motion.x;
			mouseHoverLocation.m_y = event.motion.y;
			break;
		}

	}
}

bool ArksEngine::Input::GetKeyPressed(KeyCode keyCode)
{
	if (mInputMap[keyCode] == true)
		return true;

	return false;
}

bool ArksEngine::Input::GetTwoKeysPressed(KeyCode keyCode, KeyCode keycode2)
{
	if (mInputMap[keyCode] == true && mInputMap[keycode2 == true])
		return true;
	return false;
}

bool ArksEngine::Input::IsKeyHeld(KeyCode keyCode)
{
    // Check if the key is currently pressed
    return mInputMap[keyCode];
}
