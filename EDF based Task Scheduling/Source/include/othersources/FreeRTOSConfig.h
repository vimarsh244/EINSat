#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Define the number of priorities for the EDF scheduler */
#define configMAX_PRIORITIES     10

/* Define the tick rate for the EDF scheduler */
#define configTICK_RATE_HZ       1000

/* Define the size of the global heap */
#define configTOTAL_HEAP_SIZE    ((size_t) (50 * 1024))

/* Define the size of the task stacks */
#define configMINIMAL_STACK_SIZE ((unsigned short) 64)
#define configTASK_STACK_SIZE    ((unsigned short) 512)

/* Define the interrupt priority for the EDF scheduler */
#define configKERNEL_INTERRUPT_PRIORITY     255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    191

/* Define the type of timer to be used by the EDF scheduler */
#define configUSE_TIMER_TASK    1

#endif /* FREERTOS_CONFIG_H */
