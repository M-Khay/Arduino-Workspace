
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "Kush";
const char *password = "";

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	server.send(200, "text/html", "<h1>You are connected</h1> <form action=\"/on1\"> <input type=\"submit\" value=\"led 1 On\" /></form>  <form action=\"/off1\"> <input type=\"submit\" value=\"led 1 Off\" /></form> <form action=\"/on2\"> <input type=\"submit\" value=\"led 2 On\" /></form>  <form action=\"/off2\"> <input type=\"submit\" value=\"led 2 Off\" /></form> ");
}

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);
  pinMode(4,OUTPUT);
  pinMode(2,OUTPUT);
  

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);

  led1on();
  led1off();
  led2on();
  led2off();
  
 
	server.begin();
	Serial.println("HTTP server started");
}

void led1on(){
  server.on("/on1", [](){
digitalWrite(4, HIGH);
server.send(200, "text/html", "<h1>LED1 is ON</h1> <form action=\"/on1\"> <input type=\"submit\" value=\"led 1 On\" /></form>  <form action=\"/off1\"> <input type=\"submit\" value=\"led 1 Off\" /></form> <form action=\"/on2\"> <input type=\"submit\" value=\"led 2 On\" /></form>  <form action=\"/off2\"> <input type=\"submit\" value=\"led 2 Off\" /></form> ");});
}

void led1off(){
  server.on("/off1", [](){
digitalWrite(4, LOW);
server.send(200, "text/html", "<h1>LED1 is Off</h1> <form action=\"/on1\"> <input type=\"submit\" value=\"led 1 On\" /></form>  <form action=\"/off1\"> <input type=\"submit\" value=\"led 1 Off\" /></form> <form action=\"/on2\"> <input type=\"submit\" value=\"led 2 On\" /></form>  <form action=\"/off2\"> <input type=\"submit\" value=\"led 2 Off\" /></form> ");
});

}



void led2on(){
  server.on("/on2", [](){
digitalWrite(2, HIGH);
server.send(200, "text/html", "<h1>LED2 is On</h1> <form action=\"/on1\"> <input type=\"submit\" value=\"led 1 On\" /></form>  <form action=\"/off1\"> <input type=\"submit\" value=\"led 1 Off\" /></form> <form action=\"/on2\"> <input type=\"submit\" value=\"led 2 On\" /></form>  <form action=\"/off2\"> <input type=\"submit\" value=\"led 2 Off\" /></form> ");
});

}


void led2off(){
  server.on("/off2", [](){
digitalWrite(2, LOW);
server.send(200, "text/html", "<h1>LED2 is Off</h1> <form action=\"/on1\"> <input type=\"submit\" value=\"led 1 On\" /></form>  <form action=\"/off1\"> <input type=\"submit\" value=\"led 1 Off\" /></form> <form action=\"/on2\"> <input type=\"submit\" value=\"led 2 On\" /></form>  <form action=\"/off2\"> <input type=\"submit\" value=\"led 2 Off\" /></form> ");
});

}


void loop() {
	server.handleClient();
}
