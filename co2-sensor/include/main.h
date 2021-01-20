#include <m5stack_core2/pins_arduino.h>
#include <Arduino.h>
#include <M5Core2.h>
#include <SparkFun_SCD30_Arduino_Library.h>

// libraries for SD card
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <sys/time.h>
#include <SPIFFS.h>

// libraries for WiFi AccessPoint and ConfigPortal
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiMulti.h>
#include <ESPAsync_WiFiManager.h>

// library for time sync
#include <NTPClient.h>

#include <smoca_logo.h>

#define VERSION_NUMBER "1.0.0"
#define UPDATE_SERVER "co2-sensor-firmware.smoca.ch"

#define _ESPASYNC_WIFIMGR_LOGLEVEL_ 3

#define GRAPH_UNITS 240

#define NUM_WIFI_CREDENTIALS 1
#define MAX_SSID_LEN 32
#define MAX_PW_LEN 64
#define MIN_AP_PASSWORD_SIZE 8
#define USE_DHCP_IP true
#define USE_CONFIGURABLE_DNS true

#define TIME_SYNC_HOUR 2
#define TIME_SYNC_MIN rand() % 60

#define STATE_FILENAME "/state"
#define CONFIG_FILENAME "/wifi_config"

String randomPassword();

void loadStateFile();

void saveStateFile();

void initAPIPConfigStruct(WiFi_AP_IPConfig &in_WM_AP_IPconfig);

void initSTAIPConfigStruct(WiFi_STA_IPConfig &in_WM_STA_IPconfig);

void initWiFi();

void initSD();

void initAirSensor();

void checkWiFiStatus();

void checkWiFi();

uint8_t connectMultiWiFi();

void disconnectWiFi(bool wifiOff, bool eraseAP);

void configWiFi(WiFi_STA_IPConfig in_WM_STA_IPconfig);

void displayIPConfigStruct(WiFi_STA_IPConfig in_WM_STA_IPconfig);

void loadConfigData();

void saveConfigData();

void handleNavigation(struct state *state);

void handleWiFi(struct state *oldstate, struct state *state);

void startWiFiManager(ESPAsync_WiFiManager *ESPAsync_WiFiManager, struct state *oldstate, struct state *state);

void resetWiFiManager(ESPAsync_WiFiManager *ESPAsync_WiFiManager, struct state *state);

void resetCallback();

void saveConfigPortalCredentials(ESPAsync_WiFiManager *ESPAsync_WiFiManager);

bool areRouterCredentialsValid();

void setupWiFiManager(ESPAsync_WiFiManager *ESPAsync_WiFiManager);

void handleUpdate(struct state *oldstate, struct state *state);

void fetchRemoteVersion(struct state *state, const char *version);

void updateTouch(struct state *state);

void updateTime(struct state *state);

void updateBattery(struct state *state);

void updateCo2(struct state *state);

void updateGraph(struct state *oldstate, struct state *state);

void updateLed(struct state *oldstate, struct state *state);

void updatePassword(struct state *state);

void saveStateFile(struct state *oldstate, struct state *state);

void updateWiFiState(struct state *oldstate, struct state *state);

void updateTimeState(struct state *oldstate, struct state *state);

void createSprites();

uint16_t co2color(int value);

void drawScreen(struct state *oldstate, struct state *state);

void drawHeader(struct state *oldstate, struct state *state);

void drawValues(struct state *oldstate, struct state *state);

void drawGraph(struct state *oldstate, struct state *state);

void drawCalibrationSettings(struct state *oldstate, struct state *state);

void drawCalibrationAlert(struct state *oldstate, struct state *state);

void drawWiFiSettings(struct state *oldstate, struct state *state);

void drawTimeSettings(struct state *oldstate, struct state *state);

void drawUpdateSettings(struct state *oldstate, struct state *state);

void hideButtons();

void clearScreen(struct state *oldstate, struct state *state);

bool needFirmwareUpdate(const char *deviceVersion, const char *remoteVersion);

void syncTime(struct state *state);

void writeSsd(struct state *state);

String padTwo(String input);

void writeFile(fs::FS &fs, const char *path, const char *message);

void printTime();

void syncTime(struct state *state);

void setRtc(struct state *state);

void setTimeFromRtc();

void appendFile(fs::FS &fs, const char *path, const char *message);

void setDisplayPower(bool state);

uint32_t Read32bit(uint8_t Addr);

uint32_t ReadByte(uint8_t Addr);

void WriteByte(uint8_t Addr, uint8_t Data);