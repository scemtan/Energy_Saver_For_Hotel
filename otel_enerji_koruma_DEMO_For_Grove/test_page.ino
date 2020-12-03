/*
void io() {
  {
  if (digitalRead(IN) == HIGH) {
    while(digitalRead(IN) == HIGH)delay(t);count++;
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
    while(digitalRead(OUT) == HIGH)delay(t);count--;
    //sensor_gnd_on_off();
    lcd_on();
    Serial.println(count);
    if (count == 0) {
      role_off();
      lcd_off();
    } 
    if (count < 0) {
      count = 0;
    }
  }
  }
}
void lcd_off(){
    lcd.setRGB(255, 0, 0);
    lcd.setCursor(0, 0);
    lcd.print("PERSON   : ");
    lcd.print(count);
    lcd.println("    ");
    lcd.setCursor(0, 1);
    lcd.print("ELECTRIC : OFF");
    delay (10);
}
void lcd_on(){
    lcd.setRGB(0, 255, 0);
    lcd.setCursor(0, 0);
    lcd.print("PERSON   : ");
    lcd.print(count);
    lcd.println("    ");
    lcd.setCursor(0, 1);
    lcd.print("ELECTRIC : ON ");
    delay (10);
}
*/

/*
void io() {
  if (digitalRead(IN) == HIGH) {
    while(digitalRead(IN) == HIGH)delay(t);count++;
    //sensor_gnd_on_off();
    if (count > 0) {
      Serial.println(count);
      role_on();
    }
  }
  if (digitalRead(OUT) == HIGH) {
    while(digitalRead(OUT) == HIGH)delay(t);count--;
    //sensor_gnd_on_off();
    if (count == 0) {
      Serial.println(count);
      
      //
      //if (millis() - xyz > zaman)
      //{       
        //role_off();
        //xyz = millis();
      //}
      //
      
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
      Serial.println(count);
      role_off();
    } else if (count < 0) {
      count = 0;
    } else {
      Serial.println(count);
    }
  }
  lcd_info();
}
void lcd_info() {
  if (count == 0) {
    lcd.setRGB(255, 0, 0);
    lcd.setCursor(0, 0);
    lcd.print("PERSON   : ");
    lcd.print(count);
    lcd.println("    ");
    lcd.setCursor(0, 1);
    lcd.print("ELECTRIC : OFF");
    delay (10);
  }
  else if (count >= 1) {
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
*/
