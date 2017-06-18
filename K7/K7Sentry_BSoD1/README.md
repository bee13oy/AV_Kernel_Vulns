# K7 Antivirus Premium K7Sentry.sys Kernel Driver Memory Corruption Privilege Escalation Vulnerability

## Description

- There is a Memory Corruption Vulnerability in K7Sentry.sys when DeviceIoControl API is called with ioctl number 0x95002867, and an attacker may leverage this vulnerability to execute arbitrary code in the context of SYSTEM.

- This vuln was reported to K7 directly.

## Tested Platforms: 
- Windows 7 x86 + K7 Antivirus Premium 15.1.0289

## Crash Details:

```
0: kd> r
eax=7fff0000 ebx=87799bc0 ecx=ffff0000 edx=ffff0312 esi=0115f850 edi=87799b6c
eip=82c83603 esp=a72ab9d4 ebp=a72ab9d4 iopl=0         nv up ei ng nz na pe nc
cs=0008  ss=0010  ds=0023  es=0023  fs=0030  gs=0000             efl=00010286
nt!ProbeForRead+0x2e:
82c83603 c60000          mov     byte ptr [eax],0           ds:0023:7fff0000=??
0: kd> kb
ChildEBP RetAddr  Args to Child              
a72ab9d4 88c8b8b6 ffff0000 00000312 00000001 nt!ProbeForRead+0x2e
WARNING: Stack unwind information not available. Following frames may be wrong.
a72aba14 82a39d9d 84d43630 87799b50 87799b50 K7Sentry+0x78b6
a72aba2c 82c31324 00000000 87799b50 87799bc0 nt!IofCallDriver+0x63
a72aba4c 82c34673 84d43630 87f11b78 00000000 nt!IopSynchronousServiceTail+0x1f8
a72abb08 82c7b90d 00000028 87799b50 00000000 nt!IopXxxControlFile+0x810
a72abb68 82c28ed6 885b62a8 c0008a78 82ae897b nt!NtDeviceIoControlFile+0x2a
a72abc04 82a40a06 00000028 00000000 00000000 nt!ObpRemoveObjectRoutine+0x5e
a72abc04 76e170d4 00000028 00000000 00000000 nt!KiSystemServicePostCall
0029f5b4 00000000 00000000 00000000 00000000 0x76e170d4
```