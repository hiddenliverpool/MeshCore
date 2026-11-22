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
};
