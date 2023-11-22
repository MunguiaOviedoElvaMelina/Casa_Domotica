#include <MQ135.h>


#define MQ135_PIN 34  // Reemplaza con el pin al que has conectado el sensor

MQ135 mq135(MQ135_PIN);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Lee la resistencia de gas del sensor
  float rs = mq135.getResistance();

  // Calcula la concentración de CO2 en el aire (valor aproximado)
  float ppmCO2 = mq135.getPPM();

  // Imprime el valor en el monitor serial
  Serial.print("Concentración de CO2 (aproximada): ");
  Serial.print(ppmCO2);
  Serial.println(" ppm");

  delay(1000); // Espera un segundo antes de tomar otra lectura
}
