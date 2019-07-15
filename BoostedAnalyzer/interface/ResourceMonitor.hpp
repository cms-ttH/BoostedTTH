#ifndef RESOURCEMONITOR_HPP
#define RESOURCEMONITOR_HPP

#include <unistd.h>
// #include <types.h>
#include <iostream>
#include <fstream>

class ResourceMonitor {
 public:
  ResourceMonitor();
  ~ResourceMonitor();
  void PrintMemoryUsage();
  void PrintSystemMemory();

 private:
  long PID;
  std::string procfilename;
};

#endif
