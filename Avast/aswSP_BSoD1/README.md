# Avast aswSP.sys Kernel Driver Memory Corruption Vulnerability

## Description

- There is a Memory Corruption Vulnerability in aswSP.sys when DeviceIoControl API is called with ioctl number 0xb2d6016c, and An attacker may leverage this vulnerability to execute arbitrary code in the context of SYSTEM.

- This vuln was reported to Avast via [The Avast bug bounty program](https://www.avast.com/bug-bounty).


## Tested Platforms: 
- Windows 7 SP1 x86 + Avast Free Antivirus 11.1.2253 (aswsp.sys version: 11.1.2253.1663)

## Steps to reproduce this vuln:
1. Special Pools enabled for aswSP.sys (verifier /flags 0x1 /driver aswSP.sys) and then reboot the system.
2. Run BSoD3.exe as Administrator and you will see the blue screen of death immediately.

## Crash Details:


```
1: kd> !analyze -v
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
Arg1: 82037000, memory referenced.
Arg2: 00000000, value 0 = read operation, 1 = write operation.
Arg3: 82a55703, If non-zero, the instruction address which referenced the bad memory
	address.
Arg4: 00000000, (reserved)

Debugging Details:
------------------


READ_ADDRESS:  82037000 

FAULTING_IP: 
nt!RtlInitUnicodeString+1b
82a55703 f266af          repne scas word ptr es:[edi]

MM_INTERNAL_CODE:  0

CUSTOMER_CRASH_COUNT:  1

DEFAULT_BUCKET_ID:  VERIFIER_ENABLED_VISTA_MINIDUMP

BUGCHECK_STR:  0x50

PROCESS_NAME:  BSoD3.exe

CURRENT_IRQL:  0

TRAP_FRAME:  a1ba18dc -- (.trap 0xffffffffa1ba18dc)
ErrCode = 00000000
eax=00000000 ebx=00000000 ecx=fffffaef edx=a1ba19c8 esi=a48261c0 edi=82037000
eip=82a55703 esp=a1ba1950 ebp=a1ba19f4 iopl=0         nv up ei pl zr na pe nc
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00010246
nt!RtlInitUnicodeString+0x1b:
82a55703 f266af          repne scas word ptr es:[edi]
Resetting default scope

LAST_CONTROL_TRANSFER:  from 82a5dbe8 to 82aab3c1

STACK_TEXT:  
a1ba18c4 82a5dbe8 00000000 82037000 00000000 nt!MmAccessFault+0x104
a1ba18c4 82a55703 00000000 82037000 00000000 nt!KiTrap0E+0xdc
a1ba19f4 82d554d9 89886ac8 a48261c0 95cde5f0 nt!RtlInitUnicodeString+0x1b
a1ba1a18 82a53d54 82c4b324 a48261c0 89886ac8 nt!IovCallDriver+0x73
a1ba1a2c 82c4b324 00000000 a48261c0 a4826230 nt!IofCallDriver+0x1b
a1ba1a4c 82c4e673 89886ac8 95cde5f0 00000000 nt!IopSynchronousServiceTail+0x1f8
a1ba1b08 82c9590d 0000001c a48261c0 00000000 nt!IopXxxControlFile+0x810
a1ba1b74 82b0297b 840c9498 a1ba1bec 80741000 nt!NtDeviceIoControlFile+0x2a
a1ba1c04 82a5aa06 0000001c 00000000 00000000 nt!MiCheckUserVirtualAddress+0xb3
a1ba1c04 77ce70d4 0000001c 00000000 00000000 nt!KiSystemServicePostCall
WARNING: Frame IP not in any known module. Following frames may be wrong.
0018dc2c 00000000 00000000 00000000 00000000 0x77ce70d4


STACK_COMMAND:  kb

FOLLOWUP_IP: 
nt!KiTrap0E+dc
82a5dbe8 85c0            test    eax,eax

SYMBOL_STACK_INDEX:  1

SYMBOL_NAME:  nt!KiTrap0E+dc

FOLLOWUP_NAME:  MachineOwner

MODULE_NAME: nt

IMAGE_NAME:  ntkrpamp.exe

DEBUG_FLR_IMAGE_TIMESTAMP:  56a1b854

FAILURE_BUCKET_ID:  0x50_VRF_nt!KiTrap0E+dc

BUCKET_ID:  0x50_VRF_nt!KiTrap0E+dc

Followup: MachineOwner
---------
```