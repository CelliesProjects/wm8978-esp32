# wm8978-esp32

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/7bef2c7f6e0f4103ac73b2fea5449295)](https://www.codacy.com/gh/CelliesProjects/wm8978-esp32/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=CelliesProjects/wm8978-esp32&amp;utm_campaign=Badge_Grade)

Arduino IDE library for wm8978 dac on ESP32 mcu. Tested/works with a M5Stack Node.

### Example code:

#### Setup i2c and wm8978 in one call

```c++
#include <WM8978.h> /* https://github.com/CelliesProjects/wm8978-esp32 */
#include <Audio.h>  /* https://github.com/schreibfaul1/ESP32-audioI2S */

/* M5Stack Node WM8978 I2C pins */
#define I2C_SDA     21
#define I2C_SCL     22

/* M5Stack Node I2S pins */
#define I2S_BCK      5
#define I2S_WS      13
#define I2S_DOUT     2
#define I2S_DIN     34
#define I2S_MCLK     0

Audio audio;
WM8978 dac;

void setup() {
  /* Setup wm8978 I2C interface */
  if (!dac.begin(I2C_SDA, I2C_SCL)) {
    log_e("Error setting up dac. System halted");
    while (1) delay(100);
  }
  dac.setSPKvol(40); /* max 63 */
  dac.setHPvol(32, 32);

  WiFi.begin("xxx", "xxx");
  while (!WiFi.isConnected()) {
    delay(10);
  }

  /* set i2s pins */
  audio.setPinout(I2S_BCK, I2S_WS, I2S_DOUT, I2S_DIN, I2S_MCLK);

  log_i("Connected. Starting MP3...");
  audio.connecttohost("http://icecast.omroep.nl/3fm-bb-mp3");
}

void loop() {
  audio.loop();
}

```

#### Setup i2c and wm8978 separately

```c++
#include <Wire.h>
#include <WM8978.h> /* https://github.com/CelliesProjects/wm8978-esp32 */
#include <Audio.h>  /* https://github.com/schreibfaul1/ESP32-audioI2S */

/* M5Stack Node WM8978 I2C pins */
#define I2C_SDA     21
#define I2C_SCL     22

/* M5Stack Node I2S pins */
#define I2S_BCK      5
#define I2S_WS      13
#define I2S_DOUT     2
#define I2S_DIN     34
#define I2S_MCLK     0

WM8978 dac;
Audio audio;

void setup() {

  if (!Wire.begin(I2C_SDA, I2C_SCL, 400000))
    log_e("i2c setup error!");

  if (!dac.begin())
    log_e("WM8978 setup error!");

  dac.setSPKvol(40); /* max 63 */
  dac.setHPvol(32, 32);

  WiFi.begin("xxx", "xxx");
  while (!WiFi.isConnected()) {
    delay(10);
  }

  /* set i2s pins */
  audio.setPinout(I2S_BCK, I2S_WS, I2S_DOUT, I2S_DIN, I2S_MCLK);

  log_i("Connected. Starting MP3...");
  audio.connecttohost("http://icecast.omroep.nl/3fm-bb-mp3");
}

void loop() {
  audio.loop();
}
```

