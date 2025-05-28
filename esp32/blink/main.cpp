#include <WiFi.h>
#include <WebServer.h>

const char* ssid = ""; // wifi name
const char* password = ""; // wifi password

WebServer server(80);

const int ledPin = 2;  // onboard LED (usually GPIO 2)

void handleBlink() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);

  server.send(200, "text/plain", "LED blinked");
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  server.on("/blink", handleBlink);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}
