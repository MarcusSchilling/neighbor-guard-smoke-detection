void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Initialize the Serial monitor with the baud rate 115200
  while (true) {
    delay(100);
    loop();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello, World!"); // Print "Hello, World!" to the Serial monitor
}
