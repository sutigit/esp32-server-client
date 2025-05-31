#include <WiFi.h>
#include <WebServer.h>

WebServer server(80); // Port 80

const char* ssid = "sutilan";
const char* password = "leppakerttu";

const int ledPins[] = {
  13,14,15,18,19,25,26,27,32,33 // safe led pins for output
};
const int numPins = sizeof(ledPins) / sizeof(ledPins[0]);

void blink() {
  Serial.println("blink");
}

void setup(){
    Serial.begin(460800);
    delay(1000);

    /**
     * The STA mode is used to connect the ESP32 to a Wi-Fi network, 
     * provided by an Access Point.
     */
    WiFi.mode(WIFI_STA); 
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
      Serial.println(ledPins[i]);
      pinMode(ledPins[i], OUTPUT);
      delay(500);
    }
    
    Serial.println("\nLED pins configured succesfully");

    server.on("/blink", blink);

    server.begin();
    Serial.println("\nHTTP server started");
}

void loop(){
  server.handleClient();
}
