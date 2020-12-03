#include <Wire.h>
#include <EEPROM.h>
#include <rgb_lcd.h>
String s = "0";
unsigned long int xyz = 0;
int address = 143, read_value = 0, eeprom = A1, eeprom_clr = A2, relay = A3, sense = 2,
    EXTERNAL_RFID = 3, OUT = 5, IN = 4, GND = 6, pir_header = 7, count = 0, statePIN = LOW, previous = LOW, say = 0,
    statu, statu_in, statu_out, statu_pir, statu_eeprom, x;
int sclPin = A5, sdaPin = A4;
int gnd_sensor_time = 50; // 1 = 1 msn // açma kapama süresi
int zaman = 50; // 10 = 1 sn // person "0" olunca relay kapanma süresi
int dividing = 10; // zaman'ı bölen sayısı
int t = 1000; // iki sensörden geçiş süresi
int t_setup = 2500; // setup bölümünde tanıtım yazı süresi
//-------------------------------------------------------- LCD başlangıç
rgb_lcd lcd; // C:\Users\USER\Documents\Arduino\libraries\Grove_LCD_RGB_Backlight-master
//-------------------------------------------------------- LCD bitiş
/* Software Communication List ==>
   reset & restart
   eeprom
   clear
   electric
   open
   close
   ++
   --
   sensor
   end
*/
void setup() {
  Serial.begin(115200);
  //-------------------------------------------------------- LCD başlangıç
  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 255);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" 3e-turkey.com ");
  Serial.println("3e-turkey.com");
  delay (t_setup);
  lcd.setCursor(0, 1);
  lcd.print("OTEL ENRGY SAVER");
  Serial.println("OTEL ENERGY SAVER");
  delay (t_setup);
  lcd.clear();
  //-------------------------------------------------------- LCD bitiş
  pinMode(IN, INPUT);
  pinMode(OUT, INPUT);
  pinMode(pir_header, INPUT);
  pinMode(eeprom_clr, INPUT);
  pinMode(sense, INPUT);
  pinMode(eeprom, OUTPUT);
  pinMode(GND, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(GND, HIGH);
  attachInterrupt(0, electric_sense, RISING);
  {
    read_value = EEPROM.read(143);
    if (read_value == 255) {
      count = 0;
    }
    else
    {
      count = read_value;
    }
    Serial.println(count);
  }
  lcd_off();
}
void toogle_led50() {
  digitalWrite(eeprom, !digitalRead(eeprom));
  delay(50);
}
void electric_sense() {
  Serial.println("ELEKTRİK KESİNTİSİ"); // EEPROM Register
  Serial.println(count);
  //EEPROM.write(address, (count));
  EEPROM.write(address, (count & 0xFF));
}
void electric_off() {
  if (digitalRead(sense) == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    ELEKTRIK    "); //⚡⚡⚡⚡⚡⚡⚡
    lcd.setCursor(0, 1);
    lcd.print("KESINTISI  'I2C'");
    lcd.setRGB(255, 0, 0);
    delay(500);
    lcd.setRGB(0, 0, 0);
    delay(500);
    lcd.setRGB(255, 0, 0);
    delay(500);
    lcd.setRGB(0, 0, 0);
    delay(500);
    lcd.setRGB(255, 0, 0);
    delay(500);
    lcd.setRGB(0, 0, 0);
    delay(500);
    lcd.setRGB(255, 0, 0);
    delay(500);
    lcd.setRGB(0, 0, 0);
    delay(500);
    lcd.clear();
  }
}
void (*softwareReset)( void ) = 0x0000; // Atmega328P için 0x0000
void software_communication() {
  if (Serial.available() > 0) {
    s = Serial.readString();
  }
  if ((s.indexOf("reset") >= 0) || (s.indexOf("restart") >= 0))  //  if ((s.indexOf("reset") >= 0)
  {
    role_off();
    Serial.println("Software Reset");
    delay(250);
    softwareReset();
  }
  if ((s.indexOf("eeprom") >= 0))  //  if ((s.indexOf("reset") >= 0) || (s.indexOf("5555") >= 0))
  {
    s = "end";
    read_value = EEPROM.read(143);
    count = read_value;
    Serial.println(count);
  }
  if ((s.indexOf("clear") >= 0))
  {
    Serial.println("EEPROM Clear");
    delay(100);
    eeprom_clear();
    Serial.println("Restart");
    lcd.clear();
    lcd.setRGB(255, 255, 255);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    YENIDEN");
    lcd.setCursor(0, 1);
    lcd.print("  BASLATILIYOR");
    delay(2500);
    softwareReset();
  }
  if ((s.indexOf("electric") >= 0))  //  if ((s.indexOf("reset") >= 0) || (s.indexOf("5555") >= 0))
  {
    Serial.println("Electric Data EEPROM Write Test");
    EEPROM.write(address, (142 & 0xFF));
    role_off();
    Serial.println("Restart");
    delay(250);
    softwareReset();
  }
  if ((s.indexOf("open") >= 0))  //  if ((s.indexOf("reset") >= 0) || (s.indexOf("5555") >= 0))
  {
    count = 9999;
    role_on();
    lcd_on();
  }
  if ((s.indexOf("close") >= 0))  //  if ((s.indexOf("reset") >= 0) || (s.indexOf("5555") >= 0))
  {
    count = 0;
    role_off();
    lcd_off();
    s = "end";
  }
  if ((s.indexOf("++") >= 0))  //  if ((s.indexOf("reset") >= 0) || (s.indexOf("5555") >= 0))
  {
    count++;
    role_on();
    lcd_on();
    Serial.println(count);
  }
  if ((s.indexOf("--") >= 0))  //  if ((s.indexOf("reset") >= 0) || (s.indexOf("5555") >= 0))
  {
    count--;
    lcd_on();
    if (count == 0)
    {
      count = 0;
      role_off();
      lcd_off();
      s = "end";
      Serial.println("0");
    }
    else if (count <= -1)
    {
      count = 0;
    }
    else
    {
      Serial.println(count);
    }
  }
  if ((s.indexOf("sensor") >= 0))  //  if ((s.indexOf("reset") >= 0) || (s.indexOf("5555") >= 0))
  {
    if (digitalRead(IN) == HIGH) {
      count = -9999;
      Serial.println("IN Sensor");
    }
    if (digitalRead(OUT) == HIGH) {
      count = -9999;
      Serial.println("OUT Sensor");
    }
  }
  if ((s.indexOf("end") >= 0))
  {
  }
}
void eeprom_clear() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.end();
}
void eeprom_reset_and_restart() {
  if (digitalRead(eeprom_clr) == HIGH)
  {
    digitalWrite(eeprom, HIGH);
    Serial.println(F("Hafıza silme işlemi için butona 10 sn. basılı tutunuz. Aksi takdirde Hafıza silinmeyecektir."));
    lcd.clear();
    lcd.setRGB(255, 0, 0);
    lcd.setCursor(0, 0);
    lcd.print("HAFIZAYI  SILMEK");
    lcd.setCursor(0, 1);
    lcd.print("ICIN 10SN.BASINZ");
    delay(10000);
    if (digitalRead(eeprom_clr) == HIGH)
    {
      Serial.println(F("Hafızadaki tüm kayıtlar silinecek ve bu işlem geri alınamayacak."));
      Serial.println(F("Hafıza silme işlemine başlanıyor."));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HAFIZA SILINIYOR");
      lcd.setCursor(0, 1);
      lcd.print("################");
      lcd.setCursor(0, 0);
      delay(2500);
      lcd.print("################");
      for (int i = 0 ; i < 250 ; i++) {
        toogle_led50();
      }
      eeprom_clear();
      Serial.println(F("Hafıza silme işlemi başarıyla tamamlandı.."));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HAFIZA BASARIYLA");
      lcd.setCursor(0, 1);
      lcd.print("    SILINDI");
      digitalWrite(eeprom, HIGH);
      lcd.setRGB(255, 255, 255);
      delay(250);
      digitalWrite(eeprom, LOW);
      lcd.setRGB(255, 0, 0);
      delay(250);
      digitalWrite(eeprom, HIGH);
      lcd.setRGB(255, 255, 255);
      delay(250);
      digitalWrite(eeprom, LOW);
      lcd.setRGB(255, 0, 0);
      delay(250);
      digitalWrite(eeprom, HIGH);
      lcd.setRGB(255, 255, 255);
      delay(250);
      digitalWrite(eeprom, LOW);
      lcd.setRGB(255, 0, 0);
      delay(250);
      digitalWrite(eeprom, HIGH);
      lcd.setRGB(255, 255, 255);
      delay(250);
      digitalWrite(eeprom, LOW);
      lcd.setRGB(255, 0, 0);
      delay(250);
      digitalWrite(eeprom, HIGH);
      lcd.setRGB(255, 255, 255);
      delay(250);
      digitalWrite(eeprom, LOW);
      lcd.setRGB(255, 0, 0);
      lcd.clear();
      read_value = EEPROM.read(143);
      count = read_value;
      Serial.println(count);
      role_off();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    YENIDEN");
      lcd.setCursor(0, 1);
      lcd.print("  BASLATILIYOR");
      delay(2500);
      softwareReset();
    }
    else
    {
      Serial.println(F("Hafıza silme işlemi iptal edildi."));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  HAFIZA SILME");
      lcd.setCursor(0, 1);
      lcd.print("  IPTAL EDILDI");
      delay(2500);
      lcd.clear();
      digitalWrite(eeprom, LOW);
    }
  }
}
void eeprom_read() {
  if (read_value >= 1 && count >= 1)
  {
    role_on();
    lcd_on();
  }
}
void role_on() {
  digitalWrite(relay, HIGH);
  delay(25);
}
void role_off() {
  digitalWrite(relay, LOW);
  delay(25);
}
void sensor_gnd_on_off() {
  statu_pir = digitalRead(pir_header);
  if (statu_pir == HIGH) {
    statu_in = digitalRead(IN);
    if (statu_in == HIGH) {
      digitalWrite(GND, LOW);
      delay(gnd_sensor_time);
      digitalWrite(GND, HIGH);
    }
    else {
    }
    statu_out = digitalRead(OUT);
    if (statu_out == HIGH) {
      digitalWrite(GND, LOW);
      delay(gnd_sensor_time);
      digitalWrite(GND, HIGH);
    }
    else {
    }
  }
  else {
    digitalWrite(GND, HIGH);
  }
}
void io() {
  {
    if (digitalRead(IN) == HIGH) {
      while (digitalRead(IN) == HIGH)delay(t); count++;
      //sensor_gnd_on_off();
      if (count > 0) {
        Serial.println(count);
        role_on();
        lcd_on();
      }
    }
  }
  {
    if (digitalRead(OUT) == HIGH) {
      while (digitalRead(OUT) == HIGH)delay(t); count--;
      //sensor_gnd_on_off();
      //Serial.println(count);
      if (count == 0) {
        for (int sure = 0; sure < zaman ; sure++)
        {
          delay(100);
          Serial.print("TIME     : ");
          Serial.print (zaman / dividing);
          Serial.print ("/");
          Serial.println ((sure / dividing) + 1);
          lcd.setRGB(0, 0, 255);
          lcd.setCursor(0, 0);
          lcd.print("TIME     : ");
          lcd.print (zaman / dividing);
          lcd.print ("/");
          lcd.print ((sure / dividing) + 1);
          if (digitalRead(IN) == HIGH) {
            if (digitalRead(IN) == HIGH) {
              return;
            }
          }
        }
        count = 0;
        role_off();
        lcd_off();
        Serial.println("0");
      }
      else if (count < 0) {
        count = 0;
        role_off();
        lcd_off();
      }
      else
      {
        lcd_on();
        Serial.println(count);
      }
    }
  }
}
void lcd_off() {
  if (count <= 0) {
    lcd.setRGB(255, 0, 0);
    lcd.setCursor(0, 0);
    lcd.print("PERSON   : ");
    lcd.print(count);
    lcd.println("    ");
    lcd.setCursor(0, 1);
    lcd.print("ELECTRIC : OFF");
    delay (10);
  }
}
void lcd_on() {
  if (count > 0) {
    lcd.setRGB(0, 255, 0);
    lcd.setCursor(0, 0);
    lcd.print("PERSON   : ");
    lcd.print(count);
    lcd.println("    ");
    lcd.setCursor(0, 1);
    lcd.print("ELECTRIC : ON ");
    delay (10);
  }
}
void loop () {
  software_communication();
  eeprom_read();
  io();
  eeprom_reset_and_restart();
  electric_off();
}
