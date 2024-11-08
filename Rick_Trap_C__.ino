#include <WiFi.h>
#include <ESP32WebServer.h>

String copiedSSID = "";

ESP32WebServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);

  Serial.println("Skanowanie dostępnych sieci Wi-Fi...");
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("Nie znaleziono żadnych sieci.");
  } else {
    Serial.println("Znaleziono sieci:");
    for (int i = 0; i < n; i++) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.println("dBm)");

      if (i == 0) {
        copiedSSID = WiFi.SSID(i);
        Serial.print("Skopiowano SSID: ");
        Serial.println(copiedSSID);
      }
    }

    if (copiedSSID != "") {
      Serial.println("Tworzenie własnej sieci Wi-Fi z SSID skopiowanej sieci...");
      WiFi.softAP(copiedSSID.c_str(), "");
      Serial.print("Sieć Wi-Fi stworzona: ");
      Serial.println(copiedSSID);
      Serial.print("Adres IP AP: ");
      Serial.println(WiFi.softAPIP());
    }
  }

  server.on("/", HTTP_GET, []() {
    String page = "<html><head>";
    page += "<meta http-equiv='refresh' content='0; url=https://www.youtube.com/watch?v=dQw4w9WgXcQ'>";
    page += "</head><body>";
    page += "<p>Ładowanie Rickrolla...</p>";
    page += "</body></html>";
    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Serwer działa...");
}

void loop() {
  server.handleClient();
}
