#include <NTPClient.h>
#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include<ArduinoJson.h>
#include<Adafruit_SSD1306.h>
#include<Adafruit_GFX.h>
#include<SPI.h>
#include <WiFiUdp.h>
#include "logo.h"
#include <WiFiManager.h>
#include <ArduinoOTA.h>
#include "cute_icons.h"

// DAY
// Patchy rain nearby
const unsigned char day_176 [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xf8, 0xfd, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf8, 0xf9, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfc, 0x7f, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xe0, 0x3f, 0xf8, 0x0f, 0xff, 0xff, 
	0xfe, 0x1f, 0x80, 0x0f, 0xe0, 0x03, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x07, 0x80, 0x00, 0xff, 0xff, 
	0xff, 0x9e, 0x00, 0x03, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
	0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
	0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x78, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xf8, 0x38, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x38, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 
	0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 
	0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 
	0xff, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
	0xfe, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x07, 0xff, 
	0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// NIGHT
// Partly Cloudy
const unsigned char night_partlyCloudy [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xf0, 0x0f, 0xff, 0xff, 
	0xff, 0xe0, 0x7f, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0x80, 0x00, 0xff, 0xff, 
	0xff, 0xfc, 0x1f, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x3f, 0xfe, 0x00, 0x00, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x07, 0xff, 
	0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x07, 0xff, 
	0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
	0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x03, 0xff, 
	0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


extern const unsigned char thunderstorm_rain[];
extern const unsigned char cloudy[];
extern const unsigned char drizzle[];
extern const unsigned char mist[];
extern const unsigned char rain[];
extern const unsigned char sleet[];
extern const unsigned char snow[];
extern const unsigned char thunderstrom_drizzle[];
extern const unsigned char unknown_prep[];

struct IconDef {
  const unsigned char* bitmap;
  int w;
  int h;
};

IconDef all_icons[] = {
  {day_176, 57, 54},
  {night_partlyCloudy, 57, 54},
  {thunderstorm_rain, 60, 57},
  {cloudy, 60, 53},
  {drizzle, 59, 55},
  {mist, 59, 54},
  {rain, 59, 55},
  {sleet, 60, 54},
  {snow, 57, 58},
  {thunderstrom_drizzle, 59, 55},
  {unknown_prep, 59, 54}
};

struct CuteAnimation {
  const char* name;
  const unsigned char* frame1;
  const unsigned char* frame2;
  int w;
  int h;
  int speedMs;
};

CuteAnimation cute_characters[] = {
  { "Robot", cute_robot_1, cute_robot_2, 58, 54, 350 },
  { "Pacman", cute_pacman_1, cute_pacman_2, 58, 54, 300 },
  { "Cat", cute_cat_1, cute_cat_2, 58, 54, 400 }
};

String url = "https://api.ryzumi.net/api/search/weather?city=tulungagung";
String url_sholat = "https://api.ryzumi.net/api/search/jadwal-sholat?kota=tulungagung";        

Adafruit_SSD1306 display(128, 64, &Wire, -1);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200);

int lastWeatherMinute = -1;
int lastSholatDay = -1;
unsigned long lastCheckTime = 0;
unsigned long lastTimeCheck = 0;
const unsigned long interval = 3000;

String disp_hourStr = "00";
String disp_minStr = "00";
float disp_temp = 0.0;
float disp_feels = 0.0;
String weather_desc = "";
int weather_humidity = 0;
String sholat_str = "";
String marquee_text = "Menghubungkan...";
String public_ip = "Loading..";
int scrollX = 128;
int current_icon_index = 0;
unsigned long lastScrollTime = 0;

String payload;
WiFiClientSecure client;

void setup() {
  system_update_cpu_freq(160);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  delay(300);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextWrap(false);
  // Menggambar array Vertikal secara manual (pixel-by-pixel)
  for (int16_t y = 0; y < 64; y++) {
    for (int16_t x = 0; x < 128; x++) {
      int page = y / 8;
      int byte_idx = page * 128 + x;
      uint8_t pixel_byte = pgm_read_byte(&display_image[byte_idx]);
      if (pixel_byte & (1 << (y % 8))) {
        display.drawPixel(x, y, WHITE);
      }
    }
  }
  display.display();
  delay(2000); // Tahan logo selama 2 detik
  
  display.invertDisplay(0);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.println("CONNECTING");
  display.setCursor(52, 16);
  display.println("TO");
  display.setTextSize(1);
  String saved_ssid = WiFi.SSID();
  if (saved_ssid == "") saved_ssid = "Saved WiFi";
  display.println(saved_ssid);
  display.display();

  WiFiManager wifiManager;
  
  // Set timeout koneksi ke WiFi lama menjadi 2 menit (120 detik)
  wifiManager.setConnectTimeout(120);
  
  // Callback jika tidak ada WiFi yang tersimpan atau gagal konek
  wifiManager.setAPCallback([](WiFiManager *myWiFiManager) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("WIFI SETUP MODE");
    display.println("");
    display.println("Konek ke Hotspot:");
    display.println(myWiFiManager->getConfigPortalSSID());
    display.println("Buka di Browser:");
    display.println("192.168.4.1");
    display.display();
  });

  // Coba konek ke WiFi yang tersimpan, jika gagal buat Hotspot "Wemos_Cuaca"
  if (!wifiManager.autoConnect("Wemos_Cuaca")) {
    Serial.println("Gagal koneksi dan timeout");
    ESP.restart();
    delay(1000);
  }
  display.setCursor(0, 48);
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE);
  display.print("Connected");
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
  timeClient.begin();
  client.setInsecure();
  client.setBufferSizes(4096, 512);

  // Set up OTA
  ArduinoOTA.setHostname("Wemos-Cuaca");
  ArduinoOTA.onStart([]() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("OTA Memulai...");
    display.display();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("OTA Update:");
    display.print(progress / (total / 100));
    display.println("%");
    display.display();
  });
  ArduinoOTA.onEnd([]() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("OTA Selesai!");
    display.println("Restarting...");
    display.display();
  });
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
  unsigned long now = millis();

  // Animasi Marquee Scroll setiap 30 ms
  if (now - lastScrollTime >= 30) {
    lastScrollTime = now;
    scrollX--;
    int textWidth = marquee_text.length() * 6;
    if (scrollX < -textWidth) {
      scrollX = 128;
    }
    draw_screen();
  }

  // Update Jam internal setiap 1 detik agar jam selalu tepat
  if (now - lastTimeCheck >= 1000) {
    lastTimeCheck = now;
    timeClient.update();
    int h = timeClient.getHours();
    int m = timeClient.getMinutes();
    disp_hourStr = (h < 10 ? "0" : "") + String(h);
    disp_minStr = (m < 10 ? "0" : "") + String(m);
  }

  // Cek jadwal cuaca (tiap 5 menit) & sholat (tiap hari)
  if (now - lastCheckTime >= interval) {
    lastCheckTime = now;
    check_and_update_data();
  }
}

void draw_weather_fx(int icon_idx, int iconX, int iconY) {
  // 1. Efek Hujan & Gerimis (rain, drizzle, thunderstrom_drizzle)
  if (icon_idx == 4 || icon_idx == 6 || icon_idx == 9) {
    for (int i = 0; i < 4; i++) {
      int rx = 10 + i * 11;
      int ry = 36 + ((millis() / 35 + i * 5) % 16);
      if (ry < 54) {
        display.drawLine(rx, ry, rx - 2, ry + 3, WHITE);
      }
    }
  }
  // 2. Efek Badai Petir (thunderstorm_rain)
  else if (icon_idx == 2) {
    for (int i = 0; i < 5; i++) {
      int rx = 8 + i * 9;
      int ry = 35 + ((millis() / 25 + i * 4) % 17);
      if (ry < 54) {
        display.drawLine(rx, ry, rx - 2, ry + 4, WHITE);
      }
    }
    // Kilat menyambar setiap 2.5 detik
    if ((millis() % 2500 < 120)) {
      display.drawLine(28, 36, 25, 43, WHITE);
      display.drawLine(25, 43, 29, 43, WHITE);
      display.drawLine(29, 43, 23, 52, WHITE);
    }
  }
  // 3. Efek Mendung / Berawan (cloudy atau unknown)
  else if (icon_idx == 3 || icon_idx == 10) {
    int windX1 = ((millis() / 25) % 65) - 10;
    int windX2 = (((millis() / 35) + 30) % 65) - 10;
    if (windX1 >= 0 && windX1 < 54) display.drawFastHLine(windX1, 38 + iconY, 8, WHITE);
    if (windX2 >= 0 && windX2 < 54) display.drawFastHLine(windX2, 44 + iconY, 6, WHITE);
  }
  // 4. Efek Cerah Siang (day_176)
  else if (icon_idx == 0) {
    if ((millis() / 350) % 2 == 0) {
      display.drawPixel(6, 12 + iconY, WHITE);
      display.drawPixel(14, 4 + iconY, WHITE);
      display.drawPixel(4, 22 + iconY, WHITE);
    } else {
      display.drawPixel(8, 10 + iconY, WHITE);
      display.drawPixel(12, 6 + iconY, WHITE);
      display.drawPixel(3, 24 + iconY, WHITE);
    }
  }
  // 5. Efek Malam (night_partlyCloudy)
  else if (icon_idx == 1) {
    if ((millis() / 600) % 2 == 0) {
      display.drawPixel(8, 10 + iconY, WHITE);
      display.drawPixel(7, 10 + iconY, WHITE);
      display.drawPixel(9, 10 + iconY, WHITE);
      display.drawPixel(8, 9 + iconY, WHITE);
      display.drawPixel(8, 11 + iconY, WHITE);
    }
    if ((millis() / 450) % 2 == 0) {
      display.drawPixel(46, 8 + iconY, WHITE);
      display.drawPixel(45, 8 + iconY, WHITE);
      display.drawPixel(47, 8 + iconY, WHITE);
    }
    if ((millis() / 800) % 2 == 0) {
      display.drawPixel(14, 22 + iconY, WHITE);
    }
  }
  // 6. Efek Kabut (mist)
  else if (icon_idx == 5) {
    int m1 = ((millis() / 30) % 60) - 10;
    int m2 = (((millis() / 45) + 20) % 60) - 10;
    int m3 = (((millis() / 25) + 40) % 60) - 10;
    if (m1 >= 0 && m1 < 50) display.drawFastHLine(m1, 32 + iconY, 12, WHITE);
    if (m2 >= 0 && m2 < 50) display.drawFastHLine(m2, 40 + iconY, 14, WHITE);
    if (m3 >= 0 && m3 < 50) display.drawFastHLine(m3, 48 + iconY, 10, WHITE);
  }
  // 7. Efek Salju (snow / sleet)
  else if (icon_idx == 7 || icon_idx == 8) {
    for (int i = 0; i < 4; i++) {
      int sx = 10 + i * 11 + ((millis() / 200 + i) % 3);
      int sy = 34 + ((millis() / 80 + i * 4) % 18);
      if (sy < 54) {
        display.drawPixel(sx, sy, WHITE);
        display.drawPixel(sx + 1, sy, WHITE);
      }
    }
  }
}

void draw_screen() {
  display.clearDisplay();
  
  // Jam
  display.setCursor(62, 0);
  display.setTextSize(2);
  display.println(disp_hourStr + ":" + disp_minStr);
  
  // Kota
  display.setTextSize(1);
  display.setCursor(62, 20);
  display.print("Tulungagung");
  display.drawLine(62, 28, 127, 28, WHITE);

  // Ikon & Suhu
  display.setCursor(62, 32);
  display.setTextSize(2);
  display.print(disp_temp, 1); 
  display.print((char)247); // Simbol derajat
  display.setTextSize(1);
  display.print("C"); // Huruf C berukuran kecil agar pas di ujung layar 
  
  // SSID & IP (Ganti FL) dengan animasi Ping-Pong jika panjang
  display.setTextSize(1);
  String current_text = ((millis() / 4000) % 2 == 0) ? WiFi.SSID() : public_ip;
  int textWidth = current_text.length() * 6;
  int x = 62;
  
  if (textWidth > 66) { // 66 adalah ruang piksel yang tersedia (128 - 62)
    int max_offset = textWidth - 66;
    int cycle = max_offset * 100; // 50ms per piksel x 2 (bolak-balik)
    int t = millis() % cycle;
    int offset = t / 50;
    if (offset > max_offset) {
      offset = (max_offset * 2) - offset;
    }
    x = 62 - offset;
  }
  display.setCursor(x, 48);
  display.print(current_text);

  // Marquee (Software Scroll)
  display.setTextSize(1);
  display.setCursor(scrollX, 56);
  display.print(marquee_text);

  // Menentukan ikon: Cuaca atau Karakter Animasi Lucu
  const unsigned char* active_bitmap = all_icons[current_icon_index].bitmap;
  int active_w = all_icons[current_icon_index].w;
  int active_h = all_icons[current_icon_index].h;

  unsigned long cycle = millis() % 42000; // Siklus total 42 detik
  int cute_idx = -1;

  if (cycle >= 8000 && cycle < 14000) {
    cute_idx = 0; // Robot BMO (Detik 8 - 14)
  } else if (cycle >= 22000 && cycle < 28000) {
    cute_idx = 1; // Pacman & Ghost (Detik 22 - 28)
  } else if (cycle >= 36000 && cycle < 42000) {
    cute_idx = 2; // Cute Cat (Detik 36 - 42)
  }

  int iconX = 0;
  int iconY = 0;

  if (cute_idx >= 0) {
    CuteAnimation &anim = cute_characters[cute_idx];
    bool f2 = (millis() / anim.speedMs) % 2;
    active_bitmap = f2 ? anim.frame2 : anim.frame1;
    active_w = anim.w;
    active_h = anim.h;
  } else {
    // === MODE CUACA: Animasi Melayang Lembut (Gentle Floating) ===
    const int8_t floatTable[] = { 0, 1, 2, 1 };
    iconY = floatTable[(millis() / 450) % 4];
  }

  // Menggambar ikon terakhir sebagai penutup (clipping mask) teks yang overlap
  display.drawBitmap(iconX, iconY, active_bitmap, active_w, active_h, BLACK, WHITE);

  // Jika sedang mode cuaca, gambar efek partikel cuaca dinamis (hujan/angin/petir/bintang)
  if (cute_idx == -1) {
    draw_weather_fx(current_icon_index, iconX, iconY);
  }

  display.display();
}

void fetch_weather(int minutes) {
  HTTPClient http;
  http.setTimeout(4000);
  http.begin(client, url);
  int httpcode = http.GET();

  if (httpcode != 200) {
    char ssl_err[64] = {0};
    client.getLastSSLError(ssl_err, sizeof(ssl_err));
    Serial.printf("Weather HTTP GET failed, code: %d, SSL err: %s\n", httpcode, ssl_err);
    http.end();
    client.stop();
    return;
  }

  String payload = http.getString();
  http.end();
  client.stop();

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.print("JSON parsing failed: ");
    Serial.println(error.c_str());
    return;
  }

  JsonObject main = doc["main"];
  JsonObject weather_0 = doc["weather"][0];

  const char* city_name = doc["name"];
  float curr_temp = main["temp"];
  float app_temp = main["feels_like"];
  float wind_spd = doc["wind"]["speed"];
  int kelembapan = main["humidity"];
  const char* desc = weather_0["description"];
  const char* icon_code = weather_0["icon"];

  // Mapping Ikon Berdasarkan Kode OpenWeather
  String icon_str = String(icon_code ? icon_code : "");
  if (icon_str == "01d" || icon_str == "02d") current_icon_index = 0; // day_176
  else if (icon_str == "01n" || icon_str == "02n") current_icon_index = 1; // night_partlyCloudy
  else if (icon_str == "03d" || icon_str == "03n" || icon_str == "04d" || icon_str == "04n") current_icon_index = 3; // cloudy
  else if (icon_str == "09d" || icon_str == "09n") current_icon_index = 4; // drizzle
  else if (icon_str == "10d" || icon_str == "10n") current_icon_index = 6; // rain
  else if (icon_str == "11d" || icon_str == "11n") current_icon_index = 2; // thunderstorm_rain
  else if (icon_str == "13d" || icon_str == "13n") current_icon_index = 8; // snow
  else if (icon_str == "50d" || icon_str == "50n") current_icon_index = 5; // mist
  else current_icon_index = 10; // unknown_prep

  // Fetch Public IP hanya sekali saat awal
  if (public_ip == "Loading..") {
    http.setTimeout(3000);
    http.begin(client, "https://ifconfig.me/ip");
    httpcode = http.GET();
    if (httpcode == 200) {
      public_ip = http.getString();
      public_ip.trim();
    } else {
      public_ip = WiFi.localIP().toString();
    }
    http.end();
    client.stop();
  }

  lastWeatherMinute = minutes;
  disp_temp = curr_temp;
  disp_feels = app_temp;
  weather_desc = String(desc ? desc : "");
  weather_humidity = kelembapan;
  marquee_text = weather_desc + " " + String(weather_humidity) + "%" + sholat_str;
  scrollX = 128;
  Serial.printf("Weather data updated: Temp=%.1f C, Desc=%s, IP=%s\n", curr_temp, weather_desc.c_str(), public_ip.c_str());
}

void fetch_sholat(int day) {
  HTTPClient http;
  http.setTimeout(4000);
  http.begin(client, url_sholat);
  int httpcode = http.GET();
  if (httpcode == 200) {
    String payload_sholat = http.getString();
    JsonDocument doc_sholat;
    if (!deserializeJson(doc_sholat, payload_sholat)) {
      JsonObject jadwal = doc_sholat["schedules"][0]["jadwal"];
      const char* subuh = jadwal["subuh"];
      const char* dzuhur = jadwal["dzuhur"];
      const char* ashar = jadwal["ashar"];
      const char* maghrib = jadwal["maghrib"];
      const char* isya = jadwal["isya"];
      if (subuh && dzuhur && ashar && maghrib && isya) {
        sholat_str = " | Subuh: " + String(subuh) + " Dzuhur: " + String(dzuhur) + " Ashar: " + String(ashar) + " Maghrib: " + String(maghrib) + " Isya: " + String(isya);
        lastSholatDay = day;
        marquee_text = weather_desc + " " + String(weather_humidity) + "%" + sholat_str;
        Serial.println("Jadwal Sholat updated:" + sholat_str);
      }
    }
  } else {
    Serial.printf("Sholat HTTP GET failed, code: %d\n", httpcode);
  }
  http.end();
  client.stop();
}

void check_and_update_data() {
  int minutes = timeClient.getMinutes();
  int day = timeClient.getDay();

  // 1. Ambil Cuaca jika baru boot atau setiap interval 5 menit (menit 0, 5, 10, 15, ...)
  if (lastWeatherMinute == -1 || (minutes % 5 == 0 && minutes != lastWeatherMinute)) {
    fetch_weather(minutes);
  }

  // 2. Ambil Jadwal Sholat jika baru boot atau saat hari berganti
  if (lastSholatDay == -1 || day != lastSholatDay) {
    fetch_sholat(day);
  }
}
