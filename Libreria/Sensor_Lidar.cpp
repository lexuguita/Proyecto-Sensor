#include "Sensor_Lidar.h"

Sensor_Lidar::Sensor_Lidar() {}

bool Sensor_Lidar::begin() {
    lcd.init();
    lcd.backlight();
    if (!lox.begin()) {
        lcd.print("Lidar error");
        return false;
    }
    SerialBT.begin("ESP32_Lidar"); // Nombre del dispositivo Bluetooth
    return true;
}

int Sensor_Lidar::readDistance() {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);
    if (measure.RangeStatus != 4) {
        return measure.RangeMilliMeter;
    }
    else {
        return -1; // error de lectura
    }
}

void Sensor_Lidar::displayDistance() {
    int distance = readDistance();
    lcd.clear();
    if (distance != -1) {
        lcd.setCursor(0, 0);
        lcd.print("Distancia:");
        lcd.setCursor(0, 1);
        lcd.print(distance);
        lcd.print(" mm");
    }
    else {
        lcd.print("Error lectura");
    }
}

bool Sensor_Lidar::closeDistance() {
    int distance = readDistance();
    return (distance != -1 && distance < 100); // por ejemplo, < 100mm
}

int Sensor_Lidar::getPromedio(int n) {
    long suma = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        int d = readDistance();
        if (d != -1) {
            suma += d;
            count++;
        }
        delay(50);
    }
    return (count > 0) ? suma / count : -1;
}

void Sensor_Lidar::enviarMedidasPorBluetooth(int n, int intervalo_ms) {
    SerialBT.println("Iniciando envio de medidas:");
    for (int i = 0; i < n; i++) {
        int d = readDistance();
        if (d != -1) {
            SerialBT.print("Medida ");
            SerialBT.print(i + 1);
            SerialBT.print(": ");
            SerialBT.print(d);
            SerialBT.println(" mm");
        }
        else {
            SerialBT.print("Medida ");
            SerialBT.print(i + 1);
            SerialBT.println(": Error");
        }
        delay(intervalo_ms);
    }

    int promedio = getPromedio(n);
    if (promedio != -1) {
        SerialBT.print("Promedio: ");
        SerialBT.print(promedio);
        SerialBT.println(" mm");
    }
    else {
        SerialBT.println("No se pudo calcular el promedio");
    }
}
