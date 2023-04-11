### Problem 01

---

**a. Test whether both the child and parent can access the same physical file using the**
**descriptor returned by open(). Explain why (given that the parent and child each**
**has their own stack and data segments)**

When a file is opened by a process, the operating system creates an entry in the file table, which contains information about the file, such as the file position and mode. Both parent and child process can get the file descriptor from open(); the fd(file descriptor) received from **open()** will be stored in the stack of both children and parent; since each process have their own stack, so they can read and write the fd at the same time.  

In conclusion, child process is created by forking the parent process, the child process inherits a copy of the file table entries of the parent process, including the file descriptor returned by the  **open()** call. As the below screenshot showed that both process are done, and both of them wrote their message into the file successfully.

However, there are still risks listed below in the answer part of **question b**.

![image-20230410170026038](/Users/dongliang/Library/Application Support/typora-user-images/image-20230410170026038.png)

![image-20230410195633513](/Users/dongliang/Library/Application Support/typora-user-images/image-20230410195633513.png)

**b. What happens when both the parent and the child are writing to the file
concurrently?** 

1. The data may be **interleaved**: The data from both processes may be mixed together in an unpredictable way, resulting in corrupted or garbled data.
2. The data may be **overwritten**: If both processes write to the same location within the file, the data from one process may overwrite the data from the other process, resulting in lost or incomplete data. *(not seen in the test program)*
3. The file may become **inconsistent**: If both processes update different parts of the file, the resulting file may not make sense or may be inconsistent. (very common drawbacks)

when set the **ITER_NUM** to 10, the file shows like:

![image-20230410200728393](/Users/dongliang/Library/Application Support/typora-user-images/image-20230410200728393.png)

![image-20230410200755720](/Users/dongliang/Library/Application Support/typora-user-images/image-20230410200755720.png)



According to the screen capture: we see the loop enhanced version is working correctly, and we did see the inconsistancy of the data writing to the file. All the data are interleaved as they all mixed up even all the contents are there.

### Problem 02

---

**CMD list:** 

- [x] info:  ```stat(file, &file_stat)``` call will gather all the info(inode, permission, size) we need per file while store them in the ```file_stat``` struct, and we use bit operation to mask them out(for permission), and finally interpret them into **R/W/X** format;

- [x] softlink/hardlink: use system call ```symlink(src, dest)``` and ```link(src, dest)``` to implement, set a wrapper around the user call;

- [x] rm: you can do either ```unlink()``` or ```remove()``` to implement the remove part, also use ```S_ISDIR(file_stat.st_mode)```to determine if the given file is a directroy;

**Test cmd screenshot provided:**

![image-20230410155026892](/Users/dongliang/Library/Application Support/typora-user-images/image-20230410155026892.png)