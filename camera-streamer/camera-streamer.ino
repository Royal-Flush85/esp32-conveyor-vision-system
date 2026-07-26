#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>
#include "soc/soc.h"           
#include "soc/rtc_cntl_reg.h"

#define AP_SSID "esp32cam"
#define AP_PASS "IEEEProjectInit32"

WebServer server(80);

void handleCapture() {
  auto img = esp32cam::capture();
  if (img == nullptr) {
    server.send(500, "", "");
    return;
  }
  server.setContentLength(img->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  img->writeTo(client);
}

void setup() {
  // disable burnout detector
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting...");

  auto res = esp32cam::Resolution::find(1024, 768);
  esp32cam::Config cfg;
  cfg.setPins(esp32cam::pins::AiThinker);
  cfg.setResolution(res);
  cfg.setJpeg(80);

  //check camera started
  bool ok = esp32cam::Camera.begin(cfg);
  if (!ok) {
    Serial.println("FATAL: Camera initialization failed. Check wiring/power.");
    return; // Halt execution if hardware fails
  }
  Serial.println("Camera initialized successfully.");

  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  
  server.on("/capture.jpg", handleCapture);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

}
