// #include <Arduino.h>
// #include <pinsdef.h>
// #include <main.cpp>

// // put function declarations here:
// void gpsTask(void *pvParameters);

// void gpsTask(void *pvParameters) {
//     Serial1.begin(9600, SERIAL_8N1, GPSRX, GPSTX, false, 1000, 10);
//     while (1) {
//         // put your code here
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
// }

// void vGpsTask(void *pvParameters) {
//     // Serial1.begin(9600, SERIAL_8N1, GPSRX, GPSTX, false, 1000, 10);
//     // enter critical section
//         Serial.println("vGpsTask started");
//     while (1) {
//       // take semaphore
//       if( xSemaphoreTake(xaccessVfdDataSemaphore, portMAX_DELAY) == pdPASS){
//           Serial.printf("gpsTask - globalCounter: %ld\n", globalCounter);
//           globalCounter--;
//           xSemaphoreGive(xaccessVfdDataSemaphore);
//       }
//       vTaskDelay(1000 / portTICK_PERIOD_MS);

//     }
// }