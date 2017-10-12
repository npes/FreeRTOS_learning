/*
 * Check all the required application specific macros have been defined.
 * These macros are application specific and (as downloaded) are defined
 * within FreeRTOSConfig.h.
 */




// Mandatory
#define configMINIMAL_STACK_SIZE 32 // Idle task stack (in 32-bit words)
#define configMAX_PRIORITIES 8 // Adjustable but I kept it at 8 for kicks.
#define configUSE_PREEMPTION 1
#define configUSE_IDLE_HOOK 0
#define configUSE_TICK_HOOK 0
#define INCLUDE_vTaskPrioritySet 0
#define INCLUDE_uxTaskPriorityGet 0
#define INCLUDE_vTaskDelete 1
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_vTaskDelayUntil 0
#define INCLUDE_vTaskDelay 1
#define configUSE_16_BIT_TICKS 0 // not sure what this is
#define configKERNEL_INTERRUPT_PRIORITY (7 << 5) // Lowest priority for RTOS periodic interrupts
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (1 << 5) // Leaves IRQ priority 0 for any non-RTOS Real Time interrupts
#define configTOTAL_HEAP_SIZE (24 * 1024) // Adjustable - TM4C123 should support at least 24KB heap
#define configCPU_CLOCK_HZ 80000000UL // Full 80MHz clock
#define configTICK_RATE_HZ 1000 // 1ms SysTick ticker



// Optional stuff
#define configUSE_MUTEXES 1
// #define configUSE_RECURSIVE_MUTEXES 0
// #define configUSE_COUNTING_SEMAPHORES 0
// #define configUSE_QUEUE_SETS 0
// #define configUSE_TIMERS 0
// #define configUSE_ALTERNATIVE_API 0
// #define configUSE_TRACE_FACILITY 0
// #define configUSE_CO_ROUTINES 0
// #define configUSE_STATS_FORMATTING_FUNCTIONS 0
// #define configUSE_TICKLESS_IDLE 0
// #define configUSE_APPLICATION_TASK_TAG 0
// #define configNUM_THREAD_LOCAL_STORAGE_POINTERS 0
// #define configGENERATE_RUN_TIME_STATS 0
// #define configUSE_NEWLIB_REENTRANT 0
// #define configUSE_TASK_NOTIFICATIONS 0
// #define configUSE_PORT_OPTIMIZED_TASK_SELECTION 0
// #define configCHECK_FOR_STACK_OVERFLOW 0
// #define configIDLE_SHOULD_YIELD 0
// #define configEXPECTED_IDLE_TIME_BEFORE_SLEEP 0
// #define configMAX_TASK_NAME_LEN 0
// #define configTIMER_TASK_STACK_DEPTH 0
// #define configTIMER_TASK_PRIORITY 0
// #define configTIMER_QUEUE_LENGTH 0

// #define INCLUDE_xTimerPendFunctionCall 1
// #define INCLUDE_xTaskGetSchedulerState 1
// #define INCLUDE_xSemaphoreGetMutexHolder 1
// #define INCLUDE_xTaskGetIdleTaskHandle 1
// #define INCLUDE_eTaskGetState 1
// #define INCLUDE_xTaskResumeFromISR 1
// #define INCLUDE_xTaskGetIdleTaskHandle 1
// #define INCLUDE_pcTaskGetTaskName 1
// #define INCLUDE_uxTaskGetStackHighWaterMark 1
// #define INCLUDE_xTaskGetCurrentTaskHandle 1
// #define INCLUDE_xTaskGetSchedulerState 1
// #define INCLUDE_xTimerGetTimerDaemonTaskHandle 1
