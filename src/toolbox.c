#include <ucos_ii.h>
#include <init.h>
#include "stm32f10x.h"
#include "version.h"
#include <stdio.h>

/* ps command
 * List all of tasks
 */
static int ps(int argc, char *argv[])
{
	OS_TCB *ptcb;
	ptcb = OSTCBList;
	while (ptcb->OSTCBPrio != OS_TASK_IDLE_PRIO) {	 /* Go through all TCBs in TCB list */
		printf("[%14s] PRIO:%2d TimeDelay:%5d "
			"STACK-SIZE:%4d STACK-USAGE:%2d%% "
			"CTXSW:%5d\n",
			ptcb->OSTCBTaskName,
			ptcb->OSTCBPrio, 
			ptcb->OSTCBDly,
			ptcb->OSTCBStkSize,
			ptcb->OSTCBStkUsed  *100 / (ptcb->OSTCBStkSize * sizeof(OS_STK)),
			ptcb->OSTCBCtxSwCtr);
		ptcb = ptcb->OSTCBNext;	/* Point at next TCB in TCB list */
	}
	return 0;
}

static char pshelp[] = "List all of tasks.\n";
__commandlist(ps, "ps", pshelp);

/*
 * Reset command
 * software reset system
 */
static int reset(int argc, char *argv[])
{
	__set_FAULTMASK(1);
	SCB->AIRCR = 0x05FA0004;
	return 0;
}

static char resethelp[] = "Reset system.\n";
__commandlist(reset, "reset", resethelp);

/*
 * system version
 */
static int version(int argc, char *argv[])
{
	printf("(%s@%s) %s\n", COMPILE_BY, COMPILE_HOST, COMPILER);
	/*COMPILE* is auto generated by Makefile */
	return 0;
}

static char versionhelp[] = "system version\n";
__commandlist(version, "version", versionhelp);
