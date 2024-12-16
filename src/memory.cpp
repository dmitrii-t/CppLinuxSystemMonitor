#include "memory.h"

#include <cmath>

float Ram::Utilization() {
  float utilization = (mem_total_ - mem_free_) / (1.f * mem_total_);
  return round(100.f * utilization) / 100.f;  // percentage
}
int Ram::TotalUsedMemory() { return mem_total_ - mem_free_; }
int Ram::NonCacheMemory() { return TotalUsedMemory() - buffers_ - cached_; }
int Ram::CachedMemory() { return cached_ + sreclaimable_ - shmem_; }
int Ram::Swap() { return swap_total_ - swap_free_; }