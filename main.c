/**
 * main.c
 */
//FreeRTOS include files
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

//Standard lib include files
#include <stdint.h>
#include <stdbool.h>

//TivaWare includes
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "utils/uartstdio.h"
#include "driverlib/uart.h"
#include <string.h> // for strlen()

//*****************************************************************************
//
// The mutex that protects concurrent access of UART from multiple tasks.
//
//*****************************************************************************


//Function prototypes
void NullTaskFunc(void *);
void BlinkMyLED(void *);
void ConfigureUART(void);
void Task1 (void*);
void Task2 (void*);

xQueueHandle queue_handle = NULL; //queue
xSemaphoreHandle gatekeeper = 0; //semaphore

int main(void) {
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    //
    // Initialize the UART and configure it for 115,200, 8-N-1 operation.
    //
    ConfigureUART();

    //
    // Print demo introduction.
    //
    UARTprintf("\nWelcome to NISI's FreeRTOS Demo!\n");

    //Create mutex to guard UART
    gatekeeper = xSemaphoreCreateMutex();

    // queue to send items between tasks, syntax: xQueueCreate(max queue items, 1 item size)
    queue_handle = xQueueCreate(2, sizeof(int));

    // Create tasks
    xTaskCreate(Task1, (const char*) "t1", 1024, NULL, 1, NULL);
    xTaskCreate(Task2, (const char*) "t2", 1024, NULL, 5, NULL);

    vTaskStartScheduler();   //Start FreeRTOS!

    //Should never get here since RTOS should never "exit"!
    //while(1);
    return 0;
}

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
};

void Task1 (void *p) {
    int item = 0;
    while(1){
        if (xSemaphoreTake(gatekeeper, 1000)) {
            UARTprintf("\nNow in task 1\n");
            long ok = xQueueSend(queue_handle, &item, 500); //(name of queue, item to send, time to wait if queue is full)
            xSemaphoreGive(gatekeeper);
            // ok ? UARTprintf("Item send to queue successfully") : UARTprintf("Failed to send item to queue");

            if (ok==true) {
                UARTprintf("Item send to queue successfully\n");
            } else {
                UARTprintf("Failed to send item to queue\n");
            }

        }
        else {
            UARTprintf("\nTask 1 failed access");
        }
        vTaskDelay(200); //delay task to not run before 1 second
    };
};

void Task2 (void *p) {
    int item = 0;
    while(1){
        if (xSemaphoreTake(gatekeeper, 1000)) {
            UARTprintf("\nNow in task 2\n");
            if (xQueueReceive(queue_handle, &item, 500)) {
                UARTprintf("Task 2 got item from queue\n");
            }
            xSemaphoreGive(gatekeeper);
        }
        else {
            UARTprintf("\nTask 2 failed access");
        }
        vTaskDelay(200); //delay task to not run before 1 second
    };
};
