#pragma once

#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <vector>
#include <unordered_map>
#include "Process.h"
#include <queue>
using namespace std;

struct PageTableEntry {
    bool valid;
    int frameNumber;
    bool dirty;
};

class VirtualMemoryManager {
private:
    int page_size;
    int physical_memory_size;
    int virtual_memory_size;
    int frame_count;
    queue<Process> processQueue;
    vector<bool> frame_usage; // Tracks frame allocation (true = used, false = free)
    unordered_map<int, unordered_map<int, PageTableEntry>> process_page_tables; // processID -> (pageNum -> PageTableEntry)

public:
    VirtualMemoryManager(int virtualSizeKB, int physicalSizeKB, int pageSizeKB);
    int translateAddress(int logicalAddress, Process& proc) ;  // Takes Process reference
    bool handlePageFault(Process& proc, int pageNumber) ;  // Handles page fault
    void printPageTable(int processID) const;
};

#endif
