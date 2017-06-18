# AVG Internet Security avgtdix.sys Kernel Driver Memory Corruption Privilege Escalation Vulnerability

## Description

- There is a Memory Corruption Vulnerability in avgtdix.sys when DeviceIoControl API is called with ioctl number 0x83002120, and an attacker may leverage this vulnerability to execute arbitrary code in the context of SYSTEM.

- This vuln was reported to AVG via [The ZDI program](http://www.zerodayinitiative.com/advisories/ZDI-16-487/).

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
Arg1: 894bb008, memory referenced.
Arg2: 00000000, value 0 = read operation, 1 = write operation.
Arg3: 8d0db2c3, If non-zero, the instruction address which referenced the bad memory
	address.
Arg4: 00000000, (reserved)

Debugging Details:
------------------


Could not read faulting driver name

READ_ADDRESS: GetPointerFromAddress: unable to read from 82b6c84c
Unable to read MiSystemVaType memory at 82b4b780
 894bb008 

FAULTING_IP: 
avgtdix+262c3
8d0db2c3 66833e02        cmp     word ptr [esi],2

MM_INTERNAL_CODE:  0

CUSTOMER_CRASH_COUNT:  1

DEFAULT_BUCKET_ID:  VERIFIER_ENABLED_VISTA_MINIDUMP

BUGCHECK_STR:  0x50

PROCESS_NAME:  DeviceLoader.e

CURRENT_IRQL:  0

TRAP_FRAME:  a0965844 -- (.trap 0xffffffffa0965844)
ErrCode = 00000000
eax=00008000 ebx=894ba040 ecx=0000003f edx=00000000 esi=894bb008 edi=0000003f
eip=8d0db2c3 esp=a09658b8 ebp=a09658c8 iopl=0         nv up ei ng nz na pe cy
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00010287
avgtdix+0x262c3:
8d0db2c3 66833e02        cmp     word ptr [esi],2         ds:0023:894bb008=????
Resetting default scope

LAST_CONTROL_TRANSFER:  from 82a40bf8 to 82a8e401

STACK_TEXT:  
a096582c 82a40bf8 00000000 894bb008 00000000 nt!MmAccessFault+0x104
a096582c 8d0db2c3 00000000 894bb008 00000000 nt!KiTrap0E+0xdc
a09658c8 8d0d3840 00008000 00000da8 894ba040 avgtdix+0x262c3
a0965948 8d0d5aac 894ba040 00000da8 88ca8860 avgtdix+0x1e840
a0965988 8d0cbc43 a09659c7 93a16a48 93a16a48 avgtdix+0x20aac
a09659b0 8d0b6cf1 89a92ab0 93a16a48 89a92ab0 avgtdix+0x16c43
a09659e4 8d0ba0b5 8a06b048 93a16a48 a0965a18 avgtdix+0x1cf1
a09659f4 82d384d9 89a92ab0 93a16a48 8a06b048 avgtdix+0x50b5
a0965a18 82a36d49 82c2e3e4 93a16a48 89a92ab0 nt!IovCallDriver+0x73
a0965a2c 82c2e3e4 00000000 93a16a48 93a16ab8 nt!IofCallDriver+0x1b
a0965a4c 82c31733 89a92ab0 8a06b048 00000000 nt!IopSynchronousServiceTail+0x1f8
a0965b08 82c789bd 0000001c 93a16a48 00000000 nt!IopXxxControlFile+0x810
a0965b90 82a78d10 93b65f80 82c48fc8 9ffc1c80 nt!NtDeviceIoControlFile+0x2a
a0965b98 82c48fc8 9ffc1c80 8a060a60 00000020 nt!ObfDereferenceObject+0xd
a0965c04 82a3da16 0000001c 00000000 00000000 nt!ObpCloseHandleTableEntry+0x21d
a0965c04 771c70d4 0000001c 00000000 00000000 nt!KiSystemServicePostCall
0017f1c8 00000000 00000000 00000000 00000000 0x771c70d4


STACK_COMMAND:  kb

FOLLOWUP_IP: 
avgtdix+262c3
8d0db2c3 66833e02        cmp     word ptr [esi],2

SYMBOL_STACK_INDEX:  2

SYMBOL_NAME:  avgtdix+262c3

FOLLOWUP_NAME:  MachineOwner

MODULE_NAME: avgtdix

IMAGE_NAME:  avgtdix.sys

DEBUG_FLR_IMAGE_TIMESTAMP:  561611d7

FAILURE_BUCKET_ID:  0x50_VRF_avgtdix+262c3

BUCKET_ID:  0x50_VRF_avgtdix+262c3

Followup: MachineOwner
---------
```