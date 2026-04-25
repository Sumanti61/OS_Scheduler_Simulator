# CPU Scheduling Algorithms Simulator
A C++ console application that demonstrates five classic CPU scheduling algorithms used in operating systems.
# Features
FCFS (First Come First Serve) — Processes are executed in arrival order
SJF (Shortest Job First) — Non-preemptive; selects the process with the shortest burst 96
Priority Scheduling — Non-preemptive; lower priority value = higher priority
Round Robin — Time-sliced execution with configurable quantum
SRTF (Shortest Remaining Time First) — Preemptive version of SJF
# Output
For each algorithm, the program displays:
     Gantt chart showing execution order
     Per-process metrics: Completion Time, Turnaround Time, Waiting Time
     Average Waiting Time and Turnaround Time
# Example
     Enter number of processes: 3
     AT BT Priority for P1: 0 5 2
     AT BT Priority for P2: 1 3 1
     AT BT Priority for P3: 2 4 3
     1.FCFS 2.SJF 3.Priority 4.RR 5.SRTF
     Choose: 2
