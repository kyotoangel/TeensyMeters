# 1 - Presentation of the project / What you need to recreate it yourself
## 1.1 - TeensyMeters project
What I am attempting to do with this project is... well... recreating the minimeters app but with a teensy and a screen, so I could see audio information without having to make my laggy computer more laggy (and also to get more into DSP).
So this project is open source, and you could simply recreate it with : 
- A Teensy 4.0 board
- An ILI9341 screen
- A Teensy Audio Shield
- Visual Studio Code and Platform.io
- A copy of this source code in VS code and simply uploading it to your teensy ! (I listed the pins I'm using for using the screens, they don't interfere with the audio shield pins, since I'm only using the I2S bus to sample audio)


# 2 - Breadboard routing
## 2.1 - LCD display connections
I used the following scheme to route the LCD screen (ILI9341 screen) - I didn't used the touchscreen features for this project
<img width="1535" height="572" alt="Display Schematics" src="https://github.com/user-attachments/assets/2e32194e-9094-4bf9-8446-18eb0c0a96b8" />
## 2.2 - Teensy Audio Shield connections
