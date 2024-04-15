// #include <Arduino.h>
// #include <pinsdef.h>
// #include <main.cpp>

//The MAX6921/MAX6931 are normally written using the
// following sequence:
// 1) Take CLK low.
// 2) Clock 20 bits of data in order D19 first to D0 last
// into DIN, observing the data setup and hold times.
// 3) Load the 20 output latches with a falling edge
// on LOAD.
// LOAD can be high or low during a transmission. If
// LOAD is high, then the data shifted into the shift register at DIN appear at the OUT0 to OUT19 outputs.
// CLK and DIN can be used to transmit data to other
// peripherals. Activity on CLK always shifts data into the
// MAX6921/MAX6931s’ shift register. However, the
// MAX6921/MAX6931 only update their output latch on
// the rising edge of LOAD, and the last 20 bits of data
// are loaded. Therefore, multiple devices can share CLK
// and DIN, as long as they have unique LOAD controls.



// PUTPUT PIN definitions:
// Digit 1 - bit 0
// Digit 2 - bit 1
// Digit 3 - bit 2
// Digit 4 - bit 3
// Digit 5 - bit 4
// Digit 6 - bit 5
// Digit 7 - bit 6
// Digit 8 - bit 7
// Digit 9 - bit 8

// Segment A - bit 9
// Segment B - bit 10
// Segment C - bit 11
// Segment D - bit 12
// Segment E - bit 13
// Segment F - bit 14
// Segment G - bit 15
// Segment Dot - bit 16


// void displayDigit(uint8_t digit, uint8_t value) {
//     // set digit
//     digitalWrite(VFDOUT, LOW);
//     shiftOut(VFCLK, VFLOAD, MSBFIRST, 1 << digit);
//     digitalWrite(VFLOAD, HIGH);
//     digitalWrite(VFLOAD, LOW);
//     // set value
//     digitalWrite(VFDOUT, HIGH);
//     shiftOut(VFCLK, VFLOAD, MSBFIRST, value);
//     digitalWrite(VFLOAD, HIGH);
//     digitalWrite(VFLOAD, LOW);
// }



// void vVfdUpdateTask(void *pvParameters) {
//     vTaskDelay(500);
//     Serial.println("vfdUpdateTask started");
//     while (1) {
//       if( xSemaphoreTake(xaccessVfdDataSemaphore, portMAX_DELAY) == pdPASS){
//           Serial.printf("vfdTask - globalCounter: %ld\n", globalCounter);
//           globalCounter++;
//           xSemaphoreGive(xaccessVfdDataSemaphore);
//       }
//       vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
// }

