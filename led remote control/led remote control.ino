#include <IRremote.h>
#define RECV_PIN 7
#define BLED 8
#define YLED 9

IRrecv irrecv(RECV_PIN);
decode_results results;

  // char* keys[21] = { "CH-", "CH", "CH+", "<<", ">>", ">||", "-", "+", "EQ", "100+", "200+", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
  // byte* codes[21] = { 0xFFA25D, 0xFF629D, 0xFFE21D, 0xFF22DD, 0xFF02FD, 0xFFC23D, 0xFFE01F, 0xFFA857, 0xFF906F, 0xFF9867, 0xFFB04F, 0XFF6897, 0xFF30CF, 0xFF18E7, 0xFF7A85, 0xFF10EF, 0xFF38C7, 0xFF5AA5, 0xFF42BD, 0xFF4AB5, 0xFF52AD };

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(BLED, OUTPUT);
  pinMode(YLED, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {
      case 0xFF18E7:
        digitalWrite(YLED, LOW);
        digitalWrite(BLED, HIGH);
        break;
      case 0xFF30CF:
        digitalWrite(BLED, LOW);
        digitalWrite(YLED, HIGH);
        break;
      default:
      break;
    }
    irrecv.resume();
  }
}