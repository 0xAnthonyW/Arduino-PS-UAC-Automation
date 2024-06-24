/*
    Arduino-PS-UAC-Automation
    Opens powershell and runs the defined script

    Should Work with any ATmega32U4 or SAMD device.

    Author: 0xAnthonyW
    Date: 06/2024
    https://github.com/0xAnthonyW/Arduino-PS-UAC-Automation
*/


#include <Keyboard.h>

void setup() {
    // Initialize the Keyboard library
    Keyboard.begin();
    delay(1000); // Give the computer time to recognize the USB device

    // Open the Run dialog box (Windows + R)
    Keyboard.press(KEY_LEFT_GUI);  // Press Windows key
    Keyboard.press('r');           // Press 'r' key
    delay(500);
    Keyboard.releaseAll();         // Release all keys

    delay(500); // Wait for the Run dialog box to open

    // Type the PowerShell command to run the script with elevated privileges and bypass execution policy
    Keyboard.print("powershell -Command \"Start-Process powershell -ArgumentList '-NoProfile -ExecutionPolicy Bypass -File \"D:\\Test2.ps1\"' -Verb RunAs\"");
    delay(500);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();

    // Wait for the UAC prompt to appear
    delay(3000); // Increase delay to ensure UAC prompt appears

    // Accept the UAC prompt (Alt + Y)
    digitalWrite(LED_BUILTIN, HIGH); // Turn on LED to indicate UAC handling
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('y');
    delay(500);
    Keyboard.releaseAll();
    digitalWrite(LED_BUILTIN, LOW); // Turn off LED

    // Indicate the script has finished
    while (true) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
    }
}

void loop() {
    // Do nothing
}
