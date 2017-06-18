# AVG Internet Security avgidsdriverx.sys Kernel Driver Memory Corruption Privilege Escalation Vulnerability

## Description

- There is a Memory Corruption Vulnerability in avgidsdriverx.sys when DeviceIoControl API is called with ioctl number 0x53606148, and An attacker may leverage this vulnerability to execute arbitrary code in the context of SYSTEM.

- This vuln was reported to AVG via [The ZDI program](http://www.zerodayinitiative.com/advisories/ZDI-16-483/).

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

PAGE_FAULT_IN_NONPAGED_AREA (50)
Invalid system memory was referenced.  This cannot be protected by try-except,
it must be protected by a Probe.  Typically the address is just plain bad or it
is pointing at freed memory.
Arguments:
Arg1: ffff8888, memory referenced.
Arg2: 00000000, value 0 = read operation, 1 = write operation.
Arg3: 82a40fd3, If non-zero, the instruction address which referenced the bad memory
	address.
Arg4: 00000000, (reserved)

Debugging Details:
------------------


OVERLAPPED_MODULE: Address regions for 'bthport' and 'bthport.sys' overlap

READ_ADDRESS: GetPointerFromAddress: unable to read from 82b7484c
Unable to read MiSystemVaType memory at 82b53780
 ffff8888 

FAULTING_IP: 
nt!memcpy+33
82a40fd3 f3a5            rep movs dword ptr es:[edi],dword ptr [esi]

MM_INTERNAL_CODE:  0

CUSTOMER_CRASH_COUNT:  1

DEFAULT_BUCKET_ID:  VISTA_DRIVER_FAULT

BUGCHECK_STR:  0x50

PROCESS_NAME:  AVGIDS_Ioc2_BS

CURRENT_IRQL:  0

TRAP_FRAME:  a6c4a890 -- (.trap 0xffffffffa6c4a890)
ErrCode = 00000000
eax=00004e6c ebx=0000c5e4 ecx=00003179 edx=00000000 esi=ffff8888 edi=8aab0000
eip=82a40fd3 esp=a6c4a904 ebp=a6c4a90c iopl=0         nv up ei pl nz na pe nc
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00010206
nt!memcpy+0x33:
82a40fd3 f3a5            rep movs dword ptr es:[edi],dword ptr [esi]
Resetting default scope

LAST_CONTROL_TRANSFER:  from 82a48bf8 to 82a96401

STACK_TEXT:  
a6c4a878 82a48bf8 00000000 ffff8888 00000000 nt!MmAccessFault+0x104
a6c4a878 82a40fd3 00000000 ffff8888 00000000 nt!KiTrap0E+0xdc
a6c4a90c 8fc4f637 8aab0000 ffff8888 0000c5e4 nt!memcpy+0x33
WARNING: Stack unwind information not available. Following frames may be wrong.
a6c4a984 8fc404b3 a6c4a9cc 85695ea0 c0000002 avgidsdriverx+0x27637
a6c4a9d8 8fc2a76d 8580d800 c0000002 85695f10 avgidsdriverx+0x184b3
a6c4a9f0 8fc2b268 85695f10 a6c4aa0c 86aa6208 avgidsdriverx+0x276d
a6c4aa14 82a3ed92 8580d748 85695ea0 85695ea0 avgidsdriverx+0x3268
a6c4aa2c 82c363e4 00000000 85695ea0 85695f10 nt!IofCallDriver+0x63
a6c4aa4c 82c39733 8580d748 86aa6208 00000000 nt!IopSynchronousServiceTail+0x1f8
a6c4ab08 82c809bd 0000001c 85695ea0 00000000 nt!IopXxxControlFile+0x810
a6c4ab74 82aeda27 840d0268 a6c4abec 80741000 nt!NtDeviceIoControlFile+0x2a
a6c4ac04 82a45a16 0000001c 00000000 00000000 nt!MiCheckUserVirtualAddress+0xb3
a6c4ac04 77a670d4 0000001c 00000000 00000000 nt!KiSystemServicePostCall
002dd968 00000000 00000000 00000000 00000000 0x77a670d4


STACK_COMMAND:  kb

FOLLOWUP_IP: 
avgidsdriverx+27637
8fc4f637 ??              ???

SYMBOL_STACK_INDEX:  3

SYMBOL_NAME:  avgidsdriverx+27637

FOLLOWUP_NAME:  MachineOwner

MODULE_NAME: avgidsdriverx

IMAGE_NAME:  avgidsdriverx.sys

DEBUG_FLR_IMAGE_TIMESTAMP:  56deea9d

FAILURE_BUCKET_ID:  0x50_avgidsdriverx+27637

BUCKET_ID:  0x50_avgidsdriverx+27637

Followup: MachineOwner
---------
```