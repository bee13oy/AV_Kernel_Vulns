# Avira Free Antivirus ssmdrv.sys Kernel Driver nt!memmove Memory Corruption Privilege Escalation Vulnerability

## Description

- There is a Memory Corruption Vulnerability in ssmdrv.sys when DeviceIoControl API is called with ioctl number 0x00220010, and an attacker can leverage this vulnerability to execute arbitrary code in the context of SYSTEM.

- This vuln was reported to Avira via [The ZDI program](http://www.zerodayinitiative.com/advisories/ZDI-16-670/).


## Tested Platforms: 
- Windows 7 x86 + Avira Free Antivirus 15.0.17.273

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
Arg1: 894cd000, memory referenced.
Arg2: 00000000, value 0 = read operation, 1 = write operation.
Arg3: 82a3c313, If non-zero, the instruction address which referenced the bad memory
	address.
Arg4: 00000000, (reserved)

Debugging Details:
------------------


READ_ADDRESS: GetPointerFromAddress: unable to read from 82b6f84c
Unable to read MiSystemVaType memory at 82b4e780
 894cd000 

FAULTING_IP: 
nt!memmove+33
82a3c313 f3a5            rep movs dword ptr es:[edi],dword ptr [esi]

MM_INTERNAL_CODE:  0

CUSTOMER_CRASH_COUNT:  1

DEFAULT_BUCKET_ID:  VERIFIER_ENABLED_VISTA_MINIDUMP

BUGCHECK_STR:  0x50

PROCESS_NAME:  ssmctl_BSoD1.e

CURRENT_IRQL:  0

TRAP_FRAME:  8d3738c4 -- (.trap 0xffffffff8d3738c4)
ErrCode = 00000000
eax=894d49ca ebx=abb21018 ecx=00001e73 edx=00000000 esi=894ccffe edi=abb21ed4
eip=82a3c313 esp=8d373938 ebp=8d373940 iopl=0         nv up ei pl nz ac po nc
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00010212
nt!memmove+0x33:
82a3c313 f3a5            rep movs dword ptr es:[edi],dword ptr [esi]
Resetting default scope

LAST_CONTROL_TRANSFER:  from 82a43be8 to 82a913c1

STACK_TEXT:  
8d3738ac 82a43be8 00000000 894cd000 00000000 nt!MmAccessFault+0x104
8d3738ac 82a3c313 00000000 894cd000 00000000 nt!KiTrap0E+0xdc
8d373940 82aabbfd abb21018 894cc142 00008888 nt!memmove+0x33
8d373960 8cdda64e 8d373998 00008888 9050c888 nt!RtlAppendUnicodeStringToString+0x43
WARNING: Stack unwind information not available. Following frames may be wrong.
8d3739a0 8cddab3b 8d3739b8 8d3739c0 9050c888 ssmdrv+0x64e
8d3739c8 8cddb734 894cc140 905adc20 9050c888 ssmdrv+0xb3b
8d3739e4 8cdda589 89789a58 00000eb7 8d373a18 ssmdrv+0x1734
8d3739f4 82d3b4d9 897899a0 9050c888 905adc20 ssmdrv+0x589
8d373a18 82a39d54 82c31324 9050c888 897899a0 nt!IovCallDriver+0x73
8d373a2c 82c31324 00000000 9050c888 9050c8f8 nt!IofCallDriver+0x1b
8d373a4c 82c34673 897899a0 905adc20 00000000 nt!IopSynchronousServiceTail+0x1f8
8d373b08 82c7b90d 0000001c 9050c888 00000000 nt!IopXxxControlFile+0x810
8d373b74 82ae897b 83e8fd14 8d373bec 80741000 nt!NtDeviceIoControlFile+0x2a
8d373c04 82a40a06 0000001c 00000000 00000000 nt!MiCheckUserVirtualAddress+0xb3
8d373c04 777c70d4 0000001c 00000000 00000000 nt!KiSystemServicePostCall
002adaec 00000000 00000000 00000000 00000000 0x777c70d4


STACK_COMMAND:  kb

FOLLOWUP_IP: 
ssmdrv+64e
8cdda64e ??              ???

SYMBOL_STACK_INDEX:  4

SYMBOL_NAME:  ssmdrv+64e

FOLLOWUP_NAME:  MachineOwner

MODULE_NAME: ssmdrv

IMAGE_NAME:  ssmdrv.sys

DEBUG_FLR_IMAGE_TIMESTAMP:  4a000f5e

FAILURE_BUCKET_ID:  0x50_VRF_ssmdrv+64e

BUCKET_ID:  0x50_VRF_ssmdrv+64e

Followup: MachineOwner
---------
```