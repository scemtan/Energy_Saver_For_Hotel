#define relay  A3 
#define DOOR   4 
#define BEING 5
int x = 0;
unsigned long old_time_1 = 0, old_time_2 = 0;
unsigned long now_time_1 = 0, now_time_2 = 0;
unsigned long day_time  = 86400000; // 86400000 == 24H // 43200000 == 12H // 21600000 == 6H // 3600000 == 1H // 1800000 == 1/2H
unsigned long room_time = 30000;
void setup() {Serial.begin(115200);pinMode(BEING, INPUT);pinMode(DOOR, INPUT);pinMode(relay, OUTPUT);digitalWrite(DOOR,LOW);digitalWrite(BEING,LOW);delay(2500);Serial.println("Sistem Başlatıldı");}
void loop() {  
// ***************************************** //
if (digitalRead(DOOR) == HIGH)
{ 
  if (digitalRead(BEING) == HIGH){x = 1;old_time_1 = millis();Serial.println("Varlık Algılandı, Röle Açıldı");}
  else if (digitalRead(BEING) == LOW){now_time_1 = millis();if ((now_time_1 - old_time_1 == day_time) && (digitalRead(BEING) == LOW) ){x = 0;old_time_1 = millis();Serial.println("Röle Kapandı");}}
  else{ }
}
// ***************************************** //
if (digitalRead(DOOR) == LOW)
{
  Serial.println("Kapı Açıldı");
  x = 2;
}
// ***************************************** //
if (x == 2 )
{
  if ((digitalRead(DOOR) == HIGH) && (digitalRead(BEING) == LOW)){Serial.println("Kapı Kapandı");x = 3;}
}
// ***************************************** //
if (x == 0) {digitalWrite(relay, LOW);/*Serial.println("Röle Kapalı");*/}
if (x == 1) {digitalWrite(relay, HIGH);/*Serial.println("Röle Açık");*/}
//if (x == 2) {}
if (x == 3) {now_time_1 = millis();if (now_time_1 - old_time_1 == (room_time)){
             if ((digitalRead(BEING) == HIGH)){old_time_1 = millis();x = 1;}
             if (x !=1){x = 0;Serial.println("Varlık Algılanmadı, Röle Kapandı");}old_time_1 = millis();}}
//if (x == 3) {for (int sure = 0; sure < 10000; sure++){delay(1);if ((digitalRead(KAPI) == HIGH) && (digitalRead(VARLIK) == HIGH)){ x = 4;Serial.println("İçeri Girildi");}}if (x != 4) {x = 0;Serial.println("Röle Kapandı");}}
//if (x == 4) {x = 1;}
// ***************************************** //
}
