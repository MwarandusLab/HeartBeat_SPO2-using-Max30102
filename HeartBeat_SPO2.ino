#include <Wire.h>
#include <Adafruit_GPS.h>

// Initialize the GPS module using hardware Serial
Adafruit_GPS GPS(&Serial1);

void setup() {
  // Start serial communication with a baud rate of 9600
  Serial.begin(9600);

  // Initialize the GPS module
  Serial1.begin(9600); // NEO-6M GPS module baud rate
  GPS.begin(Serial1);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  delay(1000);
}

void loop() {
  // Read GPS data
  char c = GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) {
      return;
    }

    // Extract GPS information
    float latitude = GPS.latitudeDegrees;
    float longitude = GPS.longitudeDegrees;

    // Print latitude and longitude on the serial monitor
    Serial.print("Latitude: ");
    Serial.println(latitude, 6); // Print latitude with 6 decimal places
    Serial.print("Longitude: ");
    Serial.println(longitude, 6); // Print longitude with 6 decimal places
  }
}
