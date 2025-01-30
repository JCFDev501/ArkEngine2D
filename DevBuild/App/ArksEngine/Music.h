#pragma once
struct _Mix_Music;
struct Mix_Chunk;


namespace ArksEngine
{
	class Core;
	class Debug_Log;

	class Music
	{
		ArksEngine::Core* m_pOwner; // This is the a Ptr to the core
		const char* m_pFileName; // This is a path to file
		_Mix_Music* m_pMusic; // This is a Ptr to Mix_Music
		Mix_Chunk* m_pSoundEffect; // This os a Ptr to Mix_Chunk

	public:
		/**
		 * \brief This is a constructor
		 * \param pOwner // This is the a Ptr to the core
		 * \param fileName This is a path to file
		 */
		Music(ArksEngine::Core* pOwner, const char* fileName);

		/**
		 * \brief This is a De-Constructor
		 */
		~Music();

		
		/**
		* \brief This will load a .mp3 file, meant for soundtracks and other similar things
		* \param fileName Path to .mp3 file
		*/
		void Load_Music();

		/**
		* \brief Playes music from a .mp3 file
		* \param fileName Path to .mp3 file
		* \param loops how may times to play track
		*/
		void Play_Music(int loops) const;

		/**
		* \brief Stops music
		*/
		void Stop_Music();
		


		/**
		 * \brief This will load a .wav file, meant for soundEffects and other similar things
		 * \param fileName path to .wav file
		*/
		void Load_SoundEffect();

		

		/**
		 * \brief 
		 * \param fileName path to .wav file
		 * \param loops how many times to play
		 * \param channel what channel to play on
		 */
		void Play_SoundEffect(int loops, int channel) const;

		
		void Set_MusicVolume(int volume);

		/**
		 * \brief controls how loud a sound effect is
		 * \param fileName path to .wav file
		 * \param volume 1 - 100
		 */
		void Set_SoundEffectVolume(int volume) const;


	};
}


