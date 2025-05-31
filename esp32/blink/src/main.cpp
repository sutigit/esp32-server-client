#define WIFI_DEBUG 1
#define NUM_LEDS 10

#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;
const unsigned int localUdpPort = 4210; // Port ESP32 listens on
char incomingPacket[255];               // buffer for incoming packets

const int ledPins[NUM_LEDS] = {13, 14, 15, 18, 19, 25, 26, 27, 32, 33}; // safe led pins for output
bool ledOn[NUM_LEDS] = {false};
unsigned long ledOffTime[NUM_LEDS] = {0};

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

    if (millis() - waitedTime >= 10000)
    {
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

void initLedPins()
{
  Serial.println("\nInitializing LED pins");
  for (int i = 0; i < NUM_LEDS; i++)
  {
    Serial.println(ledPins[i]);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
    delay(200);
  }

  Serial.println("\nLED pins configured succesfully");
}

void initUDP()
{
  udp.begin(localUdpPort);
  Serial.printf("UDP listening on port %d\n", localUdpPort);
}

void handlePinOn()
{
  int packetSize = udp.parsePacket();

  if (packetSize)
  {
    // Read packet
    int len = udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0; // Null-terminate
    }

    Serial.printf("UDP packet received: '%s'\n", incomingPacket);

    int pin = atoi(incomingPacket);

    // This pattern is for handling asynchronosity in lighting the LEDs
    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (ledPins[i] == pin)
      {
        digitalWrite(pin, HIGH);
        ledOn[i] = true;
        ledOffTime[i] = millis() + 100; // 200 ms later turn off
        break;
      }
    }
  }
}

void handlePinOff()
{
  // This pattern is for handling asynchronosity in lighting the LEDs
  unsigned long now = millis();
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (ledOn[i] && now > ledOffTime[i])
    {
      digitalWrite(ledPins[i], LOW);
      ledOn[i] = false;
    }
  }
}

void setup()
{
  Serial.begin(460800);
  delay(1000);

  if (connectToWiFI())
  {

    initLedPins();
    initUDP();

    delay(500);
  }
}

void loop()
{
  handlePinOn();
  handlePinOff();
}
