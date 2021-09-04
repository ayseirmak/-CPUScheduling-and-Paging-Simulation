# CPUScheduling-and-Paging-Simulation
This project covers  CPU scheduling,, Memory management and Multiprogramming headings 
# Task
## Part1
Program opens the tasks.txt file (tasks list). Each line of this file represents a process that needs to be run. In each line of the file, there is a text file that needs to be loaded into memory. Each line is the representing image of the relevant process, and a list of bytes of the file. An example tasks.txt file is given in repo that contains three representative processes.
In that project, the memory size assume to be 1 MB and each frame will be 2KB (2048 B). Therefore, the memory consists of 500 frames. In turn, processes will be loaded from the tasks.txt file as long as there is space in the memory. 
For example, suppose that a.txt consists of 15 pages. In this case, there should be 15 randomly selected frames from the remaining empty frames in the page table of a.txt. If there are not enough free frames, the relevant process should not be accepted into the system. Since the next process may be smaller, tasks.txt should continue to be read. 
For instance, if b.txt does not fit, the loading process should not be interrupted and continue with c.txt.
In the simulation you can see the page table of each process as an output.
## Part2
This part is the simulation of CPU schaduling.
Let's consider the process that corresponds to a.txt in the example tasks.txt file. The following numbers in the line that are near the a.txt, are the characters (1 byte each) addresses that to be printed on the console in each memory access. 
In the example, the first access 129. chacter, the second access 200. character, the third access 1453. character, ... is printted on console. Numbering starts from 0th byte. Assume that the Scheduler dispatches each process in turn, similar to the Round robin scheduling method, and it dispatches the next process after each dispatch has exactly 10 memory accesses.
# Compile and Run
## Warning: Please reading files(a.txt,b.txt,c.txt... tasks.txt), simulation.c are found in same directory.
## How to Compile
1.	Open a shell on the machine you wish to compile on.
2.	Change directory (cd) to the directory that contains reading files and "simulation.c".
3.	Enter the following command. 

```bash
gcc simolation.c -o <output_file_simulation> 

```
## How to run
1.	Open a shell on the machine you wish to run on.
2.	Change directory (cd) to the directory that contains reading files and "simulation.c". 
3.	Enter the following command.

```bash
./<output_file_simulation>

```
## output
1.	page table of process
2.	physical memory final structer
3.	part 2 access output

## Note
if reading files size too small or too big problem may be occoured; 
please try to find appropriate size for reading file;

if you try example file that is given in hw, with frame size 15, you can see the general structer of the code
