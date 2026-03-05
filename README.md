# wm8978-esp32

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/7bef2c7f6e0f4103ac73b2fea5449295)](https://www.codacy.com/gh/CelliesProjects/wm8978-esp32/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=CelliesProjects/wm8978-esp32&amp;utm_campaign=Badge_Grade)

Arduino IDE library for wm8978 dac on ESP32 mcu. Tested/works with a M5Stack Node.

### Example code:

#### Setup i2c and wm8978 in one call

```c++
#include <WM8978.h> /* https://github.com/CelliesProjects/wm8978-esp32 */
#include <Audio.h>  /* https://github.com/schreibfaul1/ESP32-audioI2S */

/* M5Stack Node WM8978 I2C pins */
#define I2C_SDA 21
#define I2C_SCL 22

/* M5Stack Node I2S pins */
#define I2S_BCK 5
#define I2S_WS 13
#define I2S_DOUT 2
#define I2S_DIN 34
#define I2S_MCLK 0

const char *SSID = "xxx"; 
const char *PSK = "xxx"; 

WM8978 dac;

void audio_info(Audio::msg_t m)
{
    Serial.printf("%s: %s\n", m.s, m.msg);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("starting");

    /* Setup i2c and wm8978 in one call */
    if (!dac.begin(I2C_SDA, I2C_SCL))
    {
        Serial.println("Error setting up dac. System halted");
        while (1)
            delay(100);
    }
    dac.setSPKvol(40); /* max 63 */
    dac.setHPvol(32, 32);

    WiFi.begin(SSID, PSK);
    WiFi.setSleep(false);
    while (!WiFi.isConnected())
        delay(10);
    
    Serial.println("Connected. Starting MP3...");

    /* Setup audio */
    Audio audio;

    Audio::audio_info_callback = audio_info;

    /* Set i2s pins */
    audio.setPinout(I2S_BCK, I2S_WS, I2S_DOUT, I2S_MCLK);
    audio.setConnectionTimeout(5000, 5000);
    audio.connecttohost("http://icecast.omroep.nl/3fm-bb-mp3");

    if (!audio.isRunning())
        Serial.println("could not start stream");

    audio.setVolume(20);

    while (1)
    {
        vTaskDelay(25);
        audio.loop();
    }
}

void loop()
{
}
```

#### Setup i2c and wm8978 separately

```c++
#include <WM8978.h> /* https://github.com/CelliesProjects/wm8978-esp32 */
#include <Audio.h>  /* https://github.com/schreibfaul1/ESP32-audioI2S */

/* M5Stack Node WM8978 I2C pins */
#define I2C_SDA 21
#define I2C_SCL 22

/* M5Stack Node I2S pins */
#define I2S_BCK 5
#define I2S_WS 13
#define I2S_DOUT 2
#define I2S_DIN 34
#define I2S_MCLK 0

const char *SSID = "xxx"; 
const char *PSK = "xxx"; 

WM8978 dac;

void audio_info(Audio::msg_t m)
{
    Serial.printf("%s: %s\n", m.s, m.msg);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("starting");

    /* Setup i2c */
    if (!Wire.begin(I2C_SDA, I2C_SCL, 400000))
    {
        Serial.println("Error setting up i2c. System halted");
        while (1)
            delay(100);
    }

    /* Setup wm8978 */
    if (!dac.begin())
    {
        Serial.println("Error setting up dac. System halted");
        while (1)
            delay(100);
    }
    dac.setSPKvol(40); /* max 63 */
    dac.setHPvol(32, 32);

    WiFi.begin(SSID, PSK);
    WiFi.setSleep(false);
    while (!WiFi.isConnected())
        delay(10);
    
    Serial.println("Connected. Starting MP3...");

    /* Setup audio */
    Audio audio;

    Audio::audio_info_callback = audio_info;

    /* Set i2s pins */
    audio.setPinout(I2S_BCK, I2S_WS, I2S_DOUT, I2S_MCLK);
    audio.setConnectionTimeout(5000, 5000);
    audio.connecttohost("http://icecast.omroep.nl/3fm-bb-mp3");

    if (!audio.isRunning())
        Serial.println("could not start stream");

    audio.setVolume(20);

    while (1)
    {
        vTaskDelay(25);
        audio.loop();
    }
}

void loop()
{
}
```

