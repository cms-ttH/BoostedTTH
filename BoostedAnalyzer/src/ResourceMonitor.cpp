#include "BoostedTTH/BoostedAnalyzer/interface/ResourceMonitor.hpp"

ResourceMonitor::ResourceMonitor(){
  PID=(long)getpid();
  std::cout<<"this process pid" << PID<<std::endl;
  procfilename="/proc/";
  procfilename+=std::to_string(PID);
  procfilename+="/status";
}

ResourceMonitor::~ResourceMonitor(){}

void ResourceMonitor::PrintMemoryUsage(){
  std::ifstream procFile;
  procFile.open(procfilename);
  std::string buffer;
  std::string sVMsize;
  bool lastWasVMsize=false;
//   std::cout<<procfilename<<std::endl;
  
  while(!procFile.eof()){
    procFile>>buffer;
//     std::cout<<buffer<<std::endl;
//         break;

    if(lastWasVMsize){
      sVMsize=buffer;
      lastWasVMsize=false;
    }
    if(buffer.find("VmSize")!=std::string::npos){
      lastWasVMsize=true;
    }
    else{
      lastWasVMsize=false;
    }
  }
  
  std::cout<<"Memory Usage"<<std::endl;
  std::cout<<"VMsize "<<sVMsize<<std::endl;
  procFile.close();
}

void ResourceMonitor::PrintSystemMemory(){
  std::ifstream meminfoFile;
  meminfoFile.open("/proc/meminfo");
  std::string buffer;
  std::string sFreeMem="0";
  std::string sTotalMem="0";
  std::string sBufferedMem="0";
  std::string sCachedMem="0";
  
  bool lastWasMEMTotal=false;
  bool lastWasMEMFree=false;
  bool lastWasMEMBuffered=false;
  bool lastWasMEMCached=false;
  
//   std::cout<<procfilename<<std::endl;
  
  while(!meminfoFile.eof()){
    meminfoFile>>buffer;
//     std::cout<<buffer<<std::endl;
//         break;

    if(lastWasMEMFree){
      sFreeMem=buffer;
      lastWasMEMFree=false;
    }
    if(lastWasMEMTotal){
      sTotalMem=buffer;
      lastWasMEMTotal=false;
    }
    if(lastWasMEMBuffered){
      sBufferedMem=buffer;
      lastWasMEMBuffered=false;
    }
    if(lastWasMEMCached){
      sCachedMem=buffer;
      lastWasMEMCached=false;
    }
    if(buffer.find("MemTotal")!=std::string::npos){
      lastWasMEMTotal=true;
    }
    else if(buffer.find("MemFree")!=std::string::npos){
      lastWasMEMFree=true;
    }
    else if(buffer.find("Buffers")!=std::string::npos){
      lastWasMEMCached=true;
    }
    else if(buffer.find("Cached")!=std::string::npos){
      lastWasMEMBuffered=true;
    }
    else{
      lastWasMEMFree=false;
      lastWasMEMTotal=false;
      lastWasMEMBuffered=false;
      lastWasMEMCached=false;
      
    }
  }
  
  long realFree = std::stol(sFreeMem) - std::stol(sBufferedMem) + std::stol(sCachedMem);
  std::cout<<"Total system memory: "<<sTotalMem<<std::endl;
  std::cout<<"Free system memory: "<<realFree<<std::endl;
  meminfoFile.close();
}
  
  
    
