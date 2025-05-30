#include <WiFi.h>
#include <WebServer.h>

WebServer server(80); // Port 80

const char* ssid = "sutilan";
const char* password = "leppakerttu";

const int ledPins[11] = {14,25,26,27,32,33,34,35,37,38,39};
const int numPins = sizeof(ledPins) / sizeof(ledPins[0]);

void blink() {
  Serial.println("blink");
}

void setup(){
    Serial.begin(460800);
    delay(1000);

    WiFi.mode(WIFI_STA); // The STA mode is used to connect the ESP32 to a Wi-Fi network, provided by an Access Point.
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    Serial.println("\nInitializing LED pins");
    for (int i = 0; i < numPins; i++) {
      pinMode(ledPins[i], OUTPUT);
    }

    server.on("/", blink);

    server.begin();
    Serial.println("\nHTTP server started");
}

void loop(){
  server.handleClient();
}
