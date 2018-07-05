#include <Arduino.h>
#include <pins_arduino.h>

#define TX_LED1 2
#define TX_LED2 3
#define TX_LED3 4
#define TX_LED4 5
#define TX_LED5 6
#define TX_LED6 7
#define TX_LED7 8
#define TX_LED8 9

#define RX_LED1 14
#define RX_LED2 15
#define RX_LED3 16
#define RX_LED4 17
#define RX_LED5 18
#define RX_LED6 19
#define RX_LED7 20
#define RX_LED8 21

#define IDENTIFY_LED 10

const unsigned int tx[8] = {TX_LED1, TX_LED2, TX_LED3, TX_LED4, TX_LED5, TX_LED6, TX_LED7, TX_LED8};
const unsigned int rx[8] = {RX_LED1, RX_LED2, RX_LED3, RX_LED4, RX_LED5, RX_LED6, RX_LED7, RX_LED8};

int value = 0;

void setup()
{
  Serial.begin(9600);
  for(int i=0; i<1;i++) {
    pinMode(tx[i], OUTPUT);
    pinMode(rx[i], INPUT);
  }
  pinMode(IDENTIFY_LED, OUTPUT);
  digitalWrite(IDENTIFY_LED, HIGH);
  delay(500);
  digitalWrite(IDENTIFY_LED, LOW);
}

int clampValue(int value) {
  if (value < 0) {
    return 0;
  } else {
    return value;
  }
}

int measureCycle(uint8_t txLed, uint8_t rxLed) {
  int ambientValue = 0;
  int recievedValue = 0;
  // measure ambient
  digitalWrite(txLed, LOW);
  ambientValue = analogRead(rxLed);
  // Serial.print("Ambi: ");
  // Serial.println(ambientValue);
  delay(10);
  digitalWrite(txLed, HIGH);
  delay(10);
  recievedValue = analogRead(rxLed);
  // Serial.print("Reci: ");
  // Serial.println(recievedValue);
  digitalWrite(txLed, LOW);
  return clampValue(recievedValue - ambientValue);
}

void loop()
{
  for(int i=2; i<4;i++) {
    value = measureCycle(tx[i], rx[i]);
    Serial.print("\t");
    Serial.print(i);
    Serial.print(":\t");
    Serial.print(value);
    if (value < 350)
      Serial.print("   Something Here ");
    else
      Serial.print("   Nothing Here");
  
  }
  Serial.print("\n");

  delay(1000);
}



