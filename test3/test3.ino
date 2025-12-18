/*
 * SP/03 - UART 송신/수신 파형 비교
 * CH1 : D8 (PORTB 비트뱅 TX)
 * CH2 : D0 (UART RX)
 */

#define BAUD_RATE 9600
#define BIT_TIME (1000000 / BAUD_RATE)
#define TX_BIT 0    // PB0 = D8

void setup() {
  // D8 출력 설정
  DDRB |= (1 << TX_BIT);
  PORTB |= (1 << TX_BIT);   // Idle HIGH

  // 하드웨어 UART 초기화
  Serial.begin(9600);

  Serial.println("SP/03 TX / RX Waveform Compare");
  delay(2000);
}

// TX 제어
inline void TX_HIGH() {
  PORTB |= (1 << TX_BIT);
}

inline void TX_LOW() {
  PORTB &= ~(1 << TX_BIT);
}

// UART 비트뱅 송신
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
  char txData = 'a';

  // 하드웨어 UART로도 송신 (RX 파형 생성)
  Serial.write(txData);

  // 비트뱅 송신
  uartSend(txData);

  delay(500);
}

