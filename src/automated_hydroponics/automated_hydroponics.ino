#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Ultrasonic.h>
#include <Wire.h>

// Wi-Fi credentials
const char* ssid = "YourSSID";
const char* password = "YourPassword";

// Set static IP for ESP32
IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Pin Assignments
#define PUMP_PIN 26
#define SOLENOID_PIN 25
#define MIST_GENERATOR_PIN 33
#define FERTILIZER_PUMP_PIN 32
#define DHT_PIN 27
#define PH_SENSOR_PIN 34
#define ULTRASONIC_TRIGGER_PIN 5
#define ULTRASONIC_ECHO_PIN 18
#define LIGHT_SENSOR_PIN 35
#define LIGHT_ON_PIN 17


// DHT sensor type
DHT dht(DHT_PIN, DHT11);

// LCD setup
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Ultrasonic sensor setup
Ultrasonic ultrasonic(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN);

// Web server instance
WebServer server(80);

// Store sensor values
float humidity, temperature, pH, waterLevel, lightIntensity;

// Function declarations
void setupWiFi();
void handleRoot();
void handleManualControl();
void handlePumpToggle();
void handleSolenoidToggle();
void handleLightToggle();
void handleMistToggle();
void displayLCD();
void irrigationControl();
void monitorSensors();
void handleFertilizerPumpToggle();

// HTML web interface
String manualControlPage();
String sensorDataPage();

void setup() {
  // Serial monitor setup
  Serial.begin(115200);

  // Initialize sensors and LCD
  dht.begin();
  lcd.init();
  lcd.backlight();

  // Initialize output pins
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(SOLENOID_PIN, OUTPUT);
  pinMode(MIST_GENERATOR_PIN, OUTPUT);
  pinMode(FERTILIZER_PUMP_PIN, OUTPUT);
  pinMode(LIGHT_ON_PIN,OUTPUT);
  
  // Setup Wi-Fi
  setupWiFi();

  // Define web server routes
  server.on("/", handleRoot);
  server.on("/manual", handleManualControl);
  server.on("/toggle-pump", handlePumpToggle);
  server.on("/toggle-solenoid", handleSolenoidToggle);
  server.on("/toggle-mist", handleMistToggle);
  server.on("/toggle-light", handleLightToggle);
  server.on("/toggle-fertili", handleFertilizerPumpToggle);



  // Start web server
  server.begin();

  // Initialize state
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(SOLENOID_PIN, LOW);
  digitalWrite(MIST_GENERATOR_PIN, LOW);
  digitalWrite(LIGHT_ON_PIN, LOW);
  digitalWrite(FERTILIZER_PUMP_PIN, LOW);  

}

void loop() {
  // Handle web server
  server.handleClient();

  // Monitor and control automatic operations
  monitorSensors();
  irrigationControl();

  // Update the LCD display
  displayLCD();
  delay(5000);
}

// Connect to Wi-Fi with static IP
void setupWiFi() {
  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
}

// Root web page (sensor data and graphs)
void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Hydroponics System</title>
      <style>
        body { font-family: Arial; text-align: center; }
        h1 { color: #4CAF50; }
        .gauge { width: 200px; height: 200px; }
      </style>
      <script>
        // JS for updating real-time sensor values
      </script>
    </head>
    <body>
      <h1>Hydroponics Monitoring</h1>
      <h3>Temperature: )rawliteral" + String(temperature) + R"rawliteral( °C</h3>
      <h3>Humidity: )rawliteral" + String(humidity) + R"rawliteral( %</h3>
      <h3>pH Level: )rawliteral" + String(pH) + R"rawliteral( </h3>
      <h3>Water Level: )rawliteral" + String(waterLevel) + R"rawliteral( cm</h3>
      <h3>Light Intensity: )rawliteral" + String(lightIntensity) + R"rawliteral( lux</h3>
      <a href="/manual"><button>Manual Control</button></a>
    </body>
    </html>
  )rawliteral";
  
  server.send(200, "text/html", html);
}


// Manual control page with buttons
void handleManualControl() {
  String html = manualControlPage();
  server.send(200, "text/html", html);
}

String manualControlPage() {
  String html = "<!DOCTYPE html>\n";
  html += "<html lang=\"en\">\n";
  html += "<head>\n";
  html += "  <meta charset=\"UTF-8\">\n";
  html += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  html += "  <title>Manual Control</title>\n";
  html += "  <style>\n";
  html += "    body { font-family: Arial; text-align: center; }\n";
  html += "    .button { padding: 15px 25px; font-size: 24px; margin: 5px; }\n";
  html += "    .on { background-color: #4CAF50; color: white; }\n";
  html += "    .off { background-color: #f44336; color: white; }\n";
  html += "  </style>\n";
  html += "</head>\n";
  html += "<body>\n";
  html += "  <h1>Manual Control</h1>\n";

  // Pump control button
  html += "  <p><a href=\"/toggle-pump\"><button class=\"button ";
  html += (digitalRead(PUMP_PIN) ? "on" : "off");
  html += "\">";
  html += (digitalRead(PUMP_PIN) ? "Turn Pump OFF" : "Turn Pump ON");
  html += "</button></a></p>\n";

  // Solenoid control button
  html += "  <p><a href=\"/toggle-solenoid\"><button class=\"button ";
  html += (digitalRead(SOLENOID_PIN) ? "on" : "off");
  html += "\">";
  html += (digitalRead(SOLENOID_PIN) ? "Turn Solenoid OFF" : "Turn Solenoid ON");
  html += "</button></a></p>\n";

  // Mist generator control button
  html += "  <p><a href=\"/toggle-mist\"><button class=\"button ";
  html += (digitalRead(MIST_GENERATOR_PIN) ? "on" : "off");
  html += "\">";
  html += (digitalRead(MIST_GENERATOR_PIN) ? "Turn Mist OFF" : "Turn Mist ON");
  html += "</button></a></p>\n";

  // Fertilizer pump control button
  html += "  <p><a href=\"/toggle-fertili\"><button class=\"button ";
  html += (digitalRead(FERTILIZER_PUMP_PIN) ? "on" : "off");
  html += "\">";
  html += (digitalRead(FERTILIZER_PUMP_PIN) ? "Turn Fertilizer OFF" : "Turn Fertilizer ON");
  html += "</button></a></p>\n";

  // Light control button
  html += "  <p><a href=\"/toggle-light\"><button class=\"button ";
  html += (digitalRead(LIGHT_ON_PIN) ? "on" : "off");
  html += "\">";
  html += (digitalRead(LIGHT_ON_PIN) ? "Turn Light OFF" : "Turn Light ON");
  html += "</button></a></p>\n";

  html += "  <p><a href=\"/\"><button>Go Back</button></a></p>\n";
  html += "</body>\n";
  html += "</html>\n";
  
  return html;
}

// Toggle functions for the devices
void handlePumpToggle() {
  digitalWrite(PUMP_PIN, !digitalRead(PUMP_PIN));
  handleManualControl();
}

void handleSolenoidToggle() {
  digitalWrite(SOLENOID_PIN, !digitalRead(SOLENOID_PIN));
  handleManualControl();
}

void handleMistToggle() {
  digitalWrite(MIST_GENERATOR_PIN, !digitalRead(MIST_GENERATOR_PIN));
  handleManualControl();
}

void handleFertilizerPumpToggle() {
  digitalWrite(FERTILIZER_PUMP_PIN, !digitalRead(FERTILIZER_PUMP_PIN));
  handleManualControl();
}

  
void handleLightToggle() {
  digitalWrite(LIGHT_ON_PIN, !digitalRead(LIGHT_ON_PIN));
  handleManualControl();
}

// Monitoring sensors and controlling irrigation
void monitorSensors() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  pH = analogRead(PH_SENSOR_PIN) * (14.0 / 4096.0);  // Example pH conversion
  waterLevel = ultrasonic.read();
  lightIntensity = analogRead(LIGHT_SENSOR_PIN);
}

// Irrigation control logic
void irrigationControl() {
  // Add your logic for automated irrigation, pump control, etc.
	// Automatically control components based on sensor data
  if (temperature > 30) {
    handlePumpToggle();    
  } 
  if(temperature < 20) {
    handlePumpToggle();    
  }

  if (humidity > 30) {    
    handleMistToggle();
  } 
  if (humidity < 20) {
    handleMistToggle();
  }

  if (pH < 6.5) {
    handleFertilizerPumpToggle();
  } 
  if (pH > 7.5) {
    handleFertilizerPumpToggle();
  }

  if (waterLevel < 10) {
    handleSolenoidToggle();
  } 
  if (waterLevel > 60){
    handleSolenoidToggle();
  }

  if (lightIntensity < 10) {
    handleLightToggle();
  } 
  if (lightIntensity > 15){
    handleLightToggle();
  }

}

// Display data on the LCD
void displayLCD() {
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(temperature) + "C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: " + String(humidity) + "%");
  lcd.setCursor(0, 2);
  lcd.print("pH: " + String(pH));
  lcd.setCursor(0, 3);
  lcd.print("Water Level: " + String(waterLevel) + "cm");
}
