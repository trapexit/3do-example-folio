#include "example_folio.h"

#include "stdio.h"
#include "kernel.h"
#include "operror.h"

int
main(int    argc_,
     char **argv_)
{
  Err err;
  i32 x;

  printf("bootstrap: task = %p\n",
         KernelBase->kb_CurrentTask);
  printf("bootstrap: super = %d\n",
         !!(KernelBase->kb_CurrentTask->t.n_Flags & TASK_SUPER));

  err = OpenExampleFolio();
  printf("bootstrap: OpenExampleFolio() = %p\n",err);
  PrintfSysErr(err);

  x = AddI32(5,7);
  printf("bootstrap: AddI32(5,7) = %d\n",x);

  x = SWIAddI32(5,7);
  printf("bootstrap: SWIAddI32(5,7) = %d\n",x);

  x = AddI32(5,7);
  printf("bootstrap: AddI32(5,7) = %d\n",x);

  return 0;
}
