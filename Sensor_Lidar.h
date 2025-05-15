#ifndef Sensor_Lidar_h
#define Sensor_Lidar_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <LiquidCrystal_I2C.h>
#include <BluetoothSerial.h>

class Sensor_Lidar {
public:
    Sensor_Lidar();
    bool begin();
    int readDistance(); // Devuelve la distancia en mm
    void displayDistance(); // Muestra la distancia en pantalla
    bool closeDistance();
    int getPromedio(int n);
    void enviarMedidasPorBluetooth(int n, int intervalo_ms); // NUEVA FUNCIÓN

private:
    Adafruit_VL53L0X lox;
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
    BluetoothSerial SerialBT;
};

#endif
