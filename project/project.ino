#include "WiFiManager/WiFiManager.h"
#include "HttpManager/HttpManager.h"
#include <driver/i2s.h>

#define I2S_WS   25  // LRCK
#define I2S_SCK  26  // BCLK
#define I2S_SD   19  // DOUT from mic

const char* ssid = "Barreto";
const char* password = "Miaumiau201";
HTTPClient http;

WiFiManager wifiManager(ssid, password);
HttpManager httpManager;

#define I2S_PORT I2S_NUM_0
#define bufferLen 128
int32_t sBuffer[bufferLen];

void i2s_install() {
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = bufferLen,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin() {
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };
  i2s_set_pin(I2S_PORT, &pin_config);
}

void setup() {
  Serial.begin(115200);
  delay(500);

  i2s_install();
  delay(100);

  i2s_setpin();
  i2s_start(I2S_PORT);

  Serial.println("I2S initialized, starting mic read...");
}

void loop() {
  size_t bytes_read = 0;
  esp_err_t result = i2s_read(I2S_PORT, (void *)sBuffer, sizeof(sBuffer), &bytes_read, portMAX_DELAY);
  if (result == ESP_OK && bytes_read > 0) {
    int samples_read = bytes_read / sizeof(int32_t);

    for (int i = 0; i < samples_read; i++) {
        int32_t raw_sample = sBuffer[i];
        
        // Shift right by 8 to drop least significant 8 bits
        int32_t sample_24 = raw_sample >> 8;
        
        // Sign-extend 24-bit to 32-bit manually
        if (sample_24 & 0x00800000) {  // Check if sign bit (23rd bit) is set
            sample_24 |= 0xFF000000;   // Set upper 8 bits to 1 for negative value
        } else {
            sample_24 &= 0x00FFFFFF;   // Mask upper 8 bits for positive value
        }

        Serial.println(sample_24);
    }
  }
  delay(1000);
}
