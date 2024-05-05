#include <Arduino.h>
#include <pinsdef.h>
#include <driver/spi_master.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <FreeRTOS.h>



uint32_t segmentDigits[8];
static uint32_t empty = 0b0;
unsigned long counter = 0;


static spi_transaction_t empty_screen = {
    .length = 32,         // Number of bits to transmit
    .tx_buffer = &empty,   // Data buffer
    .rx_buffer = NULL     // No data to be received
};


spi_device_handle_t vfdspi;

SemaphoreHandle_t xaccessVfdDataSemaphore = NULL;
// SemaphoreHandle_t xspiSemaphore = NULL;

// void displayDigit(uint8_t digit, uint8_t value);
// void spi_transaction_complete(spi_transaction_t *t);



// function declarations
uint32_t getSegmentShow(char c);
void clearScreen(void);
void processString(const char *input);
void vGpsTask(void *pvParameters);
void vVfdUpdateTask(void *pvParameters);





void setup() {
    // set vf pins as output
    pinMode(VFLOAD, OUTPUT);
    pinMode(VFBLANK, OUTPUT);
    Serial.begin(115200);
    Serial1.begin(38400, SERIAL_8N1, GPSTX, GPSRX);
    Serial.println("Hello World");




    // setup spi bus

    spi_bus_config_t buscfg = {
        .mosi_io_num = VFDOUT,     // MOSI pin number
        .miso_io_num = -1,    // MISO not used
        .sclk_io_num = VFCLK,     // SCK pin number
        .quadwp_io_num = -1,  // Not used
        .quadhd_io_num = -1,  // Not used
        .max_transfer_sz = 0  // Default transfer size
    };
    // Initialize the SPI bus
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));


    spi_device_interface_config_t devcfg = {
        .command_bits = 0,
        .address_bits = 0,
        .mode = 0,                    // SPI mode 0
        .clock_speed_hz = SPI_MASTER_FREQ_8M, //APB_CLK_FREQ/80,  // Clock speed in Hz (10 kHz)
        .spics_io_num = -1,           // CS pin (not used in this example)
        .queue_size = 7,              // Transactions queue size
    };

    // Add device to the bus
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &vfdspi));
    Serial.println("SPI configured");

    clearScreen();


    xaccessVfdDataSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xaccessVfdDataSemaphore);
    xTaskCreatePinnedToCore(
        vGpsTask, /* Function to implement the task */
        "gpsTask", /* Name of the task */
        2048,  /* Stack size in words */
        NULL,  /* Task input parameter */
        2,  /* Priority of the task */
        NULL,  /* Task handle. */
        0); /* Core where the task should run */

    xTaskCreatePinnedToCore(
        vVfdUpdateTask, /* Function to implement the task */
        "vfdTask", /* Name of the task */
        2048,  /* Stack size in words */
        NULL,  /* Task input parameter */
        3,  /* Priority of the task */
        NULL,  /* Task handle. */
        1); /* Core where the task should run */
}


void loop() {
    //all done in tasks
}

void vVfdUpdateTask(void *pvParameters) {
    uint32_t segmentDigits_local[8];
    Serial.println("vfdUpdateTask started");
    while (1) {
        for (int i = 0; i < 8; i++) {
            spi_transaction_t t = {
                .length = 32,         // Number of bits to transmit
                .tx_buffer = &segmentDigits[i],   // Data buffer
                .rx_buffer = NULL     // No data to be received
            };
            // take semaphore, transmit data, release semaphore
            if (xSemaphoreTake(xaccessVfdDataSemaphore, portMAX_DELAY) == pdTRUE) {
                if (spi_device_transmit(vfdspi, &t) != ESP_OK) {
                    Serial.println("Error");
                }
                xSemaphoreGive(xaccessVfdDataSemaphore);
            }

            digitalWrite(VFLOAD, HIGH);
            digitalWrite(VFLOAD, LOW);
        }
    }

}


void vGpsTask(void *pvParameters) {
    Serial.println("vGpsTask started");
    while (1) {
        char gpsbuffer[300] = {0};  // Initialize buffer and ensure it's zeroed out
        char time[10];  // Buffer to hold extracted time
        char formattedTime[9];  // Buffer to hold formatted time

        if (Serial1.available()) {
            int len = Serial1.readBytesUntil('\n', gpsbuffer, 269);
            gpsbuffer[len] = '\0';  // Null-terminate the string
            // Serial.println(gpsbuffer);

            // Check if the received string is a GNGGA sentence
            if (strncmp(gpsbuffer, "$GNGGA", 6) == 0) {

                // Extract the time portion from the GNGGA sentence
                if (sscanf(gpsbuffer, "$GNGGA,%6s,", time) == 1) {
                    // Format the time as HH-MM-SS
                    snprintf(formattedTime, sizeof(formattedTime), "%c%c-%c%c-%c%c", 
                            time[0], time[1], time[2], time[3], time[4], time[5]);

                    // Pass the formatted time to the processString function
                    if (xSemaphoreTake(xaccessVfdDataSemaphore, portMAX_DELAY) == pdTRUE) {
                        processString(formattedTime);
                        xSemaphoreGive(xaccessVfdDataSemaphore);
                    }
                } else {
                    Serial.println("Failed to extract time from the GPS data.");
                }
            }
        }
    }
}

/**
 * Returns the segment value to show on a display for a given character.
 *
 * This function takes a character as input and returns the corresponding segment value
 * to display that character on a display. The character can be any alphanumeric character
 * or a limited set of special characters. If the character is not recognized, the function
 * returns the segment value for displaying nothing.
 *
 * @param c The character to display.
 * @return The segment value to show on the display.
 */
uint32_t getSegmentShow(char c) {
    switch (c) {
        case '0': return SEGMENT_SHOW_0;
        case '1': return SEGMENT_SHOW_1;
        case '2': return SEGMENT_SHOW_2;
        case '3': return SEGMENT_SHOW_3;
        case '4': return SEGMENT_SHOW_4;
        case '5': return SEGMENT_SHOW_5;
        case '6': return SEGMENT_SHOW_6;
        case '7': return SEGMENT_SHOW_7;
        case '8': return SEGMENT_SHOW_8;
        case '9': return SEGMENT_SHOW_9;
        case 'A': return SEGMENT_SHOW_A;
        case 'C': return SEGMENT_SHOW_C;
        case 'E': return SEGMENT_SHOW_E;
        case 'F': return SEGMENT_SHOW_F;
        case 'G': return SEGMENT_SHOW_G;
        case 'H': return SEGMENT_SHOW_H;
        case 'I': return SEGMENT_SHOW_I;
        case 'J': return SEGMENT_SHOW_J;
        case 'L': return SEGMENT_SHOW_L;
        case 'O': return SEGMENT_SHOW_O;
        case 'P': return SEGMENT_SHOW_P;
        case 'S': return SEGMENT_SHOW_S;
        case 'T': return SEGMENT_SHOW_T;
        case 'U': return SEGMENT_SHOW_U;
        case 'Z': return SEGMENT_SHOW_Z;
        case '-': return SEGMENT_SHOW_DASH;
        default:  return SEGMENT_SHOW_NONE;
    }
}

/**
 * Clears the screen of the VFD display.
 * This function transmits the `empty_screen` data to the VFD display using SPI communication.
 * If the transmission fails, it prints an error message to the serial monitor.
 * Finally, it toggles the VFLOAD pin to update the display.
 */
void clearScreen(){
    if (spi_device_transmit(vfdspi, &empty_screen) != ESP_OK){
        Serial.println("Error");
    }
    digitalWrite(VFLOAD, HIGH);
    digitalWrite(VFLOAD, LOW);
}


void processString(const char *input) {
    if (strlen(input) != 8) {
        printf("Error: String must be exactly 8 characters long.\n");
        exit(1);
    }

    for (int i = 0; i < 8; i++) {
        uint32_t digitMask = 1 << (31 - i); // Create digit mask starting from DIGIT_1 to DIGIT_8
        segmentDigits[i] = getSegmentShow(input[i]) | digitMask;
    }
}
