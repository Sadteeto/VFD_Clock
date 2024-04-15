// #include <Arduino.h>
// #include <driver/spi_master.h>
// #include <pinsdef.h>

// void setupspi(){
//     spi_bus_config_t buscfg = {
//         .mosi_io_num = VFDOUT,     // MOSI pin number
//         .miso_io_num = -1,    // MISO not used
//         .sclk_io_num = VFCLK,     // SCK pin number
//         .quadwp_io_num = -1,  // Not used
//         .quadhd_io_num = -1,  // Not used
//         .max_transfer_sz = 0  // Default transfer size
//     };

//     // Initialize the SPI bus
//     ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));

//     spi_device_handle_t vfdspi;

//     spi_device_interface_config_t devcfg = {
//         .command_bits = 0,
//         .address_bits = 0,
//         .mode = 0,                    // SPI mode 0
//         .clock_speed_hz = 10 * 1000,  // Clock speed in Hz (10 kHz)
//         .spics_io_num = -1,           // CS pin (not used in this example)
//         .queue_size = 7              // Transactions queue size

//     };

//     // Add device to the bus
//     ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &vfdspi));


//     uint32_t data = 0b11001100110011000000; // 20-bit data
//     spi_transaction_t t = {
//         .length = 20,         // Number of bits to transmit
//         .tx_buffer = &data,   // Data buffer
//         .rx_buffer = NULL     // No data to be received

//     };

//     // Transmit data
//     ESP_ERROR_CHECK(spi_device_transmit(vfdspi, &t));
// }

// void vdisplay_Task(){
//     uint32_t data;
//     spi_transaction_t t = {
//         .length = 20,         // Number of bits to transmit
//         .tx_buffer = &data,   // Data buffer
//         .rx_buffer = NULL     // No data to be received
//     };


//     //REPEAT FOREVER
//     // TAKE SEMAPHORE
//     // CHECK THE CURRENT BUFFER OF THE REGISTER
//     // RELEASE SEMAPHORE
//         // loop 9 times,
//         // in each loop: char: match the truth table 
//         // add the bit of the current digit, and form a 20-bit data
//         // wait take for SPI done semaphore 
//         // shift out the data and toggle LOAD pin.
//         // release SPI done semaphore
    
// }