#pragma once

#include <Arduino.h>
#include <esp_sleep.h>
#include <helpers/ESP32Board.h>

class XiaoS3WIOBoard : public ESP32Board {
public:
  XiaoS3WIOBoard() { }

  void begin() {
    while (!Serial.availableForWrite())
      delay(10);

    ESP32Board::begin();
  }

  const char* getManufacturerName() const override {
    return "Xiao S3 WIO";
  }

  void powerOff() override {
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_21, 0);
    esp_deep_sleep_start();
  }

  uint16_t getBattMilliVolts() override {
    analogReadResolution(12);
    uint32_t mv = analogReadMilliVolts(1); // GPIO 1 (A0/D0)
    return mv * 2; // Multiply by 2 for the 1:1 voltage divider
  }
};
