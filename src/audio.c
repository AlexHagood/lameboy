    
#include <SDL2/SDL.h>
#include "sys.h" 


int audio_test(){
    SDL_AudioSpec want, have;
    SDL_AudioDeviceID dev;

    SDL_Init(SDL_INIT_AUDIO);

    float frequency = 2; // Frequency of the square wave (A4 note)
    int sample_rate = 44100; // Sample rate
    int amplitude = 28000; // Amplitude of the wave

    void audio_callback(void *userdata, Uint8 *stream, int len) {
        static float phase = 0.0f;
        int16_t *buffer = (int16_t *)stream;
        int length = len / 2; // 2 bytes per sample (16-bit audio)

        for (int i = 0; i < length; i++) {
            buffer[i] = (phase < 0.5f ? amplitude : -amplitude);
            phase += frequency / sample_rate;
            if (phase >= 1.0f) {
                phase -= 1.0f;
            }
        }
    }

    SDL_memset(&want, 0, sizeof(want)); // or SDL_zero(want)
    want.freq = sample_rate;
    want.format = AUDIO_S16SYS;
    want.channels = 1;
    want.samples = 4096;
    want.callback = audio_callback;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (dev == 0) {
        SDL_Log("Failed to open audio: %s", SDL_GetError());
    } else {
        SDL_PauseAudioDevice(dev, 0); // Start audio playback
    }
}
    