/*
 * SP/04 - UART Loopback Test
 * TX : D8 (PORTB 비트뱅)
 * RX : D0 (UART RX)
 */

#define BAUD_RATE 9600
#define BIT_TIME (1000000 / BAUD_RATE)
#define TX_BIT 0    // PB0 = D8

void setup() {
  // D8 출력 설정
  DDRB |= (1 << TX_BIT);
  PORTB |= (1 << TX_BIT);   // Idle HIGH

  // 하드웨어 UART 시작
  Serial.begin(9600);

  Serial.println("SP/04 UART Loopback Test");
  Serial.println("Connect D8 <-> D0");
  delay(2000);
}

// TX 핀 제어
inline void TX_HIGH() {
  PORTB |= (1 << TX_BIT);
}

inline void TX_LOW() {
  PORTB &= ~(1 << TX_BIT);
}

// 비트뱅 UART 송신
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
  char txChar = 'a';

  // 비트뱅 송신 (D8 → D0)
  uartSend(txChar);

  delay(5); // 수신 안정화 시간

  // RX로 들어온 데이터가 있으면 다시 PC로 출력
  if (Serial.available()) {
    char rxChar = Serial.read();
    Serial.print("Received: ");
    Serial.println(rxChar);
  }

  delay(500);
}
