#include "mbed.h"
#include "defines.h"
#include <cstdint>


DigitalIn llave(BUTTON1);
DigitalOut led(LED1);
DigitalOut buzzer(PA_10);
UnbufferedSerial puertoSerial(CONSOLE_TX, CONSOLE_RX);

bool llave_pressed = false;
bool llave_released = false;
bool char_written = false;
bool dot = false;
bool dash = false;
uint32_t inicio = 0, final = 0;

// main() runs in its own thread in the OS
int main()
{
    puertoSerial.baud(19200);
    puertoSerial.format(8, SerialBase::None, 1);

    while (true) {
        if (!llave && !llave_pressed) {
            char_written = false;
            llave_pressed = true;
            inicio = millis();
            led = ON;
            buzzer = ON;
        }

        if (llave && llave_pressed) {
            llave_released = true;
            final = millis();
            led = OFF;
            buzzer = OFF;
        }

        if (llave_pressed && llave_released) {
            if (final - inicio < 240) { // 5 WPM
                dot = true;
            } else if (final - inicio < 720) { // 5 WPM
                dash = true;
            }
            llave_pressed = false;
            llave_released = false;
            char_written = true;
            inicio = millis();
        }

        if (dot) {
            puertoSerial.write(DOT, 1);
            dot = false;
        } else if (dash) {
            puertoSerial.write(DASH, 1);
            dash = false;
        }

        if (llave && char_written) {
            if (millis() - inicio > 720) {
                puertoSerial.write("\n", 1);
                char_written = 0;
            }
        }
    }
}

