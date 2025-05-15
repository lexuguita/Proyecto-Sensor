#include <Sensor_Lidar.h>

Sensor_Lidar sensor;

void setup() {
  Serial.begin(115200);

  if (!sensor.begin()) {
    Serial.println("Sensor Lidar no detectado");
    while (1);
  }

  Serial.println("Sensor iniciado correctamente");
}

void loop() {
  int d = sensor.readDistance();
  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.println(" mm");

  sensor.displayDistance();
  delay(1000);
}
