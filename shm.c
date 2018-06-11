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

int i = 0; 
  
acquire(&(shm_table.lock)); // make sure nothing weird happens with both writing to the table at the same time
  
for (i = 0; i < 64; i++)
{
  if (shm_table.shm_pages[i].id == id)
    break;
}
 
// if i == 64, the id was not found
// otherwise, the id is at index i

if (i != 64) // id exists // is probably good
{
  
  //use mappages to add the mapping between the va and pa
  mappages(myproc()->pgdir, PGROUNDUP(myproc()->sz), PGSIZE, V2P(shm_table.shm_pages[i].frame), PTE_W|PTE_U); // perm writeable and accessible to user
 
  //pointer that will be returned through the function call
  *pointer = (char *)myproc()->sz;
  
  //increase the reference count
  shm_table.shm_pages[i].refcnt = shm_table.shm_pages[i].refcnt + 1;
  
  //update sz
  myproc()->sz = PGROUNDUP(myproc()->sz) + PGSIZE;
}
else // id doesn't exist already, need to make it
{
  //allocate a page
  
  //map it
  
  //store this information in the shm_table
  
}

// make sure to return the virtual address through the second parameter
  
release(&(shm_table.lock)); // release the lock
  
return 0; //added to remove compiler warning -- you should decide what to return
}


int shm_close(int id) {
//you write this too!

// look for the id passed in
int i = 0; 
  
acquire(&(shm_table.lock)); // make sure nothing weird happens with both writing to the table at the same time
  
for (i = 0; i < 64; i++)
{
  if (shm_table.shm_pages[i].id == id)
    break;
}
 
// if i == 64, the id was not found
// otherwise, the id is at index i

if (i != 64 && shm_table.shm_pages[i].refcnt != 0)
{
  shm_table.shm_pages[i].refcnt = shm_table.shm_pages[i].refcnt - 1;
}
else
{
  release(&(shm_table.lock)); // release in case of error
  return -1; // error
}

if (shm_table.shm_pages[i].refcnt == 0) // clear the table entry
{
  shm_table.shm_pages[i].id = 0;
  shm_table.shm_pages[i].frame = 0;
  shm_table.shm_pages[i].refcnt = 0;
}
  
release(&(shm_table.lock)); // now that everything is taken care of, someone else can look at this table

return 0; //added to remove compiler warning -- you should decide what to return
}
