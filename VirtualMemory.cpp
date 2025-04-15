#include "VirtualMemory.h"
#include "Process.h"
#include <iostream>
using namespace std;

VirtualMemoryManager::VirtualMemoryManager(int virtualSizeKB, int physicalSizeKB, int pageSizeKB) {
    page_size = pageSizeKB;
    virtual_memory_size = virtualSizeKB;
    physical_memory_size = physicalSizeKB;

    frame_count = physical_memory_size / page_size;
    frame_usage.resize(frame_count, false); // Track frame usage (true = used, false = free)
}

int VirtualMemoryManager::translateAddress(int logicalAddress, Process& proc) {
    int pageNum = logicalAddress / page_size;  // Extract page number from logical address
    int offset = logicalAddress % page_size;

    if (pageNum >= virtual_memory_size / page_size) {
        cerr << "Page number out of range\n";
        return -1;
    }

    auto& pageTable = process_page_tables[proc.getPID()];  // Get the page table for the current process
    auto it = pageTable.find(pageNum);  // Try to find the page

    // If page is not found or is invalid, handle page fault
    if (it == pageTable.end() || !it->second.valid) {
        cout << "Page fault for Process " << proc.getPID() << " at page " << pageNum << "\n";
        if (!handlePageFault(proc, pageNum)) {
            cerr << "Page fault handling failed\n";
            return -1;
        }
    }

    // Reload reference in case page was just added
    PageTableEntry& entry = process_page_tables[proc.getPID()][pageNum];
    return entry.frameNumber * page_size + offset;
}

bool VirtualMemoryManager::handlePageFault(Process& proc, int pageNum) {
    for (int i = 0; i < frame_count; ++i) {
        if (!frame_usage[i]) {
            // Assign frame to this process
            process_page_tables[proc.getPID()][pageNum] = { true, i, false }; // valid, frame, dirty
            frame_usage[i] = true;  // Mark frame as used

            cout << "Process " << proc.getPID() << ": Loaded virtual page " << pageNum
                << " into physical frame " << i << "\n";
            return true;
        }
    }

    cerr << "No free physical memory frames available\n";
    return false;
}

void VirtualMemoryManager::printPageTable(int processID) const {
    // Find the page table for the given process ID
    auto it = process_page_tables.find(processID);
    if (it == process_page_tables.end()) {
        cout << "No page table found for Process " << processID << "\n";
        return;
    }

    const auto& table = it->second;  // Reference to the page table for the process
    cout << "Page Table for Process " << processID << ":\n";

    // Use an iterator to loop through the page table
    for (auto iter = table.begin(); iter != table.end(); ++iter) {
        int pageNum = iter->first;          // The page number (key)
        const PageTableEntry& entry = iter->second;  // The page table entry (value)

        cout << "Page " << pageNum << ": ";
        if (entry.valid)
            cout << "Frame " << entry.frameNumber << "\n";
        else
            cout << "Invalid\n";
    }
}
