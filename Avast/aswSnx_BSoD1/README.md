# Avast aswSnx.sys Kernel Driver Memory Corruption Privilege Escalation Vulnerability

## Description

- There is a Memory Corruption Vulnerability in aswSnx.sys when DeviceIoControl API is called with ioctl number 0x82AC0060, and An attacker may leverage this vulnerability to execute arbitrary code in the context of SYSTEM.

- This vuln was reported to Avast via [The Avast bug bounty program](https://www.avast.com/bug-bounty).


## Tested Platforms: 
- Windows 7 x86 + Avast Premier 11.1.2253
- Windows 10 x86 + Avast Free Antivirus 11.1.2253

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
Arg2: 82b68f1f, The address that the exception occurred at
Arg3: af37b4f4, Trap Frame
Arg4: 00000000

Debugging Details:
------------------


EXCEPTION_CODE: (NTSTATUS) 0xc0000005 - The instruction at 0x%08lx referenced memory at 0x%08lx. The memory could not be %s.

FAULTING_IP: 
nt!ExFreePoolWithTag+464
82b68f1f 0fb74ffa        movzx   ecx,word ptr [edi-6]

TRAP_FRAME:  af37b4f4 -- (.trap 0xffffffffaf37b4f4)
ErrCode = 00000000
eax=00000000 ebx=8c4e20aa ecx=00000008 edx=82a81499 esi=00000010 edi=00000010
eip=82b68f1f esp=af37b568 ebp=af37b5c4 iopl=0         nv up ei pl nz na po nc
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00010202
nt!ExFreePoolWithTag+0x464:
82b68f1f 0fb74ffa        movzx   ecx,word ptr [edi-6]     ds:0023:0000000a=????
Resetting default scope

CUSTOMER_CRASH_COUNT:  1

DEFAULT_BUCKET_ID:  VERIFIER_ENABLED_VISTA_MINIDUMP

BUGCHECK_STR:  0x8E

PROCESS_NAME:  BSoD1.exe

CURRENT_IRQL:  0

LAST_CONTROL_TRANSFER:  from 8c4d79fe to 82b68f1f

STACK_TEXT:  
af37b5c4 8c4d79fe 00000010 20786e53 237a8284 nt!ExFreePoolWithTag+0x464
af37b9c8 8c431090 92b7b008 89675540 0000080c aswSnx+0xa89fe
af37b9f4 82d7e4d9 89a0d938 00000000 896274c8 aswSnx+0x2090
af37ba18 82a7cd54 82c74324 92b7b008 89a0d938 nt!IovCallDriver+0x73
af37ba2c 82c74324 00000000 92b7b008 92b7b078 nt!IofCallDriver+0x1b
af37ba4c 82c77673 89a0d938 896274c8 00000000 nt!IopSynchronousServiceTail+0x1f8
af37bb08 82cbe90d 00000090 92b7b008 00000000 nt!IopXxxControlFile+0x810
af37bb80 82ac78f4 807d5120 00000000 00000001 nt!NtDeviceIoControlFile+0x2a
af37bc04 82a83a06 00000090 00000000 00000000 nt!KeReleaseMutant+0x1b2
af37bc04 777070d4 00000090 00000000 00000000 nt!KiSystemServicePostCall
001bd9d8 00000000 00000000 00000000 00000000 0x777070d4


STACK_COMMAND:  kb

FOLLOWUP_IP: 
aswSnx+a89fe
8c4d79fe ??              ???

SYMBOL_STACK_INDEX:  1

SYMBOL_NAME:  aswSnx+a89fe

FOLLOWUP_NAME:  MachineOwner

MODULE_NAME: aswSnx

IMAGE_NAME:  aswSnx.sys

DEBUG_FLR_IMAGE_TIMESTAMP:  56b0c3de

FAILURE_BUCKET_ID:  0x8E_VRF_aswSnx+a89fe

BUCKET_ID:  0x8E_VRF_aswSnx+a89fe

Followup: MachineOwner
---------
```