#include "param.h"
#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct shm_page {
    uint id;
    char *frame;
    int refcnt;
  } shm_pages[64];
} shm_table;

void shminit() {
  int i;
  initlock(&(shm_table.lock), "SHM lock");
  acquire(&(shm_table.lock));
  for (i = 0; i< 64; i++) {
    shm_table.shm_pages[i].id =0;
    shm_table.shm_pages[i].frame =0;
    shm_table.shm_pages[i].refcnt =0;
  }
  release(&(shm_table.lock));
}

int shm_open(int id, char **pointer) {

//you write this
//*********** CS 153
uint ID_Exist = 0;
for (i = 0; i< 64; i++) {
    if (shm_table.shm_pages[i].id == id) {//Exists
      shm_table.shm_pages[i].refcnt++;
      ID_Exist = 1;
      i = 64;
    }
    else if (i == 63) {//Does not exist
      //kalloc(id);
      //memset;
      //shm_table.shm_pages[?] = 1;
    }
}
  
//if (!ID_Exist) {
  
  
//**********



return 0; //added to remove compiler warning -- you should decide what to return
}


int shm_close(int id) {
//you write this too!




return 0; //added to remove compiler warning -- you should decide what to return
}
