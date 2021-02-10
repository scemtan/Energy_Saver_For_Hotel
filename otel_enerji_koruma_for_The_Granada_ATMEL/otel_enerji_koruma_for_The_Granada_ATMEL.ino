#define relay  A3 
#define KAPI   4 
#define VARLIK 5
int x = 0;
unsigned long old_time_1 = 0, old_time_2 = 0;
unsigned long now_time_1 = 0, now_time_2 = 0;
unsigned long day_time  = 60000; // 86400000 == 24H // 43200000 == 12H // 21600000 == 6H // 3600000 == 1H
unsigned long room_time = 15000;
void setup() {Serial.begin(115200);pinMode(VARLIK, INPUT);pinMode(KAPI, INPUT);pinMode(relay, OUTPUT);digitalWrite(KAPI,LOW);digitalWrite(VARLIK,LOW);}
void loop() {  
// ***************************************** //
if (digitalRead(KAPI) == HIGH)
{ 
  if (digitalRead(VARLIK) == HIGH){x = 1;old_time_1 = millis();Serial.println("İçeri Girildi");}
  else if (digitalRead(VARLIK) == LOW){now_time_1 = millis();if ((now_time_1 - old_time_1 == day_time) && (digitalRead(VARLIK) == LOW) ){x = 0;old_time_1 = millis();Serial.println("Röle Kapandı");}}
  else{ }
}
// ***************************************** //
else if (digitalRead(KAPI) == LOW)
{
  Serial.println("Kapı Açıldı");
  x = 2;
}
// ***************************************** //
else
{
}
// ***************************************** //
if (x == 0) {digitalWrite(relay, LOW);/*Serial.println("Röle Kapalı");*/}
if (x == 1) {digitalWrite(relay, HIGH);/*Serial.println("Röle Açık");*/}
if (x == 2) {if ((digitalRead(KAPI) == HIGH) && (digitalRead(VARLIK) == LOW)){x = 3;Serial.println("Kapı Kapandı Ve Kimse Yok Röle Kapanacak");}}
if (x == 3) {now_time_1 = millis();if (now_time_1 - old_time_1 == (room_time*2)){
             if ((digitalRead(VARLIK) == HIGH)){old_time_1 = millis();x = 1;}
             else if (x !=1){x = 0;Serial.println("Röle Kapandı");}old_time_1 = millis();}}
//if (x == 3) {for (int sure = 0; sure < 10000; sure++){delay(1);if ((digitalRead(KAPI) == HIGH) && (digitalRead(VARLIK) == HIGH)){ x = 4;Serial.println("İçeri Girildi");}}if (x != 4) {x = 0;Serial.println("Röle Kapandı");}}
//if (x == 4) {x = 1;}
// ***************************************** //
}
