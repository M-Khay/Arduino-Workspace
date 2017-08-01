
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "kush's iPhone";
const char* password = "notforyou";

const char* APssid = "kush";
const char* APpassword = "";


ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Welcome.Connection Successful");
}

void setup(void){
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);
  
  WiFi.softAP(APssid, APpassword);

  Serial.print(APssid);
  Serial.print(" Server ip: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);  
  server.onNotFound(handleNotFound);  
  server.begin();
  Serial.println("HTTP server started");

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    yield();
  }

  Serial.print("Connected to: ");
  Serial.print(WiFi.SSID());
  Serial.print(", IP address: ");
  Serial.println(WiFi.localIP());
}

 
void handleNotFound() {
  
  WiFiClient client;
  Serial.print("Requesting uri: ");
  String requestUri = server.uri();
  requestUri.remove(0,1);
  int pos = requestUri.indexOf('/');
  String hostname = requestUri.substring(0,pos);
  const char* host = hostname.c_str();
  requestUri.remove(0,pos);
  
  
  Serial.println(requestUri);
  while (!client.connect(host, 80)) {
    Serial.println("WIFI connection not found. Retrying again.");
  }
  client.print(String("GET ") + requestUri);
  
  client.print(String(" HTTP/1.1\r\n") +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");          
  while(!client.available()){
      yield();
  }

  String response = "";
  while(client.available()){
    response = client.readStringUntil('\r');
  }
  response.replace("http", "WHAT-IS-THIS");
    response.replace("HTTP", "WHAT-IS-THIS");
  
  
  Serial.println("RESPONSE FROM WEB SERVER IS : ");
  Serial.println(response);
  server.send(200, "text/html", response);

  client.stop();
}

void loop(void){
  server.handleClient();
}
