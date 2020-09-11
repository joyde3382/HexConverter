void setup() {
  // put your setup code here, to run once:
Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char first[] = "48E80100";
  int i;

  uint32_t test = 0x + first;
  
  uint32_t test2 = __builtin_bswap32(test);
  Serial.print(test);
  Serial.print(test2);
  //Serial.print(1234);
  
  delay(1000);

}
