/*
 * SP/01 - 임의 문자 UART 파형 관찰 (비트뱅 방식)
 * Board : Arduino Uno
 * TX Pin : D8
 * Baud   : 9600 bps
 */

const int txPin = 8;
const int baudRate = 9600;
const int bitTime = 1000000 / baudRate; // 약 104us

void setup() {
  pinMode(txPin, OUTPUT);

  // UART idle 상태는 HIGH
  digitalWrite(txPin, HIGH);

  Serial.begin(9600);
  Serial.println("UART Bit-Bang Waveform Test");
  delay(2000);   // 오실로스코프 준비 시간
}

// UART 프레임 전송 함수
void uartSend(char data) {
  // Start Bit
  digitalWrite(txPin, LOW);
  delayMicroseconds(bitTime);

  // Data Bit 8개 (LSB First)
  for (int i = 0; i < 8; i++) {
    if (data & (1 << i))
      digitalWrite(txPin, HIGH);
    else
      digitalWrite(txPin, LOW);

    delayMicroseconds(bitTime);
  }

  // Stop Bit
  digitalWrite(txPin, HIGH);
  delayMicroseconds(bitTime);
}

void loop() {
  uartSend('a');     // 0x61
  Serial.println("Send : a");
  delay(500);
}
