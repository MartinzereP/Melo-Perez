#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Process{
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
    : pid(id), arrival_time(arrival), burst_time(burst), priority(prio), state("NEW")
    remaining_time(bust), waiting_time(0), turnaround_time(0), memory_required(memory), io_operations(io){}

//Getters
int getPID() const{
    return pid;
}
int getArrival_time() const{
    return arrival_time;
}
int getBurst_time() const{
    return burst_time;
}
int getPriority() const{
    return priority;
}
string getState() const{
    return state:
}
int getRemaining_time() const{
    return remaining_time;
}
int getWaiting_time() const{
    return waiting_time;
}
int getTurnaround_time() const{
    return turnaround_time;
}
int getMemory_required() const{
    return memory_required;
}
bool hasIo_operations() const{
    return io_operations;
}

//Setters

void setState(const string& newState) {
    state = newState;
}
void setWaitingTime(int time){
    waiting_time = time;
}
void setTuraroundTime(int time){
    turnaround_time = time;
}

//Update Process state
void updateState(const string& newState){
    state = newState;
}

 
}



main() {

  cout << "Hello" << endl;


    return 0;
}