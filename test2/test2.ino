/*
 * SP/02 - PORTB 직접 제어 UART 비트뱅
 * Board : Arduino Uno
 * TX Pin : D8 (PORTB0)
 * Baud   : 9600 bps
 */

#define BAUD_RATE 9600
#define BIT_TIME (1000000 / BAUD_RATE)

#define TX_BIT 0        // PB0 = D8

void setup() {
  // PORTB0을 출력으로 설정
  DDRB |= (1 << TX_BIT);

  // UART idle 상태 HIGH
  PORTB |= (1 << TX_BIT);

  Serial.begin(9600);
  Serial.println("SP/02 PORTB Bit-Bang UART Test");
  delay(2000);
}

// TX 핀 HIGH
inline void TX_HIGH() {
  PORTB |= (1 << TX_BIT);
}

// TX 핀 LOW
inline void TX_LOW() {
  PORTB &= ~(1 << TX_BIT);
}

// UART 1바이트 전송
void uartSend(char data) {
  // Start Bit
  TX_LOW();
  delayMicroseconds(BIT_TIME);

  // Data Bits (LSB First)
  for (int i = 0; i < 8; i++) {
    if (data & (1 << i))
      TX_HIGH();
    else
      TX_LOW();

    delayMicroseconds(BIT_TIME);
  }

  // Stop Bit
  TX_HIGH();
  delayMicroseconds(BIT_TIME);
}

void loop() {
  uartSend('a');    // 0x61
  Serial.println("Send : a");
  delay(500);
}
