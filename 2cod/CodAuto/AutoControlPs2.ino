
#include <PS2X_lib.h>

class ControladorPs2 {
public:
    ControladorPs2(int in1, int in2, int in3, int in4, int ena, int enb)
        : IN1(in1), IN2(in2), IN3(in3), IN4(in4), ENA(ena), ENB(enb), vibrate(0), error(0) {}

    void setup() {
        pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
        pinMode(IN3, OUTPUT);
        pinMode(IN4, OUTPUT);
        pinMode(ENA, OUTPUT);
        pinMode(ENB, OUTPUT);

        delay(300);
        error = ps2x.config_gamepad(4, 6, 5, 7, true, true);  // (clock, command, attention, data)
    }

    void loop() {
        int aux;
        int temp;
        int x;
        ps2x.read_gamepad(false, vibrate);

        x = ps2x.Analog(PSS_LX) - 127;
        if (x == 128)
            x = 127;

        if (ps2x.Button(PSB_BLUE)) {
            temp = ps2x.Analog(PSAB_BLUE);

            if (x < -27) {
                x = x + 127;
                aux = (temp * x) / 100;
                motores(1, temp, aux);
            } else if (x > 27) {
                x = (-1) * x + 127;
                aux = (temp * x) / 100;
                motores(1, aux, temp);
            } else {
                motores(1, temp, temp);
            }
        } else if (ps2x.Button(PSB_RED)) {
            temp = ps2x.Analog(PSAB_RED);
            motores(-1, temp, temp);
        } else {
            motores(0, 0, 0);
        }

        delay(50);
    }

private:
    void motores(int v, int m1, int m2) {
        if (v == 1) {
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
        } else if (v == -1) {
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
        } else {
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
        }

        analogWrite(ENA, m1);
        analogWrite(ENB, m2);
    }

    PS2X ps2x;
    int error;
    byte vibrate;
    const int IN1, IN2, IN3, IN4, ENA, ENB;
};

ControladorPs2 controladorPs2(13, 12, 9, 8, 11, 10);

void setup() {
    controladorPs2.setup();
}

void loop() {
    controladorPs2.loop();
}
