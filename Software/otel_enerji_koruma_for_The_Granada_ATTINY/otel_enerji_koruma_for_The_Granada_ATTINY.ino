#define relay  4 
#define DOOR   0 
#define BEING 2
int x = 0;
unsigned long old_time_1 = 0, old_time_2 = 0;
unsigned long now_time_1 = 0, now_time_2 = 0;
unsigned long day_time  = 60000; // 86400000 == 24H // 43200000 == 12H // 21600000 == 6H // 3600000 == 1H // 1800000 == 1/2H
unsigned long room_time = 30000;
void setup() {pinMode(BEING, INPUT);pinMode(DOOR, INPUT);pinMode(relay, OUTPUT);digitalWrite(DOOR,LOW);digitalWrite(BEING,LOW);delay(2500);}
void loop() {  
// ***************************************** //
if (digitalRead(DOOR) == HIGH)
{ 
  if (digitalRead(BEING) == HIGH){x = 1;old_time_1 = millis();}
  else if (digitalRead(BEING) == LOW){now_time_1 = millis();if ((now_time_1 - old_time_1 == day_time) && (digitalRead(BEING) == LOW) ){x = 0;old_time_1 = millis();}}
  else{ }
}
// ***************************************** //
if (digitalRead(DOOR) == LOW)
{
  x = 2;
}
// ***************************************** //
if (x == 2 )
{
  if ((digitalRead(DOOR) == HIGH) && (digitalRead(BEING) == LOW)){x = 3;}
}
// ***************************************** //
if (x == 0) {digitalWrite(relay, LOW);}
if (x == 1) {digitalWrite(relay, HIGH);}
//if (x == 2) {}
if (x == 3) {now_time_1 = millis();if (now_time_1 - old_time_1 == (room_time)){
             if ((digitalRead(BEING) == HIGH)){old_time_1 = millis();x = 1;}
             if (x !=1){x = 0;}old_time_1 = millis();}}
// ***************************************** //
}
