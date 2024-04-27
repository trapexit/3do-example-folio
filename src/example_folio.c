/*
  ISC License

  Copyright (c) 2024, Antonio SJ Musumeci <trapexit@spawn.link>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "example_folio.h"
#include "version.h"

#include "svc_funcs.h"

#include "hardware_addrs.h"
#include "kernel.h"
#include "kernelnodes.h"
#include "operror.h"
#include "stdio.h"
#include "types.h"

static i32  _ExampleFolioInit(ExampleFolio*);
static i32  _ExampleFolioOpen(ExampleFolio*);
static void _ExampleFolioClose(ExampleFolio*);
static i32  _ExampleFolioDelete(ExampleFolio*);
static i32  _AddI32(i32,i32);
static i32  _SubI32(i32,i32);
static i32  _SWI_AddI32(i32,i32);
static i32  _SWI_SubI32(i32,i32);
static u32  _SWI_MADAMRev(void);
static u32  _SWI_CLIORev(void);

static FolioFunc FolioUserFuncs[] =
  {
    /* add new functions at the top */
    (FolioFunc)_SubI32,   /* -2, USER_SUBI32 */
    (FolioFunc)_AddI32    /* -1, USER_ADDI32 */
  };
#define NUM_USERFUNCS (sizeof(FolioUserFuncs)/sizeof(FolioFunc))

static FolioFunc FolioSWIFuncs[] =
  {
    /* add new functions at the top */
    (FolioFunc)_SWI_CLIORev,  /* 3, SWI_CLIOREV */
    (FolioFunc)_SWI_MADAMRev, /* 2, SWI_MADAMREV */
    (FolioFunc)_SWI_SubI32,   /* 1, SWI_SUBI32 */
    (FolioFunc)_SWI_AddI32    /* 0, SWI_ADDI32 */
  };
#define NUM_SWIFUNCS (sizeof(FolioSWIFuncs)/sizeof(FolioFunc))

/* Tags used when creating the Folio */
static TagArg g_FolioTags[] =
  {
    { TAG_ITEM_NAME,            (void*)"example" }, /* name of folio */
    { TAG_ITEM_PRI,             (void*)0 },
    { CREATEFOLIO_TAG_ITEM,     (void*)EXAMPLE_FOLIO },
    { CREATEFOLIO_TAG_DATASIZE, (void*)sizeof(ExampleFolio) },
    { CREATEFOLIO_TAG_NUSERVECS,(void*)NUM_USERFUNCS }, /* number of user functions */
    { CREATEFOLIO_TAG_USERFUNCS,(void*)FolioUserFuncs }, /* list of user functions */
    { CREATEFOLIO_TAG_NSWIS,    (void*)NUM_SWIFUNCS }, /* number of swi functions */
    { CREATEFOLIO_TAG_SWIS,     (void*)FolioSWIFuncs }, /* list of swi functions */
    { CREATEFOLIO_TAG_INIT,     (void*)_ExampleFolioInit },
    { CREATEFOLIO_TAG_OPENF,    (void*)_ExampleFolioOpen },
    { CREATEFOLIO_TAG_CLOSEF,   (void*)_ExampleFolioClose },
    { CREATEFOLIO_TAG_DELETEF,  (void*)_ExampleFolioDelete },
    { TAG_END,                  (void*)0 }, /* end of tag list */
  };

int
main(i32    argc_,
     char **argv_)
{
  Item rv;

  (void)argv_;
  if(argc_ != DEMANDLOAD_MAIN_CREATE)
    return 0;

  printf("ExampleFolio: version='%s'\n",VERSION);
  rv = CreateItem(MKNODEID(KERNELNODE,FOLIONODE),g_FolioTags);
  if(rv >= 0)
    {
      printf("ExampleFolio: item=%x\n",rv);
    }
  else
    {
      printf("ExampleFolio: creation failed - ");
      PrintfSysErr(rv);
    }

  return (int)rv;
}

static
i32
_ExampleFolioInit(ExampleFolio *ef_)
{
  svc_kprintf("ExampleFolioInit: ef=%p\n",ef_);

  return 0;
}

static
i32
_ExampleFolioOpen(ExampleFolio *ef_)
{
  svc_kprintf("ExampleFolioOpen: ef=%p\n",ef_);

  return 0;
}

static
void
_ExampleFolioClose(ExampleFolio *ef_)
{
  svc_kprintf("ExampleFolioClose: ef=%p\n",ef_);
}

static
i32
_ExampleFolioDelete(ExampleFolio *ef_)
{
  svc_kprintf("ExampleFolioDelete: ef=%p\n",ef_);

  return 0;
}

static
i32
_AddI32(i32 n0_,
        i32 n1_)
{
  return (n0_ + n1_);
}

static
i32
_SubI32(i32 n0_,
        i32 n1_)
{
  return (n0_ - n1_);
}

static
i32
_SWI_AddI32(i32 n0_,
            i32 n1_)
{
  return (n0_ + n1_);
}

static
i32
_SWI_SubI32(i32 n0_,
            i32 n1_)
{
  return (n0_ - n1_);
}

static
u32
_SWI_MADAMRev(void)
{
  return *(vu32*)MADAM_ADDR;
}

static
u32
_SWI_CLIORev(void)
{
  return *(vu32*)CLIO_ADDR;
}
