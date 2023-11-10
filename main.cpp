#include "mbed.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

UnbufferedSerial pc(USBTX, USBRX, 9600);
AnalogIn ain(A0);
PwmOut ledR(LED1);
Timer t;
void aceleracionGrav(vector<double>& tiempo, vector<double>& posicion) {
  int n = tiempo.size() - 1;
  double aceleracion = 2 * (posicion[n] - posicion[0]) /
                       (tiempo[n] - tiempo[0]) / (tiempo[n] - tiempo[0]);
  cout << "Aceleración gravitacional: " << aceleracion << endl;
}

int main() {

  ledR = 1;
  float previousReading = 0.0;
  vector<double> tiempo = {};
  vector<double> posicion = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28};

  while (true) {
    
    t.start();

    if (ain <= 0.08) {
      cout << ain << endl;
      t.stop();
      cout << "Tiempo transcurrido: " << t.elapsed_time().count()
           << " milisegundos" << endl;

      // Agregar el tiempo transcurrido al vector tiempo
      tiempo.push_back(t.elapsed_time().count());

      // Verificar si el vector tiempo contiene 14 valores
      if (tiempo.size() == 14) {
        // Invocar la función aceleracionGrav
        aceleracionGrav(tiempo, posicion);

        // Limpiar el vector tiempo para futuras mediciones
        // tiempo.clear();
      }
    }

    // Añade una condición de salida para salir del bucle cuando sea necesario.
    if (tiempo.size() == 14) {
      break;
    }

    // ThisThread::sleep_for(150ms);
  }
}