//PROYECTO INTEGRADOR DE SABERES
//GRUPO NRO 1
//Marco Castilo
//*Freddy Matailo
//Ariel Tandazo
//Joel Tapia
//Juan Veintimilla
//Codigo Auto controlado por mando de PS2

#include <PS2X_lib.h> // Incluimos la librería PS2X para controlar el mando PS2

class ControladorPs2 { // Se define una clase llamada ControladorPs2
public:
     // Constructor de la clase que inicializa los pines y variables
        ControladorPs2(int in1, int in2, int in3, int in4, int ena, int enb)
        : IN1(in1), IN2(in2), IN3(in3), IN4(in4), ENA(ena), ENB(enb), vibrate(0), error(0) {}

    void setup() { 
        pinMode(IN1, OUTPUT); // Configuracion del pin IN1 como salida
        pinMode(IN2, OUTPUT); // Configuracion del pin IN2 como salida
        pinMode(IN3, OUTPUT); // Configuracion del pin IN3 como salida
        pinMode(IN4, OUTPUT); // Configuracion del pin IN4 como salida
        pinMode(ENA, OUTPUT); // Configuracion del pin ENA como salida
        pinMode(ENB, OUTPUT); // Configuracion del pin ENB como salida

        delay(300); // Espera 300 ms
        error = ps2x.config_gamepad(4, 6, 5, 7, true, true); // Configuracion del driver del mando PS2.
    }

    void loop() { 
        int aux; // Variable auxiliar
        int temp; // Variable para almacenar valores temporales
        int x; // Variable para el valor analógico del joystick izquierdo en el eje X
        ps2x.read_gamepad(false, vibrate); // Lee el estado del mando PS2 

        x = ps2x.Analog(PSS_LX) - 127; // Lee el valor del joystick izquierdo en el eje X y lo ajusta
        if (x == 128)
            x = 127; // Ajusta el valor máximo

        if (ps2x.Button(PSB_BLUE)) { // Si se presiona el botón x
            temp = ps2x.Analog(PSAB_BLUE); // Lee el valor analógico del x

            if (x < -27) { // Si el joystick se mueve a la izquierda
                x = x + 127; // Ajusta el valor de x
                aux = (temp * x) / 100; // Calcula el valor auxiliar para el motor
                motores(1, temp, aux); // Controla los motores con el valor calculado
            } else if (x > 27) { // Si el joystick se mueve a la derecha
                x = (-1) * x + 127; // Ajusta el valor de x
                aux = (temp * x) / 100; // Calcula el valor auxiliar para el motor
                motores(1, aux, temp); // Controla los motores con el valor calculado
            } else {
                motores(1, temp, temp); // Controla los motores con el mismo valor
            }
        } else if (ps2x.Button(PSB_RED)) { // Si se presiona el botón circulo
            temp = ps2x.Analog(PSAB_RED); // Lee el valor analógico del circulo
            motores(-1, temp, temp); // Controla los motores en dirección opuesta con el valor leído
        } else {
            motores(0, 0, 0); // Detiene los motores
        }

        delay(50); // Espera 50 ms antes de la siguiente iteración
    }

private:
    void motores(int v, int m1, int m2) { // Método para controlar los motores
        if (v == 1) { // Si v es 1, mueve hacia adelante
            digitalWrite(IN1, HIGH); // Activa IN1
            digitalWrite(IN2, LOW); // Desactiva IN2
            digitalWrite(IN3, LOW); // Desactiva IN3
            digitalWrite(IN4, HIGH); // Activa IN4
        } else if (v == -1) { // Si v es -1, mueve hacia atrás
            digitalWrite(IN1, LOW); // Desactiva IN1
            digitalWrite(IN2, HIGH); // Activa IN2
            digitalWrite(IN3, HIGH); // Activa IN3
            digitalWrite(IN4, LOW); // Desactiva IN4
        } else { // Si v es 0, detiene el movimiento
            digitalWrite(IN1, LOW); // Desactiva IN1
            digitalWrite(IN2, LOW); // Desactiva IN2
            digitalWrite(IN3, LOW); // Desactiva IN3
            digitalWrite(IN4, LOW); // Desactiva IN4
        }

        analogWrite(ENA, m1); // Controla la velocidad del motor ENA con el valor m1
        analogWrite(ENB, m2); // Controla la velocidad del motor ENB con el valor m2
    }

    PS2X ps2x; // Instancia de la clase PS2X para el mando PS2
    int error; // Variable para almacenar errores de configuración
    byte vibrate; // Variable para controlar la vibración del mando
    const int IN1, IN2, IN3, IN4, ENA, ENB; // Pines de control y velocidad de los motores
};

ControladorPs2 controladorPs2(13, 12, 9, 8, 11, 10); // Crea una instancia del controlador PS2 con los pines especificados

void setup() {
    controladorPs2.setup(); // Llama al método setup de la instancia del controlador PS2
}

void loop() {
    controladorPs2.loop(); // Llama al método loop de la instancia del controlador PS2
}

//FIN DEL CODIGO
