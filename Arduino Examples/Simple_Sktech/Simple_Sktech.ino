/*
 * Simple sketch to print the keyword over serial.
 * Change GPIO_Pin to your desired input pin.
 * Add a switch or just pull the GPIO_pin high i.e. to VCC to print.
*/
#define GPIO_Pin 2

void setup() {
  Serial.begin(9600); //Init serial port with 9600bps
  pinMode(GPIO_Pin, INPUT);
}

void loop() {
  if (digitalRead(GPIO_Pin) == HIGH){
  Serial.print("Hello");
  delay(2000);
  }
}
