#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;


class Process {
private:
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    string state;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int memory_required;
    bool io_operations;

public:
    //contructor
    Process(int id, int arrival, int burst, int prio = 0, int memory = 0, bool io = false)
        : pid(id), arrival_time(arrival), burst_time(burst), priority(prio), state("NEW"), remaining_time(burst), waiting_time(0), turnaround_time(0), memory_required(memory), io_operations(io) {}

    //Getters
    int getPID() const {
        return pid;
    }
    int getArrival_time() const {
        return arrival_time;
    }
    int getBurst_time() const {
        return burst_time;
    }
    int getPriority() const {
        return priority;
    }
    string getState() const {
        return state;
    }
    int getRemaining_time() const {
        return remaining_time;
    }
    int getWaiting_time() const {
        return waiting_time;
    }
    int getTurnaround_time() const {
        return turnaround_time;
    }
    int getMemory_required() const {
        return memory_required;
    }
    bool hasIo_operations() const {
        return io_operations;
    }

    //Setters

    void setState(const string& newState) {
        state = newState;
    }
    void setWaitingTime(int time) {
        waiting_time = time;
    }
    void setTuraroundTime(int time) {
        turnaround_time = time;
    }

    //Update Process state
    void updateState(const string& newState) {
        state = newState;
    }
    

    // Decrease remaining execution time
    void execution_time(int time) {
        
        if (remaining_time > 0) {
            int Create = rand() & 101;
            if (Create == remaining_time) {
                create();
            }
            remaining_time -= time;
            if (remaining_time <= 0) {
                remaining_time = 0;
                state = "TERMINATED";
            }
        }

    }
    // Display process details 
    void display() const {
        cout << "PID: " << pid << ", State: " << state
            << ", Arrival Time: " << arrival_time
            << ", Burst Time: " << burst_time
            << ", Remaining Time: " << remaining_time
            << ", Waiting Time: " << waiting_time
            << ", Turnaround Time: " << turnaround_time
            << ", Memory Required: " << memory_required
            << ", IO Operations: " << (io_operations ? "Yes" : "No") << endl;
    }

    
    queue <Process> processQ;

    void create() {
        int list;
        Process process(rand() % 101, list, rand() % 101, rand() % 11, 512, false);
        processQ.push(process);
        list += list;
    }
    
};




