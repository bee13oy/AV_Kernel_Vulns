# Avast aswSnx.sys Kernel Driver Memory Corruption Privilege Escalation Vulnerability

## Description

- There is a Memory Corruption Vulnerability in aswSnx.sys when DeviceIoControl API is called with ioctl number 0x82ac0170, and An attacker may leverage this vulnerability to execute arbitrary code in the context of SYSTEM.

- This vuln was reported to Avast via [The ZDI program](http://www.zerodayinitiative.com/advisories/ZDI-16-681/).


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
Arg2: 82ae06af, The address that the exception occurred at
Arg3: ad9d9568, Trap Frame
Arg4: 00000000

Debugging Details:
------------------


EXCEPTION_CODE: (NTSTATUS) 0xc0000005 - The instruction at 0x%08lx referenced memory at 0x%08lx. The memory could not be %s.

FAULTING_IP: 
nt!RtlCopyUnicodeString+e
82ae06af 0fb738          movzx   edi,word ptr [eax]

TRAP_FRAME:  ad9d9568 -- (.trap 0xffffffffad9d9568)
ErrCode = 00000000
eax=4a4a4a4a ebx=8e741650 ecx=acabb018 edx=acabb008 esi=87038800 edi=00000008
eip=82ae06af esp=ad9d95dc ebp=ad9d95e4 iopl=0         nv up ei pl nz na po nc
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00010202
nt!RtlCopyUnicodeString+0xe:
82ae06af 0fb738          movzx   edi,word ptr [eax]       ds:0023:4a4a4a4a=????
Resetting default scope

CUSTOMER_CRASH_COUNT:  1

DEFAULT_BUCKET_ID:  VISTA_DRIVER_FAULT

BUGCHECK_STR:  0x8E

PROCESS_NAME:  BSoD2.exe

CURRENT_IRQL:  0

LAST_CONTROL_TRANSFER:  from 8e74656b to 82ae06af

STACK_TEXT:  
ad9d95e4 8e74656b acabb008 4a4a4a4a 23e992a6 nt!RtlCopyUnicodeString+0xe
WARNING: Stack unwind information not available. Following frames may be wrong.
ad9d99e8 8e69e090 8766f638 87038800 00000008 aswSnx+0xaa56b
ad9d9a14 82a6ed9d 85635c30 00000000 8766f638 aswSnx+0x2090
ad9d9a2c 82c66324 00000000 8766f638 8766f6a8 nt!IofCallDriver+0x63
ad9d9a4c 82c69673 85635c30 84e26f80 00000000 nt!IopSynchronousServiceTail+0x1f8
ad9d9b08 82cb090d 00000090 8766f638 00000000 nt!IopXxxControlFile+0x810
ad9d9b80 82ab98f4 807d3120 00000000 00000001 nt!NtDeviceIoControlFile+0x2a
ad9d9c04 82a75a06 00000090 00000000 00000000 nt!KeReleaseMutant+0x1b2
ad9d9c04 774370d4 00000090 00000000 00000000 nt!KiSystemServicePostCall
0020fb64 00000000 00000000 00000000 00000000 0x774370d4


STACK_COMMAND:  kb

FOLLOWUP_IP: 
aswSnx+aa56b
8e74656b ??              ???

SYMBOL_STACK_INDEX:  1

SYMBOL_NAME:  aswSnx+aa56b

FOLLOWUP_NAME:  MachineOwner

MODULE_NAME: aswSnx

IMAGE_NAME:  aswSnx.sys

DEBUG_FLR_IMAGE_TIMESTAMP:  56b0c3de

FAILURE_BUCKET_ID:  0x8E_aswSnx+aa56b

BUCKET_ID:  0x8E_aswSnx+aa56b

Followup: MachineOwner
---------
```