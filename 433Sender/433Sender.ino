
/*
  433 Sender
  Sends 433 Mhz Codes to power sockets.

  Uses rc-switch from https://github.com/sui77/rc-switch

*/

#include <RCSwitch.h>

// #define DEBUGLOG // Uncomment to enable Debug Console output
#define DATAPIN D0 // Data PIN on Board

RCSwitch mySwitch = RCSwitch();
char systemCode[32] = {0};
int unitCode = 0;
int command = -1;
String recvBuffer = "";

void setup() {

  pinMode(DATAPIN, OUTPUT);
  digitalWrite(DATAPIN, LOW);   // I do this first to avoid any reverse polarity

  mySwitch.enableTransmit(DATAPIN);
  mySwitch.setRepeatTransmit(5);
  Serial.setTimeout(50);
  Serial.begin(115200);
}

void loop() {

  if (Serial.available() > 0) {
    recvBuffer = Serial.readStringUntil('\n');
    parseSerial();
  }

#ifdef DEBUGLOG
  if (command > -1) {
    Serial.print("System Code: ");
    Serial.println(systemCode);
    Serial.print("Unit Code: ");
    Serial.println(unitCode);
    Serial.print("Command: ");
    Serial.println(command);
  }
#endif

  switch (command) {
    case 0:
      mySwitch.switchOff(systemCode, unitCode);
      break;
    case 1:
      mySwitch.switchOn(systemCode, unitCode);
      break;
    default:
      command = -1;
      return;
  }
 
  command = -1;
  memset(systemCode, 0, sizeof(systemCode));
}


void parseSerial() {
  getValue(recvBuffer, ' ', 0).toCharArray(systemCode, 32);
  unitCode = getValue(recvBuffer, ' ' , 1).toInt();
  command = getValue(recvBuffer, ' ', 2).toInt();
}


String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

