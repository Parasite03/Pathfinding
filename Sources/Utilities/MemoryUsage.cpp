#include "MemoryUsage.h"
#include <Psapi.h>

double GetVirtualMemoryUsage()
{
	PROCESS_MEMORY_COUNTERS mem_counter;
	BOOL result = GetProcessMemoryInfo(GetCurrentProcess(),
		&mem_counter,
		sizeof(mem_counter));
	return mem_counter.WorkingSetSize / 1048576;
}