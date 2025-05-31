#define WIFI_DEBUG 1

#include <WiFi.h>
#include <WebServer.h>

WebServer server(80); // Port 80

const char *ssid = "sutilan";
const char *password = "leppakerttu";

const int ledPins[] = {
    13, 14, 15, 18, 19, 25, 26, 27, 32, 33 // safe led pins for output
};
const int numPins = sizeof(ledPins) / sizeof(ledPins[0]);

void handleRoot() {
  Serial.println("Hello from esp32");
  server.send(200);
}

void handleBlink()
{
  Serial.println("received something...");
  if (server.hasArg("p"))
  {
    int pin = server.arg("p").toInt();
    Serial.println(pin);
    server.send(200);
  }
  else
  {
    server.send(400);
  }
}

void handleNotFound()
{
  Serial.println("Server not found");
}

bool connectToWiFI()
{
  /**
   * The STA mode is used to connect the ESP32 to a Wi-Fi network,
   * provided by an Access Point.
   */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  long waitedTime = millis();

  #if WIFI_DEBUG
    Serial.println("\nConnecting");
  #endif

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);

    if (millis() - waitedTime >= 10000) {
      #if WIFI_DEBUG
            Serial.println("WIFI connection timeout");
      #endif

      return false;
    }
  }

  #if WIFI_DEBUG
    Serial.printf("\nWiFi Connected to: %s\n", ssid);
  #endif

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  return true;
}

void setup()
{
  Serial.begin(460800);
  delay(1000);

  if (connectToWiFI()) {
    Serial.println("\nInitializing LED pins");
    for (int i = 0; i < numPins; i++)
    {
      Serial.println(ledPins[i]);
      pinMode(ledPins[i], OUTPUT);
      digitalWrite(ledPins[i], LOW);
      delay(200);
    }
  
    Serial.println("\nLED pins configured succesfully");
    
    server.on("/", handleRoot);
    server.on("/blink", handleBlink);
    server.onNotFound(handleNotFound);
  
    server.begin();
    Serial.println("\nHTTP server started");
  }
}

void loop()
{
  server.handleClient();
}
