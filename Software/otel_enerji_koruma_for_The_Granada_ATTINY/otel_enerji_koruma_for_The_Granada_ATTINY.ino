#define relay  2 
#define DOOR   0 
#define BEING 1
int x = 0;
unsigned long old_time_1 = 0, old_time_2 = 0;
unsigned long now_time_1 = 0, now_time_2 = 0;
unsigned long day_time  = 60000; // 86400000 == 24H // 43200000 == 12H // 21600000 == 6H // 3600000 == 1H // 1800000 == 1/2H
unsigned long room_time = 15000;
void setup() {pinMode(BEING, INPUT);pinMode(DOOR, INPUT);pinMode(relay, OUTPUT);digitalWrite(DOOR,HIGH);digitalWrite(BEING,HIGH);delay(2500);}
void loop() {  
// ***************************************** //
if (digitalRead(DOOR) == LOW)
{ 
  if (digitalRead(BEING) == LOW){x = 1;old_time_1 = millis();}
  else if (digitalRead(BEING) == HIGH){now_time_1 = millis();if ((now_time_1 - old_time_1 == day_time) && (digitalRead(BEING) == HIGH) ){x = 0;old_time_1 = millis();}}
  else{ }
}
// ***************************************** //
if (digitalRead(DOOR) == HIGH)
{
  x = 2;
}
// ***************************************** //
if (x == 2 )
{
  if ((digitalRead(DOOR) == LOW) && (digitalRead(BEING) == HIGH)){x = 3;}
}
// ***************************************** //
if (x == 0) {digitalWrite(relay, HIGH);}
if (x == 1) {digitalWrite(relay, LOW);}
//if (x == 2) {}
if (x == 3) {now_time_1 = millis();if (now_time_1 - old_time_1 == (room_time)){
             if ((digitalRead(BEING) == LOW)){old_time_1 = millis();x = 1;}
             if (x !=1){x = 0;}old_time_1 = millis();}}
//if (x == 3) {for (int sure = 0; sure < 10000; sure++){delay(1);if ((digitalRead(KAPI) == HIGH) && (digitalRead(VARLIK) == HIGH)){ x = 4;Serial.println("İçeri Girildi");}}if (x != 4) {x = 0;Serial.println("Röle Kapandı");}}
//if (x == 4) {x = 1;}
// ***************************************** //
}
