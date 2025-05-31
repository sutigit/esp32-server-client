#define WIFI_DEBUG 1

#include <WiFi.h>
#include <WiFiUdp.h>
// #include <WebServer.h>

// WebServer server(80); // Port 80
WiFiUDP udp;
const unsigned int localUdpPort = 4210; // Port ESP32 listens on
char incomingPacket[255]; // buffer for incoming packets

// void handleRoot() {
//   Serial.println("Root hit");
//   server.send(200);
// }

// void handleBlink()
// {
//   if (server.hasArg("p"))
//   {
//     int pin = server.arg("p").toInt();
//     Serial.println(pin);
//     server.send(200);
//   }
//   else
//   {
//     server.send(400);
//   }
// }

void handleNotFound()
{
  Serial.println("Server not found");
}

bool connectToWiFI()
{
  const char *ssid = "sutilan";
  const char *password = "leppakerttu";

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

void initLedPins() {

    const int ledPins[] = {
        13, 14, 15, 18, 19, 25, 26, 27, 32, 33 // safe led pins for output
    };
    const int numPins = sizeof(ledPins) / sizeof(ledPins[0]);

    Serial.println("\nInitializing LED pins");
    for (int i = 0; i < numPins; i++)
    {
      Serial.println(ledPins[i]);
      pinMode(ledPins[i], OUTPUT);
      digitalWrite(ledPins[i], LOW);
      delay(200);
    }
  
    Serial.println("\nLED pins configured succesfully");
}

// void initWebServer() {
//     server.on("/", handleRoot);
//     server.on("/blink", handleBlink);
//     server.onNotFound(handleNotFound);
  
//     server.begin();
//     Serial.println("\nHTTP server started");
// }

void initUDP() {
  udp.begin(localUdpPort);
  Serial.printf("UDP listening on port %d\n", localUdpPort);
}

void handleUDP() {
  int packetSize = udp.parsePacket();
    if (packetSize) {
      // Read packet
      int len = udp.read(incomingPacket, 255);
      if (len > 0) {
        incomingPacket[len] = 0; // Null-terminate
      }

      Serial.printf("UDP packet received: '%s'\n", incomingPacket);

      int pin = atoi(incomingPacket);
      digitalWrite(pin, HIGH);
      delay(200);
    }
}

void setup()
{
  Serial.begin(460800);
  delay(1000);

  if (connectToWiFI()) {
    
    initLedPins();
    // initWebServer();
    initUDP();

    delay(500);
  }
}

void loop()
{
  // server.handleClient();
  handleUDP();
}
