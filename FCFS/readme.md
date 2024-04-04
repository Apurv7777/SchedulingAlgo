# First-Come, First-Served (FCFS) Scheduling Algorithm Implementation (Using Gantt Chart)

This repository contains a C++ program that demonstrates the First-Come, First-Served (FCFS) scheduling algorithm. In this algorithm, processes are executed in the order they arrive. The program allows the user to input the number of processes along with their arrival time and burst time in milliseconds. It then generates a Gantt chart showing the order of execution of processes and calculates the Average Turnaround time and Waiting time.

## Requirements

- VSCode (Recommended)
- C++ compiler (supporting C++11 or later)
- Terminal or command prompt

## Usage

1. Clone the repository :
```
git clone https://github.com/Apurv7777/SchedulingAlgo.git
```

2. Navigate to the cloned directory :
```
cd SchedulingAlgo/FCFS
```

3. Compile the program and run the executable :
```
fcfs
```

5. Follow the prompts to enter the number of processes, arrival time, and burst time for each process (in milliseconds).

6. View the generated Gantt chart and the calculated average turnaround time and waiting time.

## Note

- If there is &Delta; symbol in the Gantt Chart, it is representing time till CPU remains idle.
  
## Constraints

- The program accepts only millisecond values for arrival time and burst time.
- Gantt chart will not be generated for processes with burst time greater than or equal to 90,000 milliseconds. The program will stop if such processes are encountered.

## Contributors

- [Apurv Panchal](https://github.com/Apurv7777)





