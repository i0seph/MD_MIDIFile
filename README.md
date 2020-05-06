## This fork is not original.

I patched for esp32 SPIFFS.

if you want to find original library, visit MajicDesigns/MD_MIDIFile.

Thanks MajicDesigns!


## MD_MIDIFile Standard MIDI File Interpreter Library

This library allows Standard MIDI Files (SMF) to be read from an SD card and played through a MIDI interface. SMF can be opened and processed, with MIDI and SYSEX events passed to the calling program through callback functions. This allows the calling application to manage sending to a MIDI synthesizer through serial interface or other output device, such as a MIDI shield. 
* SMF playing may be controlled through the library using methods to start, pause and restart playback. 
* SMF may be automatically looped to play continuously. 
* Time ticks are normally generated by the library during playback, but this can be taken over by the user program if different time or synchronization with external MIDI clock is required.

External dependencies:
* *SdFat* library found [here](https://github.com/greiman?tab=repositories) used by the library to read SMF from the the SD card.
* *MIDI interface hardware* as described in the library documentation or similar, a USB interface with converter or a MIDI shield.

If you like and use this library please consider making a small donation using [PayPal](https://paypal.me/MajicDesigns/4USD)

[Library Documentation](https://majicdesigns.github.io/MD_MIDIFile/)
