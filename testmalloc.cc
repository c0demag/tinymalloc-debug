#include "tinymalloc.h"
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <map>

#define SIZE (1048576*16)
extern "C" {

fle __tmalloc_freelist = 0;
char __tmalloc_start[SIZE];
char * __tmalloc_end;

void init_tmalloc()
{
  __tmalloc_end = (char*) (__tmalloc_start + SIZE);
  __tmalloc_freelist = (fle) &__tmalloc_start;
  __tmalloc_freelist->size = SIZE;
  __tmalloc_freelist->next = NULL;
}

}

struct buffer
{
  unsigned short* data;
  unsigned short size;
};


int main(int argc, char* argv[]) 
{
  init_tmalloc();
  std::map<unsigned, buffer> bufs;

  const int ALLOC = 0, VERIF = 1, DEALLOC = 2;

  for(unsigned i=0; i != 10000; i++) {
    const int op = rand() % 3;
    if (op == ALLOC) {
      unsigned id = rand();
      while (bufs.find(id) != bufs.end()) {
        id = rand();
      }
      unsigned short size = rand() % 65535;
      unsigned short* data = (unsigned short*) tmalloc(size*sizeof(unsigned short));
      if (data == NULL) continue;
      for (unsigned i=0; i != size; i++) {
        data[i] = (unsigned short)(size+i);
      }
      buffer buf = { data, size };
      bufs[id] = buf;
      std::cout << "alloc[" << id << "]; size=" << size << std::endl;
    } else if(op == DEALLOC) {
      if (bufs.size() == 0) continue;
      auto it = bufs.begin();
      unsigned id = it->first;
      buffer buf = it->second;
      bufs.erase(it);
      std::cout << "dealloc[" << id << "]; size=" << buf.size << std::endl;
      for (unsigned i=0; i != buf.size; i++) {
        assert(buf.data[i] == (unsigned short)(buf.size + i));
      }
      tfree(buf.data);
    }
  }
  return 0;
}
