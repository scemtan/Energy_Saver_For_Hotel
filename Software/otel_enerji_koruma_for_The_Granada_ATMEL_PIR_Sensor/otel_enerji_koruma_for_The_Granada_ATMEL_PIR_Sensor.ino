#define relay  17  //  8  --  17 - A3
#define DOOR   4   //  9
#define BEING  5   // 10
int x = 0, y = 0;
unsigned long old_time_1 = 0, old_time_2 = 0;
unsigned long now_time_1 = 0, now_time_2 = 0;
unsigned long day_time  = 86400000; // 86400000 == 24H // 43200000 == 12H // 21600000 == 6H // 3600000 == 1H // 1800000 == 1/2H
unsigned long room_time = 15000;
void setup() {Serial.begin(115200);pinMode(BEING, INPUT);pinMode(DOOR, INPUT);pinMode(relay, OUTPUT);digitalWrite(DOOR,LOW);digitalWrite(BEING,HIGH);delay(5000);Serial.println("Sistem Başlatıldı");}
void loop() {  
// ***************************************** //
if (digitalRead(DOOR) == HIGH)
{ 
  if (x == 0 && digitalRead(BEING) == LOW){x = 1;old_time_1 = millis();Serial.println("Varlık Algılandı, Röle Açıldı");}
  else if ((y == 1) && (x == 1 && digitalRead(BEING) == HIGH)) {now_time_1 = millis();if ((now_time_1 - old_time_1 == day_time) && (digitalRead(BEING) == HIGH) ){x = 0;old_time_1 = millis();Serial.println("Röle Kapandı");}}
  else {}
}
// ***************************************** //
if (digitalRead(DOOR) == LOW){Serial.println("Kapı Açıldı");old_time_1 = millis();x = 2;}
// ***************************************** //
if (x == 2 && digitalRead(DOOR) == HIGH)
{
for (int sure = 0; sure < 1; sure++){delay(1); Serial.println("Kapı Kapandı");}
x = 3;
}
if (x == 3 && digitalRead(BEING) == LOW){old_time_1 = millis();Serial.println("Varlık Algılandı");x = 1;}
if (x == 3 && digitalRead(BEING) != LOW){now_time_1 = millis();if ((now_time_1 - old_time_1 == room_time) && (digitalRead(BEING) == HIGH) ){x = 0;old_time_1 = millis();Serial.println("Varlık Algılanmadı, Röle Kapandı");}}
// ***************************************** //
if (x == 0) {digitalWrite(relay, HIGH);}
// ***************************************** //
if (x == 1) {digitalWrite(relay, LOW);}
// ***************************************** //
if (digitalRead(BEING) == LOW){old_time_1 = millis(); y = 1;}
// ***************************************** //
}
