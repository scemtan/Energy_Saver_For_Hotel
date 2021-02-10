#define relay  1 
#define KAPI   2 
#define VARLIK 0
int x = 0;
unsigned long old_time_1 = 0, old_time_2 = 0;
unsigned long now_time_1 = 0, now_time_2 = 0;
unsigned long day_time  = 60000; // 86400000 == 24H // 43200000 == 12H // 21600000 == 6H // 3600000 == 1H
unsigned long room_time = 15000;
void setup() {pinMode(VARLIK, INPUT);pinMode(KAPI, INPUT);pinMode(relay, OUTPUT);digitalWrite(KAPI,LOW);digitalWrite(VARLIK,LOW);}
void loop() {  
// ***************************************** //
if (digitalRead(KAPI) == HIGH)
{ 
  if (digitalRead(VARLIK) == HIGH){x = 1;old_time_1 = millis();}
  else if (digitalRead(VARLIK) == LOW){now_time_1 = millis();if ((now_time_1 - old_time_1 == day_time) && (digitalRead(VARLIK) == LOW) ){x = 0;old_time_1 = millis();}}
  else{ }
}
// ***************************************** //
else if (digitalRead(KAPI) == LOW)
{
  x = 2;
}
// ***************************************** //
else
{
}
// ***************************************** //
if (x == 0) {digitalWrite(relay, LOW);/*Serial.println("Röle Kapalı");*/}
if (x == 1) {digitalWrite(relay, HIGH);/*Serial.println("Röle Açık");*/}
if (x == 2) {if ((digitalRead(KAPI) == HIGH) && (digitalRead(VARLIK) == LOW)){x = 3;}}
if (x == 3) {now_time_1 = millis();if (now_time_1 - old_time_1 == (room_time*2)){
             if ((digitalRead(VARLIK) == HIGH)){old_time_1 = millis();x = 1;}
             else if (x !=1){x = 0;}old_time_1 = millis();}}
// ***************************************** //
}
