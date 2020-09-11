
// lookup hextable for efficient conversion (avoids using string, or powers)
static const long hextable[] = { 
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1, 0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,-1,10,11,12,13,14,15,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,10,11,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};

// convert from hex in char[] to decimal in unsigned long
unsigned long HexToDec(char *hex) {
   unsigned long ret = 0; 
   while (*hex && ret >= 0) {
      ret = (ret << 4) | hextable[*hex++];
   }
   return ret; 
}

// function to convert decimal to hexadecimal 
void decToHexa(unsigned long input, char* outputBuffer, int base) 
{
  if (base == 2)
  {
      sprintf(outputBuffer,"%lx",input);
  }
  else if(base == 4)
  {
      sprintf(outputBuffer,"%04lx",input);
  }
  else if(base == 6)
  {
      sprintf(outputBuffer,"%06lx",input);
  }
  else if(base == 8)
  {
      sprintf(outputBuffer,"%08lx",input);
  }
  
  strupr(outputBuffer);
}


// reverse the input from big endian to little endian
void reverse_hex(char* input, char* output, int length){

  int j = 0;
  for(int i = length-1; i > 0; i-=2)
  {
      output[j] = input[i-1];
      output[j+1] = input[i];
      j += 2;
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}


void loop() {
  // put your main code here, to run repeatedly:

  // put your input hex here:
  int hexSize = 9; // 8 + /0 // doesn't matter that much, is just used to initalize arrays
  int base = 4; // This base variable determines the size of the number that will be worked on.
                // E.g with "48E8" the base should be 4 and with "48E80100" the base should be 8.
  char input[] = "48E8"; //E80100
  
  // just some output variable with same size as the input
  char output[hexSize] = "";
  char reversedOriginal[hexSize] = {0};
  char reversedHex1[hexSize] = {0};

  Serial.print("Original input: ");
  Serial.print(input);
  Serial.println("");
  
  // reverse the input from big endian to little endian
  reverse_hex(input,output, strlen(input));

  Serial.print("Reversed output: ");
  Serial.print(output);
  Serial.println("");
  
  // convert from hex in char[] to decimal in unsigned long
  unsigned long decVal = HexToDec(output);

  Serial.print("Output in decimal: ");
  Serial.print(decVal);
  Serial.println("");
  
  decToHexa(decVal, reversedHex1,base);

  Serial.print("Output converted back to hex: ");
  Serial.print(reversedHex1);
  Serial.println("");

  reverse_hex(reversedHex1,reversedOriginal, strlen(reversedHex1));
    
  Serial.print("Output converted back to original from hex: ");
  Serial.print(reversedOriginal);
  Serial.println("");
  Serial.println("");
  
  delay(2000);

}
