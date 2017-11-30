#pragma once

#include "abstract_core_system.h"

#include "SDL.h"

namespace core {

	enum class Keystate : Uint8
	{
		Up = 0,
		Down,
	};

	enum class Key : Uint16
	{
		KeyModLeftAlt = 0, KeyModRightAlt, KeyModLeftCtrl, KeyModRightCtrl, KeyModLeftShift,
		KeyModRightShift, KeyTab, KeyModCapsLock, KeyHome, KeyEnd, KeyPgUp, KeyPgDown,
		KeySpace, KeyEnter, Key0, Key1, Key2, Key3, Key4, Key5, Key6, Key7, Key8, Key9,
		KeyA, KeyB, KeyC, KeyD, KeyE, KeyF, KeyG, KeyH, KeyI, KeyJ, KeyK, KeyL, KeyM, KeyN, KeyO,
		KeyP, KeyQ, KeyR, KeyS, KeyT, KeyU, KeyV, KeyW, KeyX, KeyY, KeyZ, KeyLeftBracket, KeyDelete,
		KeyUp, KeyDown, KeyLeft, KeyRight,
		KeyUnknown, KeyCount = KeyUnknown
	};

	class InputCoreSystem : public AbstractCoreSystem
	{
		Keystate previous_[(Uint16)Key::KeyCount]{};
		
		Keystate current_[(Uint16)Key::KeyCount]{};

	public:

		InputCoreSystem();

		~InputCoreSystem();

		void StartUp(const Config &config) override;

		void Update(float delta_time) override;

		void CleanUp() override;

		void UpdateCurrentInput(SDL_Event &e);

		void CarryCurrentInput();

		bool KeyDown(Key key);

		bool KeyUp(Key key);

		bool KeyPressed(Key key);

	private:

		void UpdateKey(SDL_Keysym &keysym, Keystate state);
	};

}
