#include <Arduino.h>
#include <pinsdef.h>
#include <driver/spi_master.h>
// // put function declarations here:



// vfd data:
// segmented display data
// bit structure:
// byte:   0 1 2 3 4 5 6 7 8 
// digit : 1 2 3 4 5 6 7 8 9
// bit:     0 1 2 3 4 5 6 7
// segment: A B C D E F G Dot


static uint8_t g_vfdTable[21] = {segdispdot, segdisp0, segdisp1, segdisp2, segdisp3, segdisp4, segdisp5, segdisp6, segdisp7, segdisp8, segdisp9, segdisp0dot, segdisp1dot, segdisp2dot, segdisp3dot, segdisp4dot, segdisp5dot, segdisp6dot, segdisp7dot, segdisp8dot, segdisp9dot};
volatile uint32_t g_vfdData[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile long g_globalCounter = 0;

spi_device_handle_t vfdspi;

SemaphoreHandle_t xaccessVfdDataSemaphore = NULL;
SemaphoreHandle_t xspiSemaphore = NULL;

void vGpsTask(void *pvParameters);
void vVfdUpdateTask(void *pvParameters);
void displayDigit(uint8_t digit, uint8_t value);
void spi_transaction_complete(spi_transaction_t *t);


void setup() {
  // set vf pins as output
  pinMode(VFLOAD, OUTPUT);
  pinMode(VFBLANK, OUTPUT);
  Serial.begin(115200);

  xaccessVfdDataSemaphore = xSemaphoreCreateBinary();
  xspiSemaphore = xSemaphoreCreateBinary();


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
      .clock_speed_hz = APB_CLK_FREQ/80,  // Clock speed in Hz (10 kHz)
      .spics_io_num = -1,           // CS pin (not used in this example)
      .queue_size = 7,              // Transactions queue size
      .post_cb = spi_transaction_complete
  };

  // Add device to the bus
  ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &vfdspi));


  xTaskCreatePinnedToCore(
    vGpsTask, /* Function to implement the task */
    "gpsTask", /* Name of the task */
    2048,  /* Stack size in words */
    NULL,  /* Task input parameter */
    1,  /* Priority of the task */
    NULL,  /* Task handle. */
    0); /* Core where the task should run */
  // vfd task
  xTaskCreatePinnedToCore(
    vVfdUpdateTask, /* Function to implement the task */
    "vfdTask", /* Name of the task */
    2048,  /* Stack size in words */
    NULL,  /* Task input parameter */
    1,  /* Priority of the task */
    NULL,  /* Task handle. */
    1); /* Core where the task should run */

  xSemaphoreGive(xaccessVfdDataSemaphore);
}

// hardware intettupt on SPI2 done
void spi_transaction_complete(spi_transaction_t *t) {
    // Give the semaphore to unblock the waiting task
    // Serial.println("spi_transaction_complete, giving semaphore");
    digitalWrite(VFLOAD, HIGH);
    digitalWrite(VFLOAD, LOW);
    xSemaphoreGive(xspiSemaphore);
}



void vVfdUpdateTask(void *pvParameters) {
    uint32_t data = 0b11001100110011000000;

    // data structure to send to Display Driver
    spi_transaction_t t = {
        .length = 20,         // Number of bits to transmit
        .tx_buffer = &data,   // Data buffer
        .rx_buffer = NULL     // No data to be received
    };

    vTaskDelay(500);
    Serial.println("vfdUpdateTask started");
    while (1) {
      if( xSemaphoreTake(xaccessVfdDataSemaphore, portMAX_DELAY) == pdPASS){
        // Serial.printf("vfdTask - globalCounter: %ld\n", g_globalCounter);
        xSemaphoreGive(xaccessVfdDataSemaphore);

        // take semaphore
        // send data to display driver
        // Serial.println("vfdTask - Transmitting data to display driver");
        for (int i = 0; i < 9; i++) {
            ESP_ERROR_CHECK(spi_device_transmit(vfdspi, &t));
            // take semaphore
            if( xSemaphoreTake(xspiSemaphore, portMAX_DELAY) == pdPASS){
            }
        }

      }
      // vTaskDelay(9 / portTICK_PERIOD_MS);
    }
}


void vGpsTask(void *pvParameters) {
    // Serial1.begin(9600, SERIAL_8N1, GPSRX, GPSTX, false, 1000, 10);
    // enter critical section
        Serial.println("vGpsTask started");
    while (1) {
      // take semaphore
      // if( xSemaphoreTake(xaccessVfdDataSemaphore, portMAX_DELAY) == pdPASS){
          Serial.printf("gpsTask - globalCounter: %ld\n", g_globalCounter);
          // g_globalCounter--;
      //     xSemaphoreGive(xaccessVfdDataSemaphore);
      // }
      vTaskDelay(10 / portTICK_PERIOD_MS);

    }
}

void displayDigit(uint8_t digit, uint8_t value) {
    // set digit
    digitalWrite(VFDOUT, LOW);
    shiftOut(VFCLK, VFLOAD, MSBFIRST, 1 << digit);
    digitalWrite(VFLOAD, HIGH);
    digitalWrite(VFLOAD, LOW);
    // set value
    digitalWrite(VFDOUT, HIGH);
    shiftOut(VFCLK, VFLOAD, MSBFIRST, value);
    digitalWrite(VFLOAD, HIGH);
    digitalWrite(VFLOAD, LOW);
}

void loop() {
  // nothing to do here
}


