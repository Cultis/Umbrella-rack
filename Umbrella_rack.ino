#include <ESP8266WiFi.h>

// Wifi access point
#define WLAN_SSID   "XXXX"                          
#define WLAN_PASS   "XXXX"                           

// Weather Underground setup
const char server[] = "api.wunderground.com";
const String myKey = "a914fd0efd3984de";
const String myFeatures = "conditions";
const String myCountry = "Finland";      
const String myCity = "Helsinki";     

String responseString = ""; 
int APIrain;
boolean rainFound = false;         

void setup()
{

// Set datarate
  Serial.begin(115200);

// Define LED pins as an output 
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT); 

// Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());

  String html_cmd1 = "GET /api/" + myKey + "/" + myFeatures + "/q/" + myCountry + "/" + myCity + ".json HTTP/1.1";
  String html_cmd2 = "Host: " + (String)server;
  String html_cmd3 = "Connection: close";

  Serial.println("Sending commands:");
  Serial.println(" " + html_cmd1);
  Serial.println(" " + html_cmd2);
  Serial.println(" " + html_cmd3);
  Serial.println();
}

//Update values from .JSON
void checkData()
{
  int i;
  if(responseString.startsWith (F("precip_today_metric")) & !rainFound)
  {
    char rain2[5];
    rainFound = true;
    for (i=20; i < responseString.length ()-1; ++i)
    {
      if(responseString[i] == ',')
        break;
      rain2[i-20] = responseString[i];
    }
    APIrain = atoi(rain2);
  }
  responseString = "";
}

void loop() 
{
  
// LED triggers based on API data
  if (APIrain < 0.3)                                               // LEDs off when rain < 0.3mm
  {
    digitalWrite(16, LOW);            
    digitalWrite(5, LOW); 
    digitalWrite(4, LOW);
  }
  if (APIrain >= 0.3 && APIrain <= 0.9)                            // 1 LED on when rain >= 0.3mm and <= 0.9mm                          
  {
    digitalWrite(16, HIGH);
    digitalWrite(5, LOW); 
    digitalWrite(4, LOW);
  }
  
  if (APIrain > 0.9 && APIrain <= 4.4)                             // 2 LEDs on when rain > 0.9mm and <= 4.4mm
  {
    digitalWrite(16, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW); 
  }
    
  if (APIrain > 4.4)                                               // 3 LEDs on when rain over 4.4mm
  {
    digitalWrite(16, HIGH);            
    digitalWrite(5, HIGH); 
    digitalWrite(4, HIGH);
  }
  delay(10*60*1000);                                               // 10 minute delay
}
