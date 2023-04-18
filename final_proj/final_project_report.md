### Part 1 - Shell

---





### Part 2 - xv6 Extension

1. Add `priority`  attr to proc in `proc.h`;

   ![image-20230418140845805](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418140845805.png)

2. Add iteration through priority in scheduler, 3 priority levels range from 0 to 2;

![image-20230418141334034](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418141334034.png)

3. implement renice(), renice should take pid to recognize process, and the priority it expected as a second paremeter, we also need to add a wrapper for renice(), as sys_renice() should serve as a sys call;

   ![image-20230418141611625](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418141611625.png)

   ![image-20230418142255789](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418142255789.png)

4. add syscall signature in `syscall.c`, `def.h`, and `syscall.h`

   ![image-20230418141659080](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418141659080.png)

​	

![image-20230418141717500](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418141717500.png)

![image-20230418142129986](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418142129986.png)

5. add a test for the renice() syscall, we use fork to generate new child processes, and set new priority to them based on RR, print the info for process priority and iteration time after the `renice()` promotion;

![image-20230418143243661](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418143243661.png)

6. Makefile change (add _mlfq);

![image-20230418143406556](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418143406556.png)

7. Screen capture for compile and exec result;

   ![image-20230418143516742](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418143516742.png)

![image-20230418143544636](/Users/dongliang/Library/Application Support/typora-user-images/image-20230418143544636.png)