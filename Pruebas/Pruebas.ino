#include "HX711.h"

const int Pin_DT1 = 4;
const int Pin_SCK1 = 2; 
const int Pin_DT2 = 14;
const int Pin_SCK2 = 15;

HX711 balanza1;
HX711 balanza2;

const float interruptor1P15A = 11.8; //Peso por unidad de interruptores tipo 1P-15A.
const float interruptor3P70A = 31.5; //Peso por unidad de interruptores tipo 3P70A.

void setup() {
  Serial.begin(115200);
  balanza1.begin(Pin_DT1, Pin_SCK1);
  balanza2.begin(Pin_DT2, Pin_SCK2);
  Serial.print("Lectura del valor del ADC: Kg");
  Serial.println(balanza1.read());
  Serial.println(balanza2.read());
  Serial.println("No ponga ningún objeto sobre la balanza");
  Serial.println("Destarando...");
  balanza1.set_scale(216583.1652);
  balanza2.set_scale(218664.1038); 
  balanza1.tare(20);
  balanza2.tare(20);
  Serial.println("Coloque sobre la balanza un peso conocido:");
}

void loop() {
  if (balanza1.wait_ready_timeout(2000)) {
    float pesouno = balanza1.get_units(20);
    float peso1 = pesouno * 1000;
    int UnidadesINT1P = peso1 / interruptor1P15A;
    Serial.print("La bascula 1 tiene: ");
    Serial.print(UnidadesINT1P);
    Serial.println(" Unidades");
  } else {
    Serial.println("HX711 no encontrado.");
    delay(2000);
  }

  if (balanza2.wait_ready_timeout(1000)) {
    float pesodos = balanza2.get_units(20);
    float peso2 = pesodos * 1000;
    int UnidadesINT3P = peso2 / interruptor3P70A;
    Serial.print("La bascula 2 tiene: ");
    Serial.print(UnidadesINT3P);
    Serial.println(" Unidades");
  } else {
    Serial.println("HX711 no encontrado.");
    delay(2000);
  }
}
