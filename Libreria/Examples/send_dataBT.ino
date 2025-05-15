#include "Sensor_Lidar.h"

Sensor_Lidar sensor;

void setup() {
    Serial.begin(115200);
    if (!sensor.begin()) {
        Serial.println("Error iniciando el sensor LIDAR");
        while (1);
    }
}

void loop() {
    // Envía 5 mediciones cada 5 segundos y luego el promedio
    sensor.enviarMedidasPorBluetooth(5, 1000);
    delay(15000); // espera 15 segundos antes de la próxima serie
}
