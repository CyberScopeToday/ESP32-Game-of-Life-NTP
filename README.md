# ESP32 OLED Screensavers

[![CodeFactor](https://www.codefactor.io/repository/github/cyberscopetoday/slideshow-oled1306/badge)](https://www.codefactor.io/repository/github/cyberscopetoday/slideshow-oled1306)

This project showcases multiple screensavers on an OLED SSD1306 display using an Arduino Nano 3.0. The screensavers include a bouncing DVD logo, Matrix rain effect, digital clock, rotating square, scrolling text, image slideshow, and falling stars.

## Table of Contents

- [Features](#features)
- [Hardware Required](#hardware-required)
- [Wiring Instructions](#wiring-instructions)
- [Software Requirements](#software-requirements)
- [Setup Instructions](#setup-instructions)
  - [Installing Libraries](#installing-libraries)
  - [Creating Bitmaps](#creating-bitmaps)
- [Uploading the Code](#uploading-the-code)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [License](#license)

## Features

1. **Bouncing DVD Logo**: A logo that moves and bounces off the edges of the screen.
2. **Matrix Rain Effect**: Simulates the falling code effect from the Matrix movies.
3. **Digital Clock**: Displays the current time using a real-time clock module.
4. **Rotating Square**: A square that rotates around its center.
5. **Scrolling Text**: A message that scrolls across the screen.
6. **Image Slideshow**: Displays a series of images in a slideshow format.
7. **Falling Stars**: Simulates stars falling from the top of the screen.

## Hardware Required

- **Arduino Nano 3.0** (or compatible board)
- **OLED SSD1306 Display** (128x64 pixels, I2C interface)
- **RTC Module** (e.g., DS1307 or DS3231 for the clock screensaver)
- **Jumper Wires**

## Wiring Instructions

### OLED SSD1306 Display to Arduino Nano

| OLED Pin | Arduino Nano Pin |
|----------|------------------|
| VCC      | 5V (or 3.3V)     |
| GND      | GND              |
| SCL      | A5 (SCL)         |
| SDA      | A4 (SDA)         |

### RTC Module to Arduino Nano

| RTC Pin | Arduino Nano Pin |
|---------|------------------|
| VCC     | 5V               |
| GND     | GND              |
| SCL     | A5 (SCL)         |
| SDA     | A4 (SDA)         |

**Note**: Both the OLED display and RTC module use the I2C interface. They can share the same SCL and SDA lines.

## Software Requirements

- **Arduino IDE** (version 1.8 or higher)
- **Arduino Libraries**:
  - [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)
  - [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
  - [RTClib](https://github.com/adafruit/RTClib)

## Setup Instructions

### Installing Libraries

1. Open the Arduino IDE.
2. Navigate to **Sketch** > **Include Library** > **Manage Libraries...**
3. In the **Library Manager** window, search for:
   - **Adafruit SSD1306**: Install the latest version.
   - **Adafruit GFX Library**: Install the latest version.
   - **RTClib**: Install the latest version by Adafruit.

### Creating Bitmaps

#### For the DVD Logo and Slideshow Images

1. **Prepare Your Images**:
   - Use images in **PNG** or **BMP** format.
   - Resize them to the desired dimensions:
     - **DVD Logo**: 32x16 pixels.
     - **Slideshow Images**: 128x64 pixels.

2. **Convert Images to Bitmaps**:
   - Go to [Image2CPP Converter](https://javl.github.io/image2cpp/).
   - Upload your image.
   - Set the following options:
     - **Output Format**: Arduino Code.
     - **Draw Mode**: Monochrome.
     - **Image Size**: Set to your image's dimensions.
     - **Invert Image Colors**: As needed.
   - Click **Generate Code**.

3. **Copy the Bitmap Code**:
   - Copy the generated array code.

4. **Add Bitmaps to Your Arduino Sketch**:
   - Paste the copied code into your sketch.
   - Place it before the `setup()` function.
   - Ensure you prefix the array with `const unsigned char PROGMEM`.

**Example**:

```cpp
const unsigned char dvdLogo [] PROGMEM = {
  // Paste your DVD logo bitmap array here
};

const unsigned char image1 [] PROGMEM = {
  // Paste your first slideshow image bitmap array here
};

const unsigned char image2 [] PROGMEM = {
  // Paste your second slideshow image bitmap array here
};

// Add as many images as you like
```

### Updating the Slideshow Images in Code

After adding your bitmap arrays for the slideshow images, update the `images` array in the code:

```cpp
const unsigned char* images[] = {
  image1,
  image2,
  // Add additional images if you have them
};
```

## Uploading the Code

1. **Connect your Arduino Nano to your computer** via USB.
2. **Open the Arduino IDE**.
3. **Copy and Paste the Provided Code** into a new sketch.
4. **Select the Correct Board and Port**:
   - Go to **Tools** > **Board** > **Arduino Nano**.
   - Go to **Tools** > **Processor** > Select your processor (**ATmega328P** or **ATmega328P (Old Bootloader)**).
   - Go to **Tools** > **Port** > Select the COM port associated with your Arduino Nano.
5. **Compile the Sketch**:
   - Click the **Verify** button (checkmark icon) to compile and check for errors.
6. **Upload the Sketch**:
   - Click the **Upload** button (right-arrow icon) to upload the code to your Arduino Nano.

## Usage

- **Automatic Screensaver Switching**:
  - The program automatically cycles through the screensavers every 10 seconds.
  - You can adjust the duration by changing the `screenDuration` variable (in milliseconds).

- **Customizing the Message in Scrolling Text**:
  - Find the `message` variable in the code and change it to your desired text.
  - Example:
    ```cpp
    String message = "Hello, World!";
    ```

- **Adjusting Screensaver Parameters**:
  - **Matrix Effect**: Change the `delay(30);` value to speed up or slow down the effect.
  - **Rotating Square**: Modify the `angle` increment or `size` variable for different rotation speeds or square sizes.
  - **Falling Stars**: Adjust `numStars` or star `speed` for more or fewer stars or different falling speeds.

## Troubleshooting

- **Display Not Working**:
  - Ensure all wiring connections are correct.
  - Check that the OLED display I2C address (`0x3C` or `0x3D`) matches the one in the code:
    ```cpp
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    ```
  - Use an I2C scanner sketch to detect connected I2C devices.

- **RTC Module Issues**:
  - Make sure the RTC module is connected correctly.
  - If the time isn't updating, the RTC battery might be dead or missing.
  - Verify that the RTC module is compatible with the `RTClib` library.

- **Compilation Errors**:
  - Ensure all required libraries are installed correctly.
  - Double-check that all bitmap arrays are correctly formatted and placed in the code.

- **Memory Issues**:
  - Large bitmaps can consume a lot of memory.
  - If you encounter memory errors, reduce the number or size of images.
  - Use `PROGMEM` to store large arrays in flash memory.

## License

This project is open-source and available under the MIT License.

---

**Note**: This project is intended for educational purposes. Always ensure your hardware connections are secure to prevent damage to your components.
