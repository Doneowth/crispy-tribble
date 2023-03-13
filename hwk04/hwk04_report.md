### Homework 04 Report

1. syscall.h

![image-20230313092832283](/Users/dongliang/Library/Application Support/typora-user-images/image-20230313092832283.png)

​		add SYS call for date and ps;

2. usys.S

![image-20230313093126219](/Users/dongliang/Library/Application Support/typora-user-images/image-20230313093126219.png)

​		register SYS call for date and ps; thus the macro can parse the syscall;

3. syscall.c

![image-20230313093358467](/Users/dongliang/Library/Application Support/typora-user-images/image-20230313093358467.png)

​		declare syscall, and add syscall function pointer to syscall array;

4. sysproc.c

![image-20230313094538480](/Users/dongliang/Library/Application Support/typora-user-images/image-20230313094538480.png)

​			add implementation for sys_date and sys_ps to kernel source;

5. user.h

![image-20230313094654887](/Users/dongliang/Library/Application Support/typora-user-images/image-20230313094654887.png)

​			expose user-level syscall;

6. date.c

![image-20230313094813280](/Users/dongliang/Library/Application Support/typora-user-images/image-20230313094813280.png)

​		**execution for date:**

![image-20230313094913843](/Users/dongliang/Library/Application Support/typora-user-images/image-20230313094913843.png)

7. proc.c

![image-20230313095002097](/Users/dongliang/Library/Application Support/typora-user-images/image-20230313095002097.png)

​		extract info from page table(ptable), and print out;

 	8. ps.c 

![image-20230313095113067](/Users/dongliang/Library/Application Support/typora-user-images/image-20230313095113067.png)

**ps execution：**

![image-20230313095246519](/Users/dongliang/Library/Application Support/typora-user-images/image-20230313095246519.png)



**Explaination:**

the init process (pid=1) comes with the xv6 OS;

the sh process(pid=1, ppid=1) is forked from init since its ppid points to init;

the ps(pid=15) is forked from sh(pid=2), and it is running as the sh displayed;

the ps(pid=16) is forked from ps(pid=15), since it is from the parent ps, so its state is runnable;

