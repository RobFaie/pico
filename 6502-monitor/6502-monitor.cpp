#include <stdio.h>
#include <inttypes.h>
#include <string>
#include "pico/stdlib.h"

const uint LED_PIN = 25;
const uint dataPins [8] = {16, 17, 18, 19, 20, 21, 26, 27};

void gpio_callback(uint gpio, uint32_t events)
{
    gpio_put(LED_PIN, 1);

    long address = 0;
    long data = 0;
    long d = 0;
    int tmp;
    std::string addressBinary = "";
    std::string dataBinary = "";

    for (int32_t i = 15; i >= 0; i--)
    {
        tmp = gpio_get(i) ? 1 : 0;
        addressBinary += '0' + tmp;
        address = address << 1;
        address += tmp;
    }

    for (int32_t i = 7; i >= 0; i--)
    {
        d = dataPins[i];
        tmp = gpio_get(d) ? 1 : 0;
        dataBinary += '0' + tmp;
        data = data << 1;
        data += tmp;
    }

    char rw = gpio_get(28) ? 'r' : 'w';

    char buffer [75];
    int n = sprintf (buffer, "Address: %s    %04X    %c    Data: %s    %02X", addressBinary.c_str(), address, rw, dataBinary.c_str(), data);
    puts(buffer);
    gpio_put(LED_PIN, 0);
}

int main()
{
    stdio_init_all();

    gpio_init_mask (0b11100011111111111111111111111);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    gpio_set_irq_enabled_with_callback(22, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);

    while (true) {
    }
}
