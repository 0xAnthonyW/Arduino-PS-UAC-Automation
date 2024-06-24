# Arduino-PS-UAC-Automation

This project demonstrates how to use an Arduino (CJMCU ATmega32u4) to automate the execution of a PowerShell script with elevated privileges and handle User Account Control (UAC) prompts.

## Overview

The script utilizes the Arduino's keyboard emulation capabilities to:
1. Open the Run dialog.
2. Launch PowerShell with elevated privileges.
3. Execute a specified PowerShell script.
4. Automatically accept the UAC prompt.

## Getting Started

### Prerequisites

- Arduino IDE
- CJMCU ATmega32u4 (or any ATmega32u4-based board)
- PowerShell script to be executed (e.g., `D:\Test2.ps1`)

### Hardware Setup

1. Connect the CJMCU ATmega32u4 to your computer via USB.
2. Ensure the correct board and port are selected in the Arduino IDE:
   - **Tools** > **Board** > **Arduino Leonardo**
   - **Tools** > **Port** > Select the appropriate COM port

### Arduino Sketch

Upload the following sketch to your Arduino:

```cpp
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
