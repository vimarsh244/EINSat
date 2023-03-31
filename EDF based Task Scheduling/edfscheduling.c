// write freertos code for EDF (earliest deadline first) based task scheduling
// Here's an example FreeRTOS code for implementing Earliest Deadline First (EDF) scheduling:

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Define the task structure
typedef struct
{
    TaskFunction_t function;
    TickType_t deadline;
    TickType_t period;
    TaskHandle_t handle;
} Task;

// Declare the task functions
void task1(void *pvParameters);
void task2(void *pvParameters);
void task3(void *pvParameters);

// Create the tasks
Task tasks[] = {
    {task1, 200, 500, NULL},
    {task2, 300, 1000, NULL},
    {task3, 100, 3000, NULL}};

const int numTasks = sizeof(tasks) / sizeof(Task);


// Define the task priorities
const int priorities[] = {
    configMAX_PRIORITIES - 1,
    configMAX_PRIORITIES - 2,
    configMAX_PRIORITIES - 3};

// Define the task periods
const TickType_t periods[] = {
    pdMS_TO_TICKS(500),
    pdMS_TO_TICKS(1000),
    pdMS_TO_TICKS(3000)};

// Define the task handles
TaskHandle_t taskHandles[numTasks];

// Define the task queue
QueueHandle_t taskQueue;

// Define the current time
TickType_t currentTime;

void task1(void *pvParameters)
{
    while (1)
    {
        // Do the task
        vTaskDelay(pdMS_TO_TICKS(100));

        // Update the task deadline
        tasks[0].deadline += tasks[0].period;

        // Send the task to the task queue
        xQueueSend(taskQueue, &tasks[0], 0);
    }
}

void task2(void *pvParameters)
{
    while (1)
    {
        // Do the task
        vTaskDelay(pdMS_TO_TICKS(200));

        // Update the task deadline
        tasks[1].deadline += tasks[1].period;

        // Send the task to the task queue
        xQueueSend(taskQueue, &tasks[1], 0);
    }
}

void task3(void *pvParameters)
{
    while (1)
    {
        // Do the task
        vTaskDelay(pdMS_TO_TICKS(300));

        // Update the task deadline
        tasks[2].deadline += tasks[2].period;

        // Send the task to the task queue
        xQueueSend(taskQueue, &tasks[2], 0);
    }
}

void edfScheduler(void *pvParameters)
{
    while (1)
    {
        // Wait for a task to become available
        Task task;
        xQueueReceive(taskQueue, &task, portMAX_DELAY);

        // Calculate the earliest deadline
        TickType_t earliestDeadline = task.deadline;
        for (int i = 0; i < numTasks; i++)
        {
            if (tasks[i].deadline < earliestDeadline)
            {
                earliestDeadline = tasks[i].deadline;
            }
        }

        // Delay until the earliest deadline
        TickType_t delay = earliestDeadline - currentTime;
        vTaskDelay(delay);

        // Update the current time
        currentTime = earliestDeadline;

        // Execute the task
        task.function(NULL);

        // Update the task deadline
        task.deadline += task.period;

        // Send the task back to the task queue
        xQueueSendToFront(taskQueue, &task, 0);
    }
}

void setup()
{
    // Create the task queue
    taskQueue = xQueueCreate(numTasks, sizeof(Task));

    // Start the tasks
    for (int i = 0; i < numTasks; i++)
    {
        xTaskCreate(tasks[i].function, "Task", configMINIMAL_STACK_SIZE, NULL, priorities[i], &taskHandles[i]);
        tasks[i].handle = taskHandles[i];
        tasks[i].deadline = periods[i];
    }

    // Set the current time
    currentTime = xTaskGetTickCount();

    // Create the scheduler task
    xTaskCreate(edfScheduler, "Scheduler", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
}

void loop()
{
    // Empty loop
}

int main()
{
    setup();

    vTaskStartScheduler();

    return 0;
}

// =====

// In this example, we define a task structure that contains the task function, deadline, period, and handle. We create three tasks and define their priorities and periods. We then create a task queue to store the tasks and a scheduler task that will execute the tasks according to the EDF algorithm.

// Each task function updates its own deadline and sends itself to the task queue. The scheduler task waits for a task to become available, calculates the earliest deadline, delays until that deadline, executes the task, updates the task deadline, and sends the task back to the task queue.

// Finally, we start the FreeRTOS scheduler to run the tasks and the scheduler task.