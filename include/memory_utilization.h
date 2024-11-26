#pragma once

struct MemoryUtilization {

  int64_t TotalUsedMemory() {
    return MemTotal - MemFree;
  }

  int64_t NonCacheMemory() {
    return  TotalUsedMemory() - Buffers - Cached;  
  }

  int64_t CachedMemory() {
    return Cached + SReclaimable - Shmem;
  }

  int64_t Swap() {
    return SwapTotal - SwapFree;  
  }

  int64_t MemTotal;
  int64_t MemFree;
  int64_t MemAvailable;
  int64_t Buffers;
  int64_t Cached;
  int64_t SReclaimable;
  int64_t Shmem;
  int64_t SwapFree;
  int64_t SwapTotal;
};