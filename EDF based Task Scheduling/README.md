## Resources on EDF

**FreeRTOS related**:
- https://www.freertos.org/implementation/a00008.html

- https://www.digikey.com/en/maker/projects/introduction-to-rtos-solution-to-part-3-task-scheduling/8fbb9e0b0eed4279a2dd698f02ce125f
So can we do it in like Arduino IDE. just create functions that can schedule or do we have to use FreeRTOS cause am not able to fix dependencies errors

- Good overview on types of scheduling algorithms [pdf](resources/TypesOfSchedulingAlgorithms-umich.pdf)
    - Priority Inversion seems trivial especially for our EINSat use.. like sat might need some time to let's say take reading of battery, which will be handled by a subfunction. 
    - Unless we add manual delay there does not seem to be an efficient and continous way..
    - The task will have to be paused, run the other "task" (function) get output and then resume the current task.
- Interesting task scheduling method (round robin) - https://www.javatpoint.com/os-round-robin-scheduling-algorithm
    I believe most modern day kernels use this

- Efficient / Naive EDF [pdf page no 28](resources/Efficient%20Scheduling%20Library%20-%20Robin%20Kase.pdf)
    Did not quite understand the difference
    
- Scheduling tasks based on how much power it consumes. [pdf](resources/Making%20FreeRTOS%20-%20Energy%20Saving%20Technique.pdf)
    Might be useful for EINSat usecase of having limited power, but microcontrollers also don't take up a lot of power
    Also could use deep sleep, and only awake the main core on interrupts (while taking luminosity observation or something)



**How to EDF (code)**

- https://link.springer.com/article/10.1007/s10617-023-09267-7#Sec7

- https://github.com/sachin-ik/EDF_FreeRTOS

- Uses STM32 and goes over how to do EDF based scheduling on free rtos [pdf page 36](resources/Implementation%20and%20Test%20of%20EDF%20and%20LLREF.pdf)

- https://github.com/mohamed-arafa/Embedded_Sprints_Tasks/tree/main/RTOS_Tasks/Final%20Project


## Others

*Preemptive scheduling* seems super intersting
> "Preemptive scheduling is a popular and elegant scheduling mechanism. A simple view of how it works is to picture a timer interrupt that happens at a fixed rate. Each time the interrupt happens the interrupt service routine (ISR) switches the stack to a stack for another task, and when it returns from the ISR it returns to another task. From the task’s point of view it is periodically interrupted and it just takes a while before control is returned to it."