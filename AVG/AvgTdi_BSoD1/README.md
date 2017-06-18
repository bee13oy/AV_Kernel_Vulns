# AVG Internet Security avgtdix.sys Kernel Driver Memory Corruption Privilege Escalation Vulnerability

## Description

- There is a Memory Corruption Vulnerability in avgtdix.sys when DeviceIoControl API is called with ioctl number 0x534a600c, and An attacker may leverage this vulnerability to execute arbitrary code in the context of SYSTEM.

- This vuln was reported to AVG via [The ZDI program](http://www.zerodayinitiative.com/advisories/ZDI-16-484/).

## Tested Platforms: 
- Windows 7 SP1 x86 + AVG Internet Security 16.61.7539

## Crash Details:

```
0: kd> !analyze -v
*******************************************************************************
*                                                                             *
*                        Bugcheck Analysis                                    *
*                                                                             *
*******************************************************************************

KERNEL_MODE_EXCEPTION_NOT_HANDLED_M (1000008e)
This is a very common bugcheck.  Usually the exception address pinpoints
the driver/function that caused the problem.  Always note this address
as well as the link date of the driver/image that contains this address.
Some common problems are exception code 0x80000003.  This means a hard
coded breakpoint or assertion was hit, but this system was booted
/NODEBUG.  This is not supposed to happen as developers should never have
hardcoded breakpoints in retail code, but ...
If this happens, make sure a debugger gets connected, and the
system is booted /DEBUG.  This will let us see why this breakpoint is
happening.
Arguments:
Arg1: c0000005, The exception code that was not handled
Arg2: 8fac4e04, The address that the exception occurred at
Arg3: 97e2b94c, Trap Frame
Arg4: 00000000

Debugging Details:
------------------


EXCEPTION_CODE: (NTSTATUS) 0xc0000005 - The instruction at 0x%08lx referenced memory at 0x%08lx. The memory could not be %s.

FAULTING_IP: 
avgtdix+2e04
8fac4e04 0fb78888000000  movzx   ecx,word ptr [eax+88h]

TRAP_FRAME:  97e2b94c -- (.trap 0xffffffff97e2b94c)
ErrCode = 00000000
eax=00008700 ebx=873f0040 ecx=856cff00 edx=84f88f10 esi=84f88ea0 edi=86c48598
eip=8fac4e04 esp=97e2b9c0 ebp=97e2b9d0 iopl=0         nv up ei pl nz na pe nc
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00010206
avgtdix+0x2e04:
8fac4e04 0fb78888000000  movzx   ecx,word ptr [eax+88h]   ds:0023:00008788=????
Resetting default scope

CUSTOMER_CRASH_COUNT:  1

DEFAULT_BUCKET_ID:  VISTA_DRIVER_FAULT

BUGCHECK_STR:  0x8E

PROCESS_NAME:  AvgTdi_BSoD1.e

CURRENT_IRQL:  0

LAST_CONTROL_TRANSFER:  from 8fac3e53 to 8fac4e04

STACK_TEXT:  
WARNING: Stack unwind information not available. Following frames may be wrong.
97e2b9d0 8fac3e53 856cfe70 856cfe70 00000000 avgtdix+0x2e04
97e2ba04 8fac70b5 8747bd00 856cfe70 97e2ba2c avgtdix+0x1e53
97e2ba14 82a70d92 856cfe70 84f88ea0 84f88ea0 avgtdix+0x50b5
97e2ba2c 82c683e4 00000000 84f88ea0 84f88f10 nt!IofCallDriver+0x63
97e2ba4c 82c6b733 856cfe70 8747bd00 00000000 nt!IopSynchronousServiceTail+0x1f8
97e2bb08 82cb29bd 0000001c 84f88ea0 00000000 nt!IopXxxControlFile+0x810
97e2bb74 82b1fa27 840003e0 97e2bbec 80741000 nt!NtDeviceIoControlFile+0x2a
97e2bc04 82a77a16 0000001c 00000000 00000000 nt!MiCheckUserVirtualAddress+0xb3
97e2bc04 76ed70d4 0000001c 00000000 00000000 nt!KiSystemServicePostCall
0031dad8 00000000 00000000 00000000 00000000 0x76ed70d4


STACK_COMMAND:  kb

FOLLOWUP_IP: 
avgtdix+2e04
8fac4e04 0fb78888000000  movzx   ecx,word ptr [eax+88h]

SYMBOL_STACK_INDEX:  0

SYMBOL_NAME:  avgtdix+2e04

FOLLOWUP_NAME:  MachineOwner

MODULE_NAME: avgtdix

IMAGE_NAME:  avgtdix.sys

DEBUG_FLR_IMAGE_TIMESTAMP:  561611d7

FAILURE_BUCKET_ID:  0x8E_avgtdix+2e04

BUCKET_ID:  0x8E_avgtdix+2e04

Followup: MachineOwner
---------
```