#pragma once

// Represens system memory data
class Ram {
 public:
  Ram(long int mem_total, long int mem_free, long int mem_available,
      long int buffers, long int cached, long int sreclaimable, long int shmem,
      long int swap_free, long int swap_total)
      : mem_total_(mem_total),
        mem_free_(mem_free),
        mem_available_(mem_available),
        buffers_(buffers),
        cached_(cached),
        sreclaimable_(sreclaimable),
        shmem_(shmem),
        swap_free_(swap_free),
        swap_total_(swap_total) {}

  Ram() {}

  float Utilization();
  int TotalUsedMemory();
  int NonCacheMemory();
  int CachedMemory();
  int Swap();

 private:
  long int mem_total_;
  long int mem_free_;
  long int mem_available_;
  long int buffers_;
  long int cached_;
  long int sreclaimable_;
  long int shmem_;
  long int swap_free_;
  long int swap_total_;
};