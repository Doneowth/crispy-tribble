### Problem 1

1. **Test your program without using any locks. Simulate a sequence of enqueue and dequeue operations. Comments on the results and highlights the data race problem that is expected to occur.**

     *since there is no lock involved, if we enque 0, 5, 6 with 3 threads; and deque with 2 threads, we should see one element 		remain in the queue. The data race problem here is that you can not ensure all the enque/deque calls are finished properly, which means, while the tail pointer was accessed by one of the enq threads, it is possible that one of the other thread will acquire the same tail from the memory (since all threads share the same address space), thus an enque will result in nothing get enqued;*	

​                          *![image-20230323165011989](/Users/dongliang/Library/Application Support/typora-user-images/image-20230323165011989.png)*

​     *refer to the above screen capture, we should get 6 as the only remaining element, however 5 could be printed out, since 6 is not   enqued;*



2. **Compare the performance of your program by using two locks (as in the slides) as opposed to using only one lock for both the enqueue and dequeue operations. Simulate a large number of overlapped (not sequential) enqueues and dequeues operations by all threads and use the system time (this is for simplicity as it is not the best way) to compare the performance of these two approaches. Comments on the results.**

   _According to the performance (time cost in us), the one lock approach does not show too much difference compare to the two locks approach_

   ![image-20230324155952520](/Users/dongliang/Library/Application Support/typora-user-images/image-20230324155952520.png)

   _mutex lock implementation is architecture-specific. most of the mutexes will cost almost nothing if there is native hardware support, others will cost a lot. In the above casel, we can see little difference on the performance._

3. **Why do we need a dummy node in case two locks are deployed? Support your answer by testing the code without using a dummy node.**

   *if there is no dummy node, think about this edge case, when there is only one node remains in the queue, so both the enque and deque thread can access that value, a deque would failed as an enque is not done.*

   ![image-20230324161253929](/Users/dongliang/Library/Application Support/typora-user-images/image-20230324161253929.png)

---

### Problem 2

**Test Result**

|num_threads|time_take (us)|
| --- | --- |
| 1 | 1100 |
| 2 | 1337 |
| 3 | 1100 |
| 4 | 1200 |
| 5 | 1200 |
| 6 | 1124 |
| 7 | 1388 |
| 8 | 1432 |
| 9 | 1923 |
| 10 | 1817 |

---

*screen shots provided*

![image-20230324185332112](/Users/dongliang/Library/Application Support/typora-user-images/image-20230324185332112.png)

---

### Problem 3



![IMG_3A4F5943CBD4-1](/Users/dongliang/Downloads/IMG_3A4F5943CBD4-1.jpeg)

![IMG_C33E08483615-1](/Users/dongliang/Downloads/IMG_C33E08483615-1.jpeg)
