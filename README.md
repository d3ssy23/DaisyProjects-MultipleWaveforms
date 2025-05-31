## Custom Daisy build - MultipleWaveforms

# You'll need first to download the Daisy libs - libDaisy and DaisySP (check or modify the makefile depening on their path on your machine)

# Intro
- A custom Daisy Pod build integrating 2 knobs - pitch and volume and 2 buttons - mute and changing the waveform, you can listen to it stereo from the line out.

# Build 
- Get the Daisy in bootloader mode and connect it to the computer
- make - will create the build folder and binary
- make program-dfu - will erease and load the build to the Daisy Seed/Pod
