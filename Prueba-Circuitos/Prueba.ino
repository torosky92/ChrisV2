// Defino las librerias
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Configurar shield de servo
Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

// Defino los puertos de los servos del brazo
#define S1 0 // Giro de antebrazo con servo MG996R
#define S2 1 // Subir o Bajar de antebrazo con servo MG996R
#define S3 2 // Subir o Bajar de brazo con servo MG996R
#define S4 3 // Giro de brazo con servo MG90S
#define S5 4 // Subir o Bajar de Garra con servo MG90S
#define S6 5 // Giro de Garra con servo MG90S
#define S7 6 // Abrir o Cerrar la Garra con servo MG90S
#define S8 7 // Disipador con servo SG90

// Definicion de variables
unsigned int posMG90S0 = 172; // ancho de pulso en cuentas para pocicion 0° con servo MG996R
unsigned int posMG90S180 = 645; // ancho de pulso en cuentas para la pocicion 180° con servo MG996R
unsigned int posMG996R0 = 172; // ancho de pulso en cuentas para pocicion 0° con servo MG90S
unsigned int posMG996R180 = 515; // ancho de pulso en cuentas para la pocicion 180° con servo MG90S
float Servo1 = 0; // Variable de Grados para el Giro de antebrazo con servo MG996R como flotante
float Servo2 = 0; // Variable de Grados para el Subir o Bajar de antebrazo con servo MG996R como flotante
float Servo3 = 0; // Variable de Grados para el Subir o Bajar de brazo con servo MG996R como flotante
float Servo4 = 0; // Variable de Grados para el Giro de brazo con servo MG90S como flotante
float Servo5 = 0; // Variable de Grados para el Subir o Bajar de Garra con servo MG90S como flotante
float Servo6 = 0; // Variable de Grados para el Giro de Garra con servo MG90S como flotante
float Servo7 = 0; // Variable de Grados para el Abrir o Cerrar la Garra con servo MG90S como flotante
float Servo8 = 0; // Variable de Grados para el Disipador con servo SG90 como flotante
//182 a 0 grados

void setup() {
  // Configuracion de servos
  servos.begin(); // Activacion de servos
  servos.setPWMFreq(60); // Configuracion de frecuencia de los servos

  Servo7 = map(2, 0, 180, posMG90S0, posMG90S180); // Valor de grados a 0
  servos.setPWM(S7, 0, Servo7);
  delay(5000);
  Servo7 = map(90, 0, 180, posMG90S0, posMG90S180); // Valor de grados a 90
  servos.setPWM(S7, 0, Servo7);
  delay(1000);

  Servo6 = map(90, 0, 180, posMG90S0, posMG90S180); // Valor de grados a 0
  servos.setPWM(S6, 0, Servo6);
  delay(1000);
  Servo6 = map(0, 0, 180, posMG90S0, posMG90S180); // Valor de grados a 90
  servos.setPWM(S6, 0, Servo6);
  delay(1000);

  Servo5 = map(90, 0, 180, posMG90S0, posMG90S180); // Valor de grados a 0
  servos.setPWM(S5, 0, Servo5);
  delay(1000);
  Servo5 = map(0, 0, 180, posMG90S0, posMG90S180); // Valor de grados a 90
  servos.setPWM(S5, 0, Servo5);
  delay(1000);

  Servo4 = map(90, 0, 180, posMG90S0, posMG90S180); // Valor de grados a 0
  servos.setPWM(S4, 0, Servo4);
  delay(1000);
  Servo4 = map(0, 0, 180, posMG90S0, posMG90S180); // Valor de grados a 90
  servos.setPWM(S4, 0, Servo4);
  delay(1000);

  Servo3 = map(120, 0, 180, posMG996R0, posMG996R180); // Valor de grados a 0
  servos.setPWM(S3, 100, Servo3);
  delay(1000);
  Servo3 = map(50, 0, 180, posMG996R0, posMG996R180); // Valor de grados a 90
  servos.setPWM(S3, 100, Servo3);
  delay(1000);

  Servo2 = map(40, 0, 180, posMG996R0, posMG996R180); // Valor de grados a 0
  servos.setPWM(S2, 100, Servo2);
  delay(2000);
  Servo2 = map(90, 0, 180, posMG996R0, posMG996R180); // Valor de grados a 90
  servos.setPWM(S2, 100, Servo2);
  delay(15000);

  Servo1 = map(0, 0, 180, posMG996R0, posMG996R180); // Valor de grados a 0
  servos.setPWM(S1, 100, Servo1);
  delay(1000);
  Servo1 = map(90, 0, 180, posMG996R0, posMG996R180); // Valor de grados a 90
  servos.setPWM(S1, 100, Servo1);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
