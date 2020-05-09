/*
   Nombre de Proyecto: Chris V2 - Brazo Robotico de 6 Grados de Libertad
   Integrantes: David Antonio Toro Medina
                Santiago Bernal del Rio
                Mateo Maya Uparela
   Programador: David Antonio Toro Medina
   Descripcion: El siguiente codigo es el control del brazo robotico fisico
                con la comunicacion serial entre Arduino y ROS
*/

// Defino las librerias
#include <Wire.h> // Libreria necesario para la tarjeta shield de Servos
#include <Adafruit_PWMServoDriver.h> // Libreria necesario para la tarjeta shield de Servos
#include <ros.h> // Libreria de comunicacion serial entre arduino y ROS
#include <std_msgs/UInt16.h> // Libreria de comunicacion serial entre arduino y ROS
#include <sensor_msgs/JointState.h> // Libreria de comunicacion serial entre arduino y ROS

// Configurar shield de servo
Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

// Defino los puertos de los servos del brazo
ros::NodeHandle  nh;
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
float Servo1 = 90; // Variable de Grados para el Giro de antebrazo con servo MG996R como flotante
float Servo2 = 90; // Variable de Grados para el Subir o Bajar de antebrazo con servo MG996R como flotante
float Servo3 = 90; // Variable de Grados para el Subir o Bajar de brazo con servo MG996R como flotante
float Servo4 = 90; // Variable de Grados para el Giro de brazo con servo MG90S como flotante
float Servo5 = 90; // Variable de Grados para el Subir o Bajar de Garra con servo MG90S como flotante
float Servo6 = 90; // Variable de Grados para el Giro de Garra con servo MG90S como flotante
float Servo7 = 0; // Variable de Grados para el Abrir o Cerrar la Garra con servo MG90S como flotante
float Servo8 = 0; // Variable de Grados para el Disipador con servo SG90 como flotante

// Funcion para el control de los servos de referencia MG90S en general
void setServoMG90S(uint8_t n_servo, int angulo) {
  int duty = map(angulo, 0, 180, posMG90S0, posMG90S180);
  servos.setPWM(n_servo, 20, duty);
}

// Funcion para el control de los servos de referencia MG90S para las pinzas
void setServoPinzaMG90S(uint8_t n_servo, int angulo) {
  int duty = map(angulo, 0, 180, posMG90S0, posMG90S180);
  servos.setPWM(n_servo, 0, duty);
}

// Funcion para el control de los servos de referencia MG996R
void setServoMG996R(uint8_t n_servo, int angulo) {
  int duty = map(angulo, 0, 180, posMG996R0, posMG996R180);
  servos.setPWM(n_servo, 100, duty);
}

// Funcion de recepcion de informacion y configuracion de servos
void servo_cb(const sensor_msgs::JointState& cmd_msg) {
  Servo1 = radiansToDegrees(cmd_msg.position[0]);
  Servo2 = radiansToDegrees(cmd_msg.position[1]);
  Servo3 = radiansToDegrees(cmd_msg.position[2]);
  Servo4 = radiansToDegrees(cmd_msg.position[3]);
  Servo5 = radiansToDegrees(cmd_msg.position[4]);
  Servo6 = radiansToDegrees(cmd_msg.position[5]);
  Servo7 = radiansToDegrees(cmd_msg.position[6]);

  // Control del servo para el control de la puerta de la rampa
  if (Servo3 >= 80) {
    Servo8 = 0;
  }
  else {
    Servo8 = 90;
  }

  // Configuracion de los servos en la posicion
  setServoMG996R(S1, Servo1);
  setServoMG996R(S2, Servo2);
  setServoMG996R(S3, Servo3);
  setServoMG90S(S4, Servo4);
  setServoMG90S(S5, Servo5);
  setServoMG90S(S6, Servo6);
  setServoPinzaMG90S(S7, Servo7);
  setServoMG90S(S8, Servo8);
}

// Conexion de los valores de las articulaciones de la simulacion en ROS
ros::Subscriber<sensor_msgs::JointState> sub("joint_states", servo_cb);

void setup() {
  // Configuracion de comunicacion serial entre Arduino y ROS
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);

  // Configuracion de servos
  servos.begin(); // Activacion de servos
  servos.setPWMFreq(60); // Configuracion de frecuencia de los servos

  // Posicion Inicial del brazo
  setServoMG996R(S1, Servo1);
  setServoMG996R(S2, Servo2);
  setServoMG996R(S3, Servo3);
  setServoMG90S(S4, Servo4);
  setServoMG90S(S5, Servo5);
  setServoMG90S(S6, Servo6);
  setServoPinzaMG90S(S7, Servo7);
  setServoMG90S(S8, Servo8);
}

void loop() {
  nh.spinOnce();
}

//Funcion para convertir de radianes a grados los datos obtenidos
double radiansToDegrees(float position_radians) {
  position_radians = position_radians + 1.6;
  return position_radians * 57.2958;
}
