/*-------------------------------------------------------------------------
  peep.c - source file for peephole optimizer helper functions

  Written By -  Philipp Klaus Krause

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2, or (at your option) any
  later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

  In other words, you are welcome to use, share and improve this program.
  You are forbidden to forbid anyone else to use, share and improve
  what you give them.   Help stamp out software-hoarding!
-------------------------------------------------------------------------*/

#include "common.h"
#include "SDCCicode.h"
#include "z80.h"
#include "SDCCglobl.h"
#include "SDCCpeeph.h"
#include "gen.h"

#define NOTUSEDERROR() do {werror(E_INTERNAL_ERROR, __FILE__, __LINE__, "error in notUsed()");} while(0)

/*#define D(_s) { printf _s; fflush(stdout); }*/
#define D(_s)

#define ISINST(l, i) (!strncmp((l), (i), sizeof(i) - 1))

typedef enum
{
  S4O_CONDJMP,
  S4O_WR_OP,
  S4O_RD_OP,
  S4O_TERM,
  S4O_VISITED,
  S4O_ABORT,
  S4O_CONTINUE
} S4O_RET;

static struct
{
  lineNode *head;
} _G;

/*-----------------------------------------------------------------*/
/* univisitLines - clear "visited" flag in all lines               */
/*-----------------------------------------------------------------*/
static void
unvisitLines (lineNode *pl)
{
  for (; pl; pl = pl->next)
    pl->visited = FALSE;
}

#define AOP(op) op->aop
#define AOP_SIZE(op) AOP(op)->size

static bool
isReturned(const char *what)
{
  symbol *sym;
  sym_link *sym_lnk;
  int size;
  lineNode *l;

  if(strncmp(what, "iy", 2) == 0)
    return FALSE;
  if(strlen(what) != 1)
    return TRUE;

  l = _G.head;
  do
  {
    l = l->next;
  } while(l->isComment || l->ic == NULL || l->ic->op != FUNCTION);

  sym = OP_SYMBOL(IC_LEFT(l->ic));

  if(sym && IS_DECL(sym->type))
    {
      // Find size of return value.
      specifier *spec;
      if(sym->type->select.d.dcl_type != FUNCTION)
        NOTUSEDERROR();
      spec = &(sym->etype->select.s);
      if(spec->noun == V_VOID)
        size = 0;
      else if(spec->noun == V_CHAR || spec->noun == V_BOOL)
        size = 1;
      else if(spec->noun == V_INT && !(spec->b_long))
        size = 2;
      else
        size = 4;

      // Check for returned pointer.
      sym_lnk = sym->type;
      while (sym_lnk && !IS_PTR (sym_lnk))
        sym_lnk = sym_lnk->next;
      if(IS_PTR(sym_lnk))
        size = 2;
    }
  else
    {
      NOTUSEDERROR();
      size = 4;
    }

  switch(*what)
    {
    case 'd':
      return(size >= 4);
    case 'e':
      return(size >= 3);
    case 'h':
      return(size >= 2);
    case 'l':
      return(size >= 1);
    default:
      return FALSE;
    }
}

/*-----------------------------------------------------------------*/
/* incLabelJmpToCount - increment counter "jmpToCount" in entry    */
/* of the list labelHash                                           */
/*-----------------------------------------------------------------*/
static bool
incLabelJmpToCount (const char *label)
{
  labelHashEntry *entry;

  entry = getLabelRef (label, _G.head);
  if (!entry)
    return FALSE;
  entry->jmpToCount++;
  return TRUE;
}

/*-----------------------------------------------------------------*/
/* findLabel -                                                     */
/* 1. extracts label in the opcode pl                              */
/* 2. increment "label jump-to count" in labelHash                 */
/* 3. search lineNode with label definition and return it          */
/*-----------------------------------------------------------------*/
static lineNode *
findLabel (const lineNode *pl)
{
  char *p;
  lineNode *cpl;

  /* 1. extract label in opcode */

  /* In each mcs51 jumping opcode the label is at the end of the opcode */
  p = strlen (pl->line) - 1 + pl->line;

  /* scan backward until ',' or '\t' */
  for (; p > pl->line; p--)
    if (*p == ',' || *p == '\t')
      break;

  /* sanity check */
  if (p == pl->line)
    {
      NOTUSEDERROR();
      return NULL;
    }

  /* skip ',' resp. '\t' */
  ++p;

  /* 2. increment "label jump-to count" */
  if (!incLabelJmpToCount (p))
    return NULL;

  /* 3. search lineNode with label definition and return it */
  for (cpl = _G.head; cpl; cpl = cpl->next)
    {
      if (   cpl->isLabel
          && strncmp (p, cpl->line, strlen(p)) == 0)
        {
          return cpl;
        }
    }
  return NULL;
}

/* Check if reading arg implies reading what. */
static bool argCont(const char *arg, const char *what)
{
  return (arg[0] == '#') ? FALSE : strstr(arg, what) != NULL;
}

static bool
z80MightRead(const lineNode *pl, const char *what)
{
  if(strcmp(what, "iyl") == 0 || strcmp(what, "iyh") == 0)
    what = "iy";
  if(strcmp(what, "ixl") == 0 || strcmp(what, "ixh") == 0)
    what = "ix";

  if(strcmp(pl->line, "call\t__initrleblock") == 0)
    return TRUE;

  if(strcmp(pl->line, "call\t__sdcc_call_hl") == 0 && (strchr(what, 'h') != 0 || strchr(what, 'l') != 0))
    return TRUE;

  if(strncmp(pl->line, "call\t", 5) == 0 && strchr(pl->line, ',') == 0)
    return FALSE;

  if(ISINST(pl->line, "ret") && !isReturned(what))
    return FALSE;

  if(strcmp(pl->line, "ex\t(sp),hl") == 0 && strchr(what, 'h') == 0 && strchr(what, 'l') == 0)
    return FALSE;
  if(strcmp(pl->line, "ex\tde,hl") == 0 && strchr(what, 'h') == 0 && strchr(what, 'l') == 0 && strchr(what, 'd') == 0 && strchr(what, 'e') == 0)
    return FALSE;
  if(ISINST(pl->line, "ld\t"))
    {
      if(strstr(strchr(pl->line, ','), what) && strchr(pl->line, ',')[1] != '#' && !(strchr(pl->line, ',')[1] == '(' && strchr(pl->line, ',')[2] == '#') && !(strchr(pl->line, ',')[1] == '(' && strchr(pl->line, ',')[3] != ')' && strchr(pl->line, ',')[4] != ')'))
        return TRUE;
      if(*(strchr(pl->line, ',') - 1) == ')' && strstr(pl->line + 3, what) && (strchr(pl->line, '#') == 0 || strchr(pl->line, '#') > strchr(pl->line, ',')))
        return TRUE;
      return FALSE;
    }

  if(strcmp(pl->line, "xor\ta,a") == 0)
    return FALSE;

  if(ISINST(pl->line, "adc\t") ||
    ISINST(pl->line, "add\t") ||
    ISINST(pl->line, "and\t") ||
    ISINST(pl->line, "sbc\t") ||
    ISINST(pl->line, "sub\t") ||
    ISINST(pl->line, "xor\t"))
    {
      if(argCont(pl->line + 4, what))
        return TRUE;
      if(strstr(pl->line + 4, "hl") == 0 && strcmp("a", what) == 0)
        return TRUE;
      return FALSE;
    }

  if(ISINST(pl->line, "or\t") || ISINST(pl->line, "cp\t") )
    {
      if(argCont(pl->line + 3, what))
        return TRUE;
      if(strcmp("a", what) == 0)
        return TRUE;
      return FALSE;
    }

  if(ISINST(pl->line, "neg"))
    return(strcmp(what, "a") == 0);

  if(ISINST(pl->line, "pop\t"))
    return FALSE;

  if(ISINST(pl->line, "push\t"))
    return(strstr(pl->line + 5, what) != 0);

  if(
    ISINST(pl->line, "dec\t") ||
    ISINST(pl->line, "inc\t"))
    {
      return(argCont(pl->line + 4, what));
    }

  // Rotate and shift group (todo: rld rrd, maybe sll)
  if(ISINST(pl->line, "rlca") ||
     ISINST(pl->line, "rla") ||
     ISINST(pl->line, "rrca") ||
     ISINST(pl->line, "rra"))
    return(strcmp(what, "a") == 0);
  if(
    ISINST(pl->line, "rl\t") ||
    ISINST(pl->line, "rr\t"))
    {
      return(argCont(pl->line + 3, what));
    }
  if(
    ISINST(pl->line, "rlc\t") ||
    ISINST(pl->line, "sla\t") ||
    ISINST(pl->line, "sra\t") ||
    ISINST(pl->line, "srl\t"))
    {
      return(argCont(pl->line + 4, what));
    }

  // Bit set, reset and test group
  if(
    ISINST(pl->line, "bit\t") ||
    ISINST(pl->line, "set\t") ||
    ISINST(pl->line, "res\t"))
    {
      return(argCont(pl->line + 4, what));
    }

 if(ISINST(pl->line, "ccf"))
    return FALSE;

  if(strncmp(pl->line, "jp\t", 3) == 0 ||
    (bool)(strncmp(pl->line, "jr\t", 3)) == 0)
    return FALSE;

  if(ISINST(pl->line, "djnz\t"))
    return(strchr(what, 'b') != 0);

  if(ISINST(pl->line, "mlt\t"))
    return(strstr(pl->line + 4, what) != 0);

  return TRUE;
}

static bool
z80UncondJump(const lineNode *pl)
{
  if((ISINST(pl->line, "jp\t") ||
    ISINST(pl->line, "jr\t")) && strchr(pl->line, ',') == 0)
    return TRUE;
  return FALSE;
}

static bool
z80CondJump(const lineNode *pl)
{
  if(((ISINST(pl->line, "jp\t") ||
    ISINST(pl->line, "jr\t")) && strchr(pl->line, ',') != 0) ||
    ISINST(pl->line, "djnz\t"))
    return TRUE;
  return FALSE;
}

static bool
z80SurelyWrites(const lineNode *pl, const char *what)
{
  if(strcmp(what, "iyl") == 0 || strcmp(what, "iyh") == 0)
    what = "iy";
  if(strcmp(what, "ixl") == 0 || strcmp(what, "ixh") == 0)
    what = "ix";

  if(strcmp(pl->line, "xor\ta,a") == 0 && strcmp(what, "a") == 0)
    return TRUE;
  if(ISINST(pl->line, "ld\t") && strncmp(pl->line + 3, "hl", 2) == 0 && (what[0] == 'h' || what[0] == 'l'))
    return TRUE;
  if(ISINST(pl->line, "ld\t") && strncmp(pl->line + 3, "de", 2) == 0 && (what[0] == 'd' || what[0] == 'e'))
    return TRUE;
  if(ISINST(pl->line, "ld\t") && strncmp(pl->line + 3, "bc", 2) == 0 && (what[0] == 'b' || what[0] == 'c'))
    return TRUE;
  if(ISINST(pl->line, "ld\t") && strncmp(pl->line + 3, what, strlen(what)) == 0 && pl->line[3 + strlen(what)] == ',')
    return TRUE;
  if(ISINST(pl->line, "pop\t") && strstr(pl->line + 4, what))
    return TRUE;
  if(ISINST(pl->line, "call\t") && strchr(pl->line, ',') == 0  && strcmp(what, "ix"))
    return TRUE;
  if(strcmp(pl->line, "ret") == 0)
    return TRUE;
  if(ISINST(pl->line, "ld\tiy") && strncmp(what, "iy", 2) == 0)
    return TRUE;

  return FALSE;
}

static bool
z80SurelyReturns(const lineNode *pl)
{
  if(strcmp(pl->line, "\tret") == 0)
    return TRUE;
  return FALSE;
}

/*-----------------------------------------------------------------*/
/* scan4op - "executes" and examines the assembler opcodes,        */
/* follows conditional and un-conditional jumps.                   */
/* Moreover it registers all passed labels.                        */
/*                                                                 */
/* Parameter:                                                      */
/*    lineNode **pl                                                */
/*       scanning starts from pl;                                  */
/*       pl also returns the last scanned line                     */
/*    const char *pReg                                             */
/*       points to a register (e.g. "ar0"). scan4op() tests for    */
/*       read or write operations with this register               */
/*    const char *untilOp                                          */
/*       points to NULL or a opcode (e.g. "push").                 */
/*       scan4op() returns if it hits this opcode.                 */
/*    lineNode **plCond                                            */
/*       If a conditional branch is met plCond points to the       */
/*       lineNode of the conditional branch                        */
/*                                                                 */
/* Returns:                                                        */
/*    S4O_ABORT                                                    */
/*       on error                                                  */
/*    S4O_VISITED                                                  */
/*       hit lineNode with "visited" flag set: scan4op() already   */
/*       scanned this opcode.                                      */
/*    S4O_FOUNDOPCODE                                              */
/*       found opcode and operand, to which untilOp and pReg are   */
/*       pointing to.                                              */
/*    S4O_RD_OP, S4O_WR_OP                                         */
/*       hit an opcode reading or writing from pReg                */
/*    S4O_CONDJMP                                                  */
/*       hit a conditional jump opcode. pl and plCond return the   */
/*       two possible branches.                                    */
/*    S4O_TERM                                                     */
/*       acall, lcall, ret and reti "terminate" a scan.            */
/*-----------------------------------------------------------------*/
static S4O_RET
scan4op (lineNode **pl, const char *what, const char *untilOp,
         lineNode **plCond)
{
  for (; *pl; *pl = (*pl)->next)
    {
      if (!(*pl)->line || (*pl)->isDebug || (*pl)->isComment || (*pl)->isLabel)
        continue;
      D(("Scanning %s for %s\n", (*pl)->line, what));
      /* don't optimize across inline assembler,
         e.g. isLabel doesn't work there */
      if ((*pl)->isInline)
        {
          D(("S4O_RD_OP: Inline asm\n"));
          return S4O_ABORT;
        }

      if ((*pl)->visited)
        {
          D(("S4O_VISITED\n"));
          return S4O_VISITED;
        }

      (*pl)->visited = TRUE;

      if(z80MightRead(*pl, what))
        {
          D(("S4O_RD_OP\n"));
          return S4O_RD_OP;
        }

      if(z80UncondJump(*pl))
        {
          *pl = findLabel (*pl);
            if (!*pl)
              {
                D(("S4O_ABORT\n"));
                return S4O_ABORT;
              }
        }
      if(z80CondJump(*pl))
        {
          *plCond = findLabel (*pl);
          if (!*plCond)
            {
              D(("S4O_ABORT\n"));
              return S4O_ABORT;
            }
          D(("S4O_CONDJMP\n"));
          return S4O_CONDJMP;
        }

      if(z80SurelyWrites(*pl, what))
        {
          D(("S4O_WR_OP\n"));
          return S4O_WR_OP;
        }

      /* Don't need to check for de, hl since z80MightRead() does that */
      if(z80SurelyReturns(*pl))
        {
          D(("S4O_TERM\n"));
          return S4O_TERM;
        }
    }
  D(("S4O_ABORT\n"));
  return S4O_ABORT;
}

/*-----------------------------------------------------------------*/
/* doTermScan - scan through area 2. This small wrapper handles:   */
/* - action required on different return values                    */
/* - recursion in case of conditional branches                     */
/*-----------------------------------------------------------------*/
static bool
doTermScan (lineNode **pl, const char *what)
{
  lineNode *plConditional;

  for (;; *pl = (*pl)->next)
    {
      switch (scan4op (pl, what, NULL, &plConditional))
        {
          case S4O_TERM:
          case S4O_VISITED:
          case S4O_WR_OP:
            /* all these are terminating conditions */
            return TRUE;
          case S4O_CONDJMP:
            /* two possible destinations: recurse */
              {
                lineNode *pl2 = plConditional;
                D(("CONDJMP trying other branch first\n"));
                if (!doTermScan (&pl2, what))
                  return FALSE;
                D(("Other branch OK.\n"));
              }
            continue;
          case S4O_RD_OP:
          default:
            /* no go */
            return FALSE;
        }
    }
}

/* Regular 8 bit reg */
static bool
isReg(const char *what)
{
  if(strlen(what) != 1)
    return FALSE;
  switch(*what)
    {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'h':
    case 'l':
      return TRUE;
    }
  return FALSE;
}

/* 8-Bit reg only accessible by 16-bit and undocumented instructions */
static bool
isUReg(const char *what)
{
  if(strcmp(what, "iyl") == 0 || strcmp(what, "iyh") == 0)
    return TRUE;
  if(strcmp(what, "ixl") == 0 || strcmp(what, "ixh") == 0)
    return TRUE;
  return FALSE;
}

static bool
isRegPair(const char *what)
{
  if(strlen(what) != 2)
    return FALSE;
  if(strcmp(what, "bc") == 0)
    return TRUE;
  if(strcmp(what, "de") == 0)
    return TRUE;
  if(strcmp(what, "hl") == 0)
    return TRUE;
  if(strcmp(what, "sp") == 0)
    return TRUE;
  if(strcmp(what, "ix") == 0)
    return TRUE;
  if(strcmp(what, "iy") == 0)
    return TRUE;
  return FALSE;
}

/* Check that what is never read after endPl. */

bool
z80notUsed (const char *what, lineNode *endPl, lineNode *head)
{
  lineNode *pl;
  D(("Checking for %s\n", what));
  if(isRegPair(what))
    {
      char low[2], high[2];
      low[0] = what[1];
      high[0] = what[0];
      low[1] = 0;
      high[1] = 0;
      if(strcmp(what, "iy") == 0)
        {
          if(IY_RESERVED)
            return FALSE;
          return(z80notUsed("iyl", endPl, head) && z80notUsed("iyh", endPl, head));
        }
      if(strcmp(what, "ix") == 0)
        {
          if(IY_RESERVED)
            return FALSE;
          return(z80notUsed("ixl", endPl, head) && z80notUsed("ixh", endPl, head));
        }
      return(z80notUsed(low, endPl, head) && z80notUsed(high, endPl, head));
    }

  if(!isReg(what) && !isUReg(what))
    return FALSE;

  _G.head = head;

  unvisitLines (_G.head);

  pl = endPl->next;
  if (!doTermScan (&pl, what))
    return FALSE;

  return TRUE;
}

bool
z80notUsedFrom (const char *what, const char *label, lineNode *head)
{
  lineNode *cpl;

  for (cpl = _G.head; cpl; cpl = cpl->next)
    {
      if (cpl->isLabel && !strncmp (label, cpl->line, strlen(label)))
        {
          return z80notUsed (what, cpl, head);
        }
    }
  return FALSE;
}

bool
z80canAssign (const char *op1, const char *op2, const char *exotic)
{
  const char *dst, *src;

  // Indexed accesses: One is the indexed one, the other one needs to be a reg or immediate.
  if(exotic)
  {
    if(!strcmp(exotic, "ix") || !strcmp(exotic, "iy"))
    {
      if(isReg(op1))
        return TRUE;
    }
    else if(!strcmp(op2, "ix") || !strcmp(op2, "iy"))
    {
      if(isReg(exotic) || exotic[0] == '#')
        return TRUE;
    }

    return FALSE;
  }

  // Everything else.
  dst = op1;
  src = op2;

  // 8-bit regs can be assigned to each other directly.
  if(isReg(dst) && isReg(src))
    return TRUE;

  // Same if at most one of them is (hl).
  if(isReg(dst) && !strcmp(src, "(hl)"))
    return TRUE;
  if(!strcmp(dst, "(hl)") && isReg(src))
    return TRUE;

  // Can assign between a and (bc), (de)
  if(!strcmp(dst, "a") && (!strcmp(src, "(bc)") || ! strcmp(src, "(de)")))
    return TRUE;
  if((!strcmp(dst, "(bc)") || ! strcmp(dst, "(de)")) && !strcmp(src, "a"))
    return TRUE;

  // Can load immediate values directly into registers and register pairs.
  if((isReg(dst) || isRegPair(dst)) && src[0] == '#')
    return TRUE;

  if((!strcmp(dst, "a") || isRegPair(dst)) && !strncmp(src, "(#", 2))
    return TRUE;
  if(!strncmp(dst, "(#", 2) && (!strcmp(src, "a") || isRegPair(src)))
    return TRUE;

  // Can load immediate values directly into (hl).
  if(!strcmp(dst, "(hl)") && src[0] == '#')
    return TRUE;

  return FALSE;
}

int z80instructionSize(lineNode *pl)
{
  const char *op1start, *op2start;

  op1start = strchr(pl->line, '\t');
  if(op1start)
    {
      op1start++;
      op2start = strchr(op1start, ',');
      if(op2start)
        do
          op2start++;
      while(op2start && (*op2start == ' ' || *op2start == '\t'));
    }
  else
    op2start = 0;

  /* All ld instructions */
  if(ISINST(pl->line, "ld\t"))
    {
      /* These 3 are the only cases of 4 byte long ld instructions. */
      if(!strncmp(op1start, "ix", 2) || !strncmp(op1start, "iy", 2))
        return(4);
      if((argCont(op1start, "(ix)") || argCont(op1start, "(iy)")) && op2start[0] == '#')
        return(4);
      if(op1start[0] == '(' && strncmp(op1start, "(bc)", 4) &&
         strncmp(op1start, "(de)", 4) && strncmp(op1start, "(hl)", 4) &&
         strncmp(op2start, "hl", 2) && strncmp(op2start, "a", 2))
        return(4);

      if(IS_R2K && !strncmp(op1start, "hl", 2) && (argCont(op2start, "(hl)") || argCont(op2start, "(iy)")))
        return(4);
      if(IS_R2K && !strncmp(op1start, "hl", 2) && (argCont(op2start, "(sp)") || argCont(op2start, "(ix)")))
        return(3);

      /* These 4 are the only remaining cases of 3 byte long ld instructions. */
      if(argCont(op2start, "(ix)") || argCont(op2start, "(iy)"))
        return(3);
      if(argCont(op1start, "(ix)") || argCont(op1start, "(iy)"))
        return(3);
      if((op1start[0] == '(' && strncmp(op1start, "(bc)", 4) && strncmp(op1start, "(de)", 4) && strncmp(op1start, "(hl)", 4)) ||
         (op2start[0] == '(' && strncmp(op1start, "(bc)", 4) && strncmp(op1start, "(de)", 4) && strncmp(op1start, "(hl)", 4)))
        return(3);
      if((op1start[1] == 'c' || op1start[1] == 'd' || op1start[1] == 'l' || op1start[1] == 'p') && op2start[0] == '#')
        return(3);

      /* These 3 are the only remaining cases of 2 byte long ld instructions. */
      if(op2start[0] == '#')
        return(2);
      if(op1start[0] == 'i' || op1start[0] == 'r' || op2start[0] == 'i' || op2start[0] == 'r')
        return(2);
      if(!strncmp(op2start, "ix", 2) || !strncmp(op2start, "iy", 2))
        return(2);

      /* All other ld instructions */
      return(1);
    }

  /* Exchange */
  if(ISINST(pl->line, "exx"))
    return(1);
  if(ISINST(pl->line, "ex"))
    {
      if(!op2start)
        {
          fprintf(stderr, "Warning: z80instructionSize() failed to parse line node %s\n", pl->line);
          return(4);
        }
      if(argCont(op1start, "(sp)") && (IS_R2K || !strncmp(op2start, "ix", 2) || !strncmp(op2start, "iy", 2)))
        return(2);
      return(1);
    }

  /* Push / pop */
  if(ISINST(pl->line, "push") || ISINST(pl->line, "pop"))
    {
      if(!strncmp(op1start, "ix", 2) || !strncmp(op1start, "iy", 2))
        return(2);
      return(1);
    }

  /* 16 bit add / subtract / and */
  if((ISINST(pl->line, "add") || ISINST(pl->line, "adc") || ISINST(pl->line, "sbc") || IS_R2K && ISINST(pl->line, "and")) && !strncmp(op1start, "hl", 2))
    {
      if(ISINST(pl->line, "add") || ISINST(pl->line, "and"))
        return(1);
      return(2);
    }
  if(ISINST(pl->line, "add") && (!strncmp(op1start, "ix", 2) || !strncmp(op1start, "iy", 2)))
    return(2);

  if(IS_R2K && ISINST(pl->line, "add") && !strncmp(op1start, "sp", 2))
    return(2);

  /* 8 bit arithmetic, two operands */
  if(op2start &&  op1start[0] == 'a' && (ISINST(pl->line, "add") || ISINST(pl->line, "adc") || ISINST(pl->line, "sub") || ISINST(pl->line, "sbc") || ISINST(pl->line, "cp") || ISINST(pl->line, "and") || ISINST(pl->line, "or") || ISINST(pl->line, "xor")))
    {
      if(argCont(op2start, "(ix)") || argCont(op2start, "(iy)"))
        return(3);
      if(op2start[0] == '#')
        return(2);
      return(1);
    }

  if(ISINST(pl->line, "rlca") || ISINST(pl->line, "rla") || ISINST(pl->line, "rrca") || ISINST(pl->line, "rra"))
    return(1);

  /* Increment / decrement */
  if(ISINST(pl->line, "inc") || ISINST(pl->line, "dec"))
    {
      if(!strncmp(op1start, "ix", 2) || !strncmp(op1start, "iy", 2))
        return(2);
      if(argCont(op1start, "(ix)") || argCont(op1start, "(iy)"))
        return(3);
      return(1);
    }

  if(ISINST(pl->line, "rlc") || ISINST(pl->line, "rl") || ISINST(pl->line, "rrc") || ISINST(pl->line, "rr") || ISINST(pl->line, "sla") || ISINST(pl->line, "sra") || ISINST(pl->line, "srl"))
    {
      if(argCont(op1start, "(ix)") || argCont(op1start, "(iy)"))
        return(3);
      return(2);
    }

  if(ISINST(pl->line, "rld") || ISINST(pl->line, "rrd"))
    return(2);

  /* Bit */
  if(ISINST(pl->line, "bit") || ISINST(pl->line, "set") || ISINST(pl->line, "res"))
    {
      if(argCont(op1start, "(ix)") || argCont(op1start, "(iy)"))
        return(4);
      return(2);
    }

  if(ISINST(pl->line, "jr") || ISINST(pl->line, "djnz"))
    return(2);

  if(ISINST(pl->line, "jp"))
    {
      if(!strncmp(op1start, "(hl)", 4))
        return(1);
      if(!strncmp(op1start, "(ix)", 4) || !strncmp(op1start, "(iy)", 4))
        return(2);
      return(3);
    }

  if (TARGET_IS_R2K &&
      (ISINST(pl->line, "ipset3") || ISINST(pl->line, "ipset2") ||
       ISINST(pl->line, "ipset1") || ISINST(pl->line, "ipset0") ||
       ISINST(pl->line, "ipres")))
    return(2);
  
  if(ISINST(pl->line, "reti") || ISINST(pl->line, "retn"))
    return(2);

  if(ISINST(pl->line, "ret") || ISINST(pl->line, "rst"))
    return(1);

  if(ISINST(pl->line, "call"))
    return(3);

  if(ISINST(pl->line, "ldi") || ISINST(pl->line, "ldd") || ISINST(pl->line, "cpi") || ISINST(pl->line, "cpd"))
    return(2);

  if(ISINST(pl->line, "neg"))
    return(2);

  if(ISINST(pl->line, "daa") || ISINST(pl->line, "cpl") || ISINST(pl->line, "ccf") || ISINST(pl->line, "scf") || ISINST(pl->line, "nop") || ISINST(pl->line, "halt") || ISINST(pl->line,  "ei") || ISINST(pl->line, "di"))
    return(1);

  if(ISINST(pl->line, "im"))
    return(2);

  if(ISINST(pl->line, "in") || ISINST(pl->line, "out") || ISINST(pl->line, "ot"))
    return(2);

  if(ISINST(pl->line, "di") || ISINST(pl->line, "ei"))
    return(1);

  if(IS_Z180 && ISINST(pl->line, "mlt"))
    return(2);

  if(IS_R2K && ISINST(pl->line, "mul"))
    return(1);

  if(ISINST(pl->line, ".db"))
    {
      int i, j;
      for(i = 1, j = 0; pl->line[j]; i += pl->line[j] == ',', j++);
      return(i);
    }

  fprintf(stderr, "Warning: z80instructionSize() failed to parse line node %s\n", pl->line);

  return(4);
}

