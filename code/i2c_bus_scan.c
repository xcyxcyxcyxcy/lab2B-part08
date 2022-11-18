#include <stdio.h>
#include <stdlib.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "registers.h"
#include "ADPS_REGISTER.h"
#include "adafruit_qtpy_rp2040.h"
#include "pico/stdlib.h"
#include "pio_i2c.h"

#define PIN_SDA 22
#define PIN_SCL 23

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void SET_ADPS(PIO pio, uint sm){
    
    uint8_t A[2] = {0};

    
    A[0] = ATIME_REGISTER;
    A[1] = (uint8_t)(0x81);
    pio_i2c_write_blocking(pio, sm, ADPS_ADDRESS, A, 2);

   
    A[0] = ADPS_CONTROL_ONE_REGISTER;
    A[1] = ADPS_CONTROL_ONE_AGAIN;
    pio_i2c_write_blocking(pio, sm, ADPS_ADDRESS, A, 2);

    A[0] = ADPS_ENABLE_REGISTER;
    A[1] = ADPS_ENABLE_PON | ADPS_ENABLE_AEN | ADPS_ENABLE_PEN;
    pio_i2c_write_blocking(pio, sm, ADPS_ADDRESS, A, 2);
}

void ADPS_READ(PIO pio, uint sm, uint8_t reg_ad, uint8_t *B, uint bytes) {
    
    pio_i2c_write_blocking(pio, sm, ADPS_ADDRESS, &reg_ad, 1);  
    pio_i2c_read_blocking(pio, sm, ADPS_ADDRESS, B, bytes);
}

int main() {
    stdio_init_all();

    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &i2c_program);
    i2c_program_init(pio, sm, offset, PIN_SDA, PIN_SCL);

    while(!stdio_usb_connected());

    printf("Proximity and color\n");

    SET_ADPS(pio, sm);
 
    while(1) {
        
        
        uint8_t B[1] = {0};
        ADPS_READ(pio, sm, STATUS_REGISTER, B, 1);
        ADPS_READ(pio, sm, ID_REGISTER, B, 1);

        // Mask to check Proximity and color data to read
        uint8_t data_arr[8] = {0};

        if ((B[0] & STATUS_REGISTER_AVALID) == STATUS_REGISTER_AVALID) {
            ADPS_READ(pio, sm, RGBC_DATA_REGISTER_CDATAL, data_arr, 8);
            uint16_t c_val = (data_arr[1] << 8 | data_arr[0]); 
            uint16_t r_val = (data_arr[3] << 8 | data_arr[2]); 
            uint16_t g_val = (data_arr[5] << 8 | data_arr[4]); 
            uint16_t b_val = (data_arr[7] << 8 | data_arr[6]); 
            printf("Color Values : (%d, %d, %d, %d)\n", r_val, g_val, b_val, c_val);
        }

        if ((B[0] & STATUS_REGISTER_PVALID) == STATUS_REGISTER_PVALID) {
            ADPS_READ(pio, sm, PROXIMITY_DATA_REGISTER, data_arr, 1);
            printf("Proximity Value : %d\n", data_arr[0]);
        } 
        
        sleep_ms(500); 
    }
    return 0;
}
