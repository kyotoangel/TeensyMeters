# 1 - Presentation of the project / What you need to recreate it yourself
## 1.1 - TeensyMeters project
What I am attempting to do with this project is... well... recreating the minimeters app but with a teensy and a screen, so I could see audio information without having to make my laggy computer more laggy (and also to get more into DSP).
So this project is open source, and you could simply recreate it with : 
- A Teensy 4.0 board
- An ILI9341 screen
- A Teensy Audio Shield
- Visual Studio Code and Platform.io
- A copy of this source code in VS code and simply uploading it to your teensy ! (I listed the pins I'm using for using the screens, they don't interfere with the audio shield pins, since I'm only using the I2S bus to sample audio)

The project is still in development, I plan on regularly updating it to add more features !

## 1.2 - Aditionnal features
### 1.2.1 - External power supply
I want this project to be as portable as possible (by adding a battery to power up the teensy), to do so you'll need to dissociate "Vusb" and "Vin" pads on the teensy, more info here : https://www.pjrc.com/teensy/external_power.html
The best way to do it is by following this kind of schematic (shoutout Leonard for the idea and the explaination) : ![WhatsApp Image 2025-08-08 à 02 26 45_915d9bfd](https://github.com/user-attachments/assets/b988fee9-76e9-4d38-84d2-4c3e7aaea560)
By doing so and using a MOSHFET, you can use the battery / external usb C power supply and still be able to switch and use the teensy micro usb input to program it ! (priority given to the micro usb input of the teensy)

(for the USB C / battery supply, i'm using this one : https://aliexpress.com/item/1005003586772730.html)


# 2 - Breadboard routing
## 2.1 - LCD display connections
I used the following scheme to route the LCD screen (ILI9341 screen) - I didn't used the touchscreen features for this project
<img width="1535" height="572" alt="Display Schematics" src="https://github.com/user-attachments/assets/2e32194e-9094-4bf9-8446-18eb0c0a96b8" />
## 2.2 - Teensy Audio Shield connections
