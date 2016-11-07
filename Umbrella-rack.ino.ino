// Include libraries
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>


const char* ssid     = "XXXX";  // Wifi name.
const char* password = "XXXX"; // Wifi password.

const char* host     = "api.wunderground.com"; // Wunderground domain.

//String path          = "/api/a914fd0efd3984de/conditions/q/autoip.json";  // Conditions for current rain.
String path          = "/api/<API_KEY>/forecast/q/autoip.json";  // Forecast for propability of rain.


void setup() { 
   
// Setting pins as outputs
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT);
  pinMode(16, OUTPUT);
      
  Serial.begin(115200);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

// Connect  to Wifi
  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  delay(10);  
  Serial.println("IP address: " + WiFi.localIP());
}

void loop() {
  // Connect to host  
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");

  delay(500); // Wait for server to respond.
  
  // Read response
  String section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line); // Print line
    // Parse HTML body.
    if (section=="header") { 
      Serial.print(".");
      if (line=="\n") { // Skips the empty space at the beginning.
        section="json";
      }
    }
    else if (section=="json") { 
      section="ignore";
      String result = line.substring(1);

      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      //Serial.print(size); // Print size
      result.toCharArray(json, size);
      //Serial.print(result); // Print results.
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);;
      
      int pop = json_parsed["pop"]; //Store pop value.
      
      // Print probability of precipitation value
      Serial.print("Probability of precipitation: ");
      Serial.print(pop);
      Serial.print('\n');
      
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed. 3min delay before next try.");
        delay(3*60*1000); // 3min delay.
        return;
      }

      // LED triggers
      if (pop >= 10 && pop < 30) {  // If pop >= 10 and  pop < 30, trigger 1 LED.
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(16, LOW);
      }
      if (pop >= 30 && pop <= 60) { // If pop >= 30 and  pop <= 60, trigger 2 LED.
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(16, LOW);
      }  
      if (pop > 60) { // If pop >60, trigger 3 LED.
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(16, HIGH);
      }
    }
  }
  Serial.print("3min delay before next reading.");
  delay(3*60*1000); // 3min delay
}
