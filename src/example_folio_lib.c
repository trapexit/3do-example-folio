#include "example_folio.h"
#include "version.h"

#include "folio.h"
#include "kernel.h"
#include "kernelnodes.h"
#include "nodes.h"
#include "types.h"

static Folio *g_ExampleFolioBase;


Err
OpenExampleFolio(void)
{
  Item item;
  
  printf("OpenExampleFolio: version='%s'\n",VERSION);
  item = FindAndOpenFolio("example");
  printf("OpenExampleFolio: FindAndOpenFolio(\"example\") = %x\n",item);
  if(item < 0)
    return (Err)item;

  g_ExampleFolioBase = (Folio*)LookupItem(item);

  return 0;
}

Err
CloseExampleFolio(void)
{
  Err err;

  err = CloseItem(g_ExampleFolioBase->fn.n_Item);

  printf("CloseExampleFolio: CloseItem(item) = %x\n",err);

  return err;
}

i32
AddI32(i32 n0_,
       i32 n1_)
{
  i32 result;

  CallFolioRet(g_ExampleFolioBase, USER_ADDI32, (n0_, n1_), result, (i32));

  return result;
}

i32
SubI32(i32 n0_,
       i32 n1_)
{
  int32 result;

  CallFolioRet(g_ExampleFolioBase, USER_SUBI32, (n0_, n1_), result, (i32));

  return result;
}
