#include <UIPEthernet.h>
String z = "0", serial = "00:01:02:03:04:05";
char local_ip = "0";
int temp = 0, e_status = 0, power_cut = 0, person = 0;
EthernetClient client;
static byte mac[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
void setup() {
  Serial.begin(115200);
  Ethernet.begin(mac);
  //for (byte i = 0; i < 6; ++i) {Serial.print(mac[i], HEX);if (i < 5)Serial.print(':');}
}
void loop() {
  if (Serial.available() >= 0) {z = Serial.readString();}
  if (person = z.toInt()) {if(person > 0 ){e_status = 1;}else if(person < 0 ){person = 0;e_status = 0;}Serial.println(person);internet ();}
}
void internet () {
  //char server[] = "energy-saver.3e-turkey.com";
  //if (Ethernet.begin(mac) == 0) {Serial.println("Failed to configure Ethernet using DHCP");while (1);}
  if (client.connect("energy-saver.3e-turkey.com", 80)) {
    Serial.println("Connected to server");
    client.println("GET /updater.php?v=8VdiCJMubyLAY37sT5Kbvfq8nLlQgznb&serial=" + serial + "&person=" + person + "&e_status=" + e_status + "&power_cut=" + power_cut + "&local_ip=" + local_ip +" HTTP/1.1");
    client.println("Host: energy-saver.3e-turkey.com");
    client.println();
  } else {Serial.println("Connection to server failed");}
  while (client.connected()) {if (client.available()) {char c = client.read();Serial.print(c);}}z = " ";
}
