/*
 * SP/05 - UART Character Repeat Verification
 * TX : D8 (PORTB Bit-Bang)
 * RX : D0 (UART RX)
 */

#define BAUD_RATE 9600
#define BIT_TIME (1000000 / BAUD_RATE)
#define TX_BIT 0    // PB0 = D8

char testChars[] = { 'a', 'A', 'Z' };
int indexChar = 0;

void setup() {
  DDRB |= (1 << TX_BIT);
  PORTB |= (1 << TX_BIT);   // Idle HIGH

  Serial.begin(9600);
  Serial.println("SP/05 UART Character Test");
  Serial.println("Characters: a, A, Z");
  delay(2000);
}

// TX 제어
inline void TX_HIGH() {
  PORTB |= (1 << TX_BIT);
}

inline void TX_LOW() {
  PORTB &= ~(1 << TX_BIT);
}

// 비트뱅 UART 송신
void uartSend(char data) {
  TX_LOW();                         // Start Bit
  delayMicroseconds(BIT_TIME);

  for (int i = 0; i < 8; i++) {     // Data Bits
    if (data & (1 << i))
      TX_HIGH();
    else
      TX_LOW();
    delayMicroseconds(BIT_TIME);
  }

  TX_HIGH();                        // Stop Bit
  delayMicroseconds(BIT_TIME);
}

void loop() {
  char tx = testChars[indexChar];

  uartSend(tx);   // D8 → D0 전송
  delay(5);

  if (Serial.available()) {
    char rx = Serial.read();
    Serial.print("Send: ");
    Serial.print(tx);
    Serial.print("  |  Receive: ");
    Serial.println(rx);
  }

  indexChar++;
  if (indexChar >= 3) indexChar = 0;

  delay(700);
}
