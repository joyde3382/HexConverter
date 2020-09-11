# 1 "c:\\Projects\\HexConverter\\SampleCode.ino"
# 1 "c:\\Projects\\HexConverter\\SampleCode.ino"
void array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1 < 0xA ? '0' + nib1 : 'A' + nib1 - 0xA;
        buffer[i*2+1] = nib2 < 0xA ? '0' + nib2 : 'A' + nib2 - 0xA;
    }
    buffer[len*2] = '\0';
}

unsigned long HexToDec(String hexString) {
    unsigned long ret;
    for(int i=0, n=hexString.length(); i!=n; ++i) {
        char ch = hexString[i];
        int val = 0;
        if('0'<=ch && ch<='9') val = ch - '0';
        else if('a'<=ch && ch<='f') val = ch - 'a' + 10;
        else if('A'<=ch && ch<='F') val = ch - 'A' + 10;
        else continue; // skip non-hex characters
        ret = ret*16 + val;
    }
    //Serial.print(ret);
    //Serial.println(" ret");
    return ret;
}



void setup() {
  // put your setup code here, to run once:
Serial.begin(38400);
}




void loop() {
  // put your main code here, to run repeatedly:

unsigned long int b;
char str[] = "01,00 02 55 04 03 00 00 00 00 00 48 E8 01 00 E8 03"; //define the delay for 254.6 mm to 191.1 mm then back to 254.6 mm (48 E8 01 00 = 1250 ms delay) which is what is being modified here
//note that the 48 E8 01 00 is in LSB format which will need to be changed to MSB to then be converted to an unsigned long int.
//48 E8 01 00 turns into 00 01 E8 48 then can be converted to 125000 as an unsigned long int.
char str1[9] = "00000000"; //pulling 4 hex bytes (8 characters) out to be modified

Serial.print(str[33]);
Serial.print(str[34]);
Serial.print(" ");
Serial.print(str[36]);
Serial.print(str[37]);
Serial.print(" ");
Serial.print(str[39]);
Serial.print(str[40]);
Serial.print(" ");
Serial.print(str[42]);
Serial.print(str[43]);
Serial.print(" ");
Serial.println("LSB - str");

//spaces are not needed and this doesn't need to be printed, this is just for debugging

str1[0] = str[42];
str1[1] = str[43];
str1[2] = str[39];
str1[3] = str[40];
str1[4] = str[36];
str1[5] = str[37];
str1[6] = str[33];
str1[7] = str[34];
//str1[8] = '/0';

Serial.print(str1[0]);
Serial.print(str1[1]);
Serial.print(" ");
Serial.print(str1[2]);
Serial.print(str1[3]);
Serial.print(" ");
Serial.print(str1[4]);
Serial.print(str1[5]);
Serial.print(" ");
Serial.print(str1[6]);
Serial.print(str1[7]);
Serial.print(" ");
Serial.println("MSB - str1");

//convert hex to decimal
unsigned long int ret2 = HexToDec(str1);


Serial.print(ret2);
Serial.println(" Actual 32 Bit Decimal");

//modify it if needed

ret2 = ret2 + random(5000);
Serial.print(ret2);
Serial.println(" Randomized ret2");

//convert it back

//long c=0;
  byte d[4];
//  Serial.println("Original:");
//  Serial.println(b,HEX); //these will not have leading zeros
  delay(1000);

  for (int i=0; i<4; i++)
  {
    d[i]=((ret2>>(i*8)) & 0xff); //extract the right-most byte of the shifted variable
//   if (d[i] < 16) {Serial.print("0");}
//    Serial.println(d[i],HEX);
    delay(100);
//   return ret2;
  }

/*



if (d[3] < 16) {Serial.print("0");}

Serial.print(d[3], HEX);

Serial.print(" ");

if (d[2] < 16) {Serial.print("0");}

Serial.print(d[2], HEX);

Serial.print(" ");

if (d[1] < 16) {Serial.print("0");}

Serial.print(d[1], HEX);

Serial.print(" ");

if (d[0] < 16) {Serial.print("0");}

Serial.print(d[0], HEX);



Serial.println(" Individual bytes");



*/
# 136 "c:\\Projects\\HexConverter\\SampleCode.ino"
//combine it back to the full command, only with a modified value now


char str2[32] = "";
array_to_string(d, 4, str2);
Serial.print("New Command ");
Serial.println(str2);



delay(1000);

//original HEX
Serial.print(str);
Serial.println(" Original HEX");

//modified HEX

str[33]=str2[0];
str[34]=str2[1];
str[36]=str2[2];
str[37]=str2[3];
str[39]=str2[4];
str[40]=str2[5];
str[42]=str2[6];
str[43]=str2[7];

Serial.print(str[33]);
Serial.print(str[34]);
Serial.print(" ");
Serial.print(str[36]);
Serial.print(str[37]);
Serial.print(" ");
Serial.print(str[39]);
Serial.print(str[40]);
Serial.print(" ");
Serial.print(str[42]);
Serial.print(str[43]);
Serial.print(" ");
Serial.println("LSB #2");

Serial.print(str);
Serial.println(" Modified Full HEX");
Serial.println(" ");

}
