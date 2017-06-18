# Check Point ZoneAlarm Security vsdatant.sys Kernel Driver Memory Corruption Privilege Escalation Vulnerability

## Description

- There is a Memory Corruption Vulnerability in vsdatant.sys when DeviceIoControl API is called with ioctl number 0x8400001f, and an attacker may leverage this vulnerability to execute arbitrary code in the context of SYSTEM.

- This vuln was reported to Check Point via [The ZDI program](http://www.zerodayinitiative.com/advisories/ZDI-16-683//).

## Tested Platforms: 
- Windows 7 x86 + ZoneAlarm Security 14.1.057.000

## Crash Details:

```
1: kd> !analyze -v
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
Arg2: 90543bd0, The address that the exception occurred at
Arg3: af7bf844, Trap Frame
Arg4: 00000000

Debugging Details:
------------------


EXCEPTION_CODE: (NTSTATUS) 0xc0000005 - The instruction at 0x%08lx referenced memory at 0x%08lx. The memory could not be %s.

FAULTING_IP: 
vsdatant+1cbd0
90543bd0 ff36            push    dword ptr [esi]

TRAP_FRAME:  af7bf844 -- (.trap 0xffffffffaf7bf844)
ErrCode = 00000000
eax=af7bf8e4 ebx=8400001f ecx=00000000 edx=c0001378 esi=44444444 edi=879e1138
eip=90543bd0 esp=af7bf8b8 ebp=af7bf8d0 iopl=0         nv up ei pl zr na pe nc
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00010246
vsdatant+0x1cbd0:
90543bd0 ff36            push    dword ptr [esi]      ds:0023:44444444=????????
Resetting default scope

CUSTOMER_CRASH_COUNT:  1

DEFAULT_BUCKET_ID:  VISTA_DRIVER_FAULT

BUGCHECK_STR:  0x8E

PROCESS_NAME:  Vsdatant_BSoD1

CURRENT_IRQL:  0

LAST_CONTROL_TRANSFER:  from 90544692 to 90543bd0

STACK_TEXT:  
WARNING: Stack unwind information not available. Following frames may be wrong.
af7bf8d0 90544692 87b4e430 00000001 44444444 vsdatant+0x1cbd0
af7bf908 9054258f 85e52030 879e1120 85e52030 vsdatant+0x1d692
af7bf91c 82a80d9d 85e52030 879e1120 879e1120 vsdatant+0x1b58f
af7bf934 82c78324 00000000 879e1120 879e1190 nt!IofCallDriver+0x63
af7bf954 82c7b673 85e52030 87b4e430 00000000 nt!IopSynchronousServiceTail+0x1f8
af7bfa10 82cc290d 0000001c 879e1120 00000000 nt!IopXxxControlFile+0x810
af7bfa44 8ec56910 0000001c 00000000 00000000 nt!NtDeviceIoControlFile+0x2a
af7bfad0 8ed2d05a 0000001c 00000000 00000000 klif+0x1f910
af7bfb08 8ed2e206 8ec564d6 af7bfb44 00000028 klhk+0x105a
af7bfb24 8ed2d01f 85ce8c70 af7bfb44 af7bfb38 klhk+0x2206
af7bfb74 82b2f97b 846bd07c af7bfbec 80741000 klhk+0x101f
af7bfc04 82a87a06 0000001c 00000000 00000000 nt!MiCheckUserVirtualAddress+0xb3
af7bfc04 77c070d4 0000001c 00000000 00000000 nt!KiSystemServicePostCall
0026eb50 00000000 00000000 00000000 00000000 0x77c070d4


STACK_COMMAND:  kb

FOLLOWUP_IP: 
vsdatant+1cbd0
90543bd0 ff36            push    dword ptr [esi]

SYMBOL_STACK_INDEX:  0

SYMBOL_NAME:  vsdatant+1cbd0

FOLLOWUP_NAME:  MachineOwner

MODULE_NAME: vsdatant

IMAGE_NAME:  vsdatant.sys

DEBUG_FLR_IMAGE_TIMESTAMP:  56f0cfc0

FAILURE_BUCKET_ID:  0x8E_vsdatant+1cbd0

BUCKET_ID:  0x8E_vsdatant+1cbd0

Followup: MachineOwner
---------
```