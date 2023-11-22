#include <Arduino.h>

const int botonPin = 2; // Pin donde está conectado el botón de emergencia

// Datos predefinidos
const char* nombre = "MELINA MUNGUIA";
const int edad = 30;
const char* domicilio = "AV COLIMA 773 LOS PINOS";

void setup() {
  Serial.begin(115200);
  pinMode(botonPin, INPUT_PULLUP);
}

void loop() {
  int botonEstado = digitalRead(botonPin);

  if (botonEstado == HIGH) {
    // Botón presionado
    Serial.print("Nombre: ");
    Serial.println(nombre);
    Serial.print("Edad: ");
    Serial.println(edad);
    Serial.print("Domicilio: ");
    Serial.println(domicilio);

    // Espera un tiempo para evitar múltiples lecturas por rebote
    delay(1000);
  }
}
