#include <Wire.h>
#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <Arduino_FreeRTOS.h>
#include "Semphr.h"

#define DHTPIN 9
#define DHTTYPE DHT11
#define RECV_PIN 2
#define RELAY 4
#define rtDelay(v) {vTaskDelay(v / portTICK_PERIOD_MS); } // Macro to make things easier

// Instantiate Classes
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
IRrecv irrecv(RECV_PIN);

typedef struct {
  byte code;
  char* value;
} remoteKey;

// Remote keys and codes
const remoteKey keyPairs[21] = {
  {0xFFA25D, "CH-"},
  {0xFF629D, "CH"},
  {0xFFE21D, "CH+"},
  {0xFF22DD, "<<"},
  {0xFF02FD, ">>"},
  {0xFFC23D, ">||"},
  {0xFFE01F, "-"},
  {0xFFA857, "+"},
  {0xFF906F, "EQ"},
  {0xFF9867, "100+"},
  {0xFFB04F, "200+"},
  {0xFF6897, "0"},
  {0xFF30CF, "1"},
  {0xFF18E7, "2"},
  {0xFF7A85, "3"},
  {0xFF10EF, "4"},
  {0xFF38C7, "5"},
  {0xFF5AA5, "6"},
  {0xFF42BD, "7"},
  {0xFF4AB5, "8"},
  {0xFF52AD, "9"}
};

// For decoding signals recieved by IR reciever
decode_results remoteEntry;

// Semaphore Handle
SemaphoreHandle_t xSemaphore;

// Task handles

void setup() {
  // Initialize dht
  dht.begin();

  // Interrupt Service Routine
  attachInterrupt(digitalPinToInterrupt(RECV_PIN), getChannel, RISING);

  // Initialize lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello world");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

// for reading temperature: dht.readTemperature()

void getChannel(){
  if (irrecv.decode(&remoteEntry)) {
    switch (remoteEntry.value, HEX) {
      case keyPairs[1].code:
        lcd.print(keyPairs[1].value);
        break;
      case keyPairs[2].code:
        lcd.print(keyPairs[2].value);
        break;
      default:
        break;
    }
  }
}
void getPassword(){}
void getTreshold(){}

// void convertEntry(byte* entryPtr, char* outputPtr) {
//   for (int i = 0; i < 21; i++) {
//     if (*entryPtr == codes[i]) {
//       *outputPtr = keys[i];
//     }
//   }
// }
