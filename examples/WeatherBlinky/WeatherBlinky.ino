#include "Badge.h"
#include "Image.h"
#include "WifiInfo.h"
#include <PubSubClient.h>

#define mqtt_server "127.0.0.1"
#define mqtt_port 1883

//#define mqtt_app "InternetThing"
#define mqtt_user "testSub"
#define mqtt_password "thing1pw"

Badge badge;
Image image;

WiFiClient espClient;
PubSubClient client(espClient);

static uint32_t palette[] = {Image::RED, Image::BLACK, Image::WHITE, Image::GREEN};
static int red_pixels[LED_ROWS][LED_COLS] = {
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0}};
static int white_pixels[LED_ROWS][LED_COLS] = {
   {2,2,2,2,2,2,2,2},
   {2,2,2,2,2,2,2,2},
   {2,2,2,2,2,2,2,2},
   {2,2,2,2,2,2,2,2},
   {2,2,2,2,2,2,2,2},
   {2,2,2,2,2,2,2,2},
   {2,2,2,2,2,2,2,2},
   {2,2,2,2,2,2,2,2}};
static int green_pixels[LED_ROWS][LED_COLS] = {
   {3,3,3,3,3,3,3,3},
   {3,3,3,3,3,3,3,3},
   {3,3,3,3,3,3,3,3},
   {3,3,3,3,3,3,3,3},
   {3,3,3,3,3,3,3,3},
   {3,3,3,3,3,3,3,3},
   {3,3,3,3,3,3,3,3},
   {3,3,3,3,3,3,3,3}};

// Process an incoming message that we have subscribed to.
static void mqtt_callback(const char * const topic_raw, const byte * const payload, unsigned int len) {
  String topic = topic_raw;

  Serial.print("MQTT topic '");
  Serial.print(topic);
  Serial.print("' length ");
  Serial.println(len);

  if (topic == "weather") {
    for (int i = 0; i < len; i++) {
      char receivedChar = (char)payload[i];
      Serial.print(receivedChar);
    }
    image.setimage(palette, white_pixels);
    image.paint(badge.matrix);
    badge.matrix.show();
  }
}

void setup() {
  badge.begin();
  badge.matrix.clear();
  badge.matrix.show();

  WiFi.persistent(false);
  WiFi.begin(wifi_ssid, wifi_pwd);

  Serial.print("joining network: ");
  Serial.println(wifi_ssid);

  while (WiFi.status() != WL_CONNECTED) {
    image.setimage(palette, red_pixels);
    image.paint(badge.matrix);
    badge.matrix.show();
    delay(30);
  }
  Serial.print("successfully joined network!");
  image.setimage(palette, green_pixels);
  image.paint(badge.matrix);
  badge.matrix.show();
  
  // let the user know that we have an IP address
  String s = WiFi.localIP().toString();
  Serial.print("local IP: ");
  Serial.println(s);

  // connect to the mqtt server
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
   Serial.print("Attempting MQTT connection...");
   // Attempt to connect
   if (client.connect("ESP8266 Client")){//, mqtt_user, mqtt_password)) {
    Serial.println("connected");
    // ... and subscribe to topic
    client.subscribe("weather/#");
   } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
   }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
