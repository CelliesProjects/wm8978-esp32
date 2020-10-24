# wm8978-esp32

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e81fc45de095479cba43ecff7cf94b3b)](https://app.codacy.com/manual/CelliesProjects/wm8978-esp32?utm_source=github.com&utm_medium=referral&utm_content=CelliesProjects/wm8978-esp32&utm_campaign=Badge_Grade_Dashboard)

Arduino IDE library for wm8978 codec on ESP32 mcu.

- Tested/works with a M5Stack Node.


### Example code:
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

/* M5Stack WM8978 MCLK gpio number */
#define I2S_MCLKPIN  0

Audio audio(I2S_BCK, I2S_WS, I2S_DOUT);
WM8978 dac;

void setup() {
  /* Setup wm8978 I2C interface */
  if (!dac.begin(I2C_SDA, I2C_SCL)) {
    ESP_LOGE(TAG, "Error setting up dac. System halted");
    while (1) delay(100);
  }

  /* Select I2S MCLK pin */
  audio.i2s_mclk_pin_select(I2S_MCLKPIN);

  WiFi.begin("xxx", "xxx");
  while (!WiFi.isConnected()) {
    delay(10);
  }
  ESP_LOGI(TAG, "Connected. Starting MP3...");
  audio.connecttohost("http://icecast.omroep.nl/3fm-bb-mp3");

  dac.setSPKvol(40); /* max 63 */
  dac.setHPvol(32, 32);
}

void loop() {
  audio.loop();
}

```
To show `ESP_LOGx` messages on the Serial port, compile with `Tools->Core Debug Level` set to `Info`.
