## Example

On [Intel Core i7-8700](https://ark.intel.com/content/www/us/en/ark/products/126686/intel-core-i7-8700-processor-12m-cache-up-to-4-60-ghz.html):

```
CPUID.B.00     00000016 756E6547 6C65746E 49656E69
Maximum Basic Leaf = 00000016
Vendor Identification String = GenuineIntel
CPUID.B.01     000906EA 09100800 7FFAFBFF BFEBFBFF
Processor Type = Original OEM Processor
Basic Family ID = 6
Extended Family ID = 0
Basic Model ID = E
Extended Model ID = 09
Display Family ID = 06
Display Model ID = 9E
Brand Index = 0
CLFLUSH Line Size = 64B
HT Threads = 16
Supported     = SSE3 PCLMULQDQ DTES64 MONITOR DS-CPL VMX SMX EIST TM2 SSSE3 SDBG FMA CMPXCHG16B xTPR_Update_Control PDCM PCID SSE4_1 SSE4_2 x2APIC MOVBE POPCNT TSC-Deadline AESNI XSAVE OSXSAVE AVX F16C RDRAND FPU VME DE PSE TSC MSR PAE MCE CX8 APIC SEP MTRR PGE MCA CMOV PAT PSE-36 CLFLUSH DS ACPI MMX FXSAVE SSE SSE2 SS HTT TM PBE
Not Supported = CNXT-ID DCA PSN
CPUID.B.02     76036301 00F0B5FF 00000000 00C30000
CPUID.B.03     00000000 00000000 00000000 00000000
CPUID.B.04.0   1C004121 01C0003F 0000003F 00000000
Cache Type = L1 Data
Self Initializing = Yes
Max Number of Addressable IDs for Logical Processors Sharing This Cache = 2
Max Number of Addressable IDs for Cores in Physical Package = 8
Associativity = 8-way Set Associative
Coherency Line Size = 64B
Physical Line Partitions = 1
Number of Sets = 64
Total Size = 32768B (32KB)
Lower Level Invalidate Behavior = Guaranteed
Inclusiveness = Non-Inclusive
Cache Indexing = Direct Mapped
CPUID.B.04.1   1C004122 01C0003F 0000003F 00000000
Cache Type = L1 Instruction
Self Initializing = Yes
Max Number of Addressable IDs for Logical Processors Sharing This Cache = 2
Max Number of Addressable IDs for Cores in Physical Package = 8
Associativity = 8-way Set Associative
Coherency Line Size = 64B
Physical Line Partitions = 1
Number of Sets = 64
Total Size = 32768B (32KB)
Lower Level Invalidate Behavior = Guaranteed
Inclusiveness = Non-Inclusive
Cache Indexing = Direct Mapped
CPUID.B.04.2   1C004143 00C0003F 000003FF 00000000
Cache Type = L2 Unified
Self Initializing = Yes
Max Number of Addressable IDs for Logical Processors Sharing This Cache = 2
Max Number of Addressable IDs for Cores in Physical Package = 8
Associativity = 4-way Set Associative
Coherency Line Size = 64B
Physical Line Partitions = 1
Number of Sets = 1024
Total Size = 262144B (256KB)
Lower Level Invalidate Behavior = Guaranteed
Inclusiveness = Non-Inclusive
Cache Indexing = Direct Mapped
CPUID.B.04.3   1C03C163 03C0003F 00002FFF 00000006
Cache Type = L3 Unified
Self Initializing = Yes
Max Number of Addressable IDs for Logical Processors Sharing This Cache = 16
Max Number of Addressable IDs for Cores in Physical Package = 8
Associativity = 16-way Set Associative
Coherency Line Size = 64B
Physical Line Partitions = 1
Number of Sets = 12288
Total Size = 12582912B (12.0MB)
Lower Level Invalidate Behavior = Guaranteed
Inclusiveness = Inclusive
Cache Indexing = Complex Function
CPUID.B.04.4   00000000 00000000 00000000 00000000
CPUID.B.05     00000040 00000040 00000003 11142120
Smallest Monitor-Line Size = 64B
Largest Monitor-Line Size = 64B
Support Enumeration of Monitor-Mwait extensions = Yes
Support Interruption = Yes
Number of C0 Sub States = 0
Number of C1 Sub States = 2
Number of C2 Sub States = 1
Number of C3 Sub States = 2
Number of C4 Sub States = 4
Number of C5 Sub States = 1
Number of C6 Sub States = 1
Number of C7 Sub States = 1
CPUID.B.06     000027F7 00000002 00000009 00000000
Supported     = TEMP TB ARAT PLN ECMD PTM HWP HWP_Notification HWP_Activity_Window HWP_Energy_Performance_Preference HDC
Not Supported = HWP_Package_Level_Request TBMax HWP_Capabilities HWP_PECI_Override Flexible_HWP Fast_HWP_MSR Ignoring_Idle_Logical_Processor_HWP
Number of Interrupt Thresholds in Digital Thermal Sensor = 2
Hardware Coordination Feedback Capability = No
Performance-Energy Bias Preference = Yes
CPUID.B.07.0   00000000 029C6FBF 40000000 9C002400
Supported     = FSGSBASE IA32_TSC_ADJUST_MSR SGX BMI1 HLE AVX2 SMEP BMI2 Enhanced_REP_MOVSB INVPCID RTM Deprecates_FPU_CS/DS MPX RDSEED ADX SMAP CLFLUSHOPT Intel_Processor_Trace SGX_LC Enumerate_IBRS/IBPB Enumerate_STIBP Enumerate_L1D_FLUSH Enumerate_SSBD
Not Supported = FDP_EXCEPTN_ONLY RDT-M RDT-A AVX512F AVX512DQ AVX512_IFMA CLWB AVX512PF AVX512ER AVX512CD SHA AVX512BW AVX512VL PREFETCHWT1 AVX512_VBMI UMIP PKU OSPKE WAITPKG AVX512_VBMI2 CET_SS GFNI VAES VPCLMULQDQ AVX512_VNNI AVX512_BITALG AVX512_VPOPCNTDQ RDPID CLDEMOTE MOVDIRI MOVDIRI64B AVX512_4VNNIW AVX512_4FMAPS Fast_Short_REP_MOV CET_IBT Enumerate_IA32_ARCH_CAPABILITIES_MSR Enumerate_IA32_CORE_CAPABILITIES_MSR
MAWAU in 64-bit Mode = 0
Hybrid Part = No
CPUID.B.09     00000000 00000000 00000000 00000000
IA32_PLATFORM_DCA_CAP MSR[31:0] = 00000000
CPUID.B.0A     07300404 00000000 00000000 00000603
Performance Monitoring Version ID = 4
Number of GP Performance Monitoring Counters per Logical Processor = 4
Bit Width of GP Performance Monitoring Counter = 48
Supported Events     = Core_cycle Instruction_retired Reference_cycles Last-level_cache_reference Last-level_cache_misses Branch_instruction_retired Branch_mispredict_retired
Not Supported Events =
AnyThread deprecation = No
CPUID.B.0B.0   00000001 00000002 00000100 00000009
Topology Level = 0
Topology Type = SMT
Number of Logical Processors at This Level Type = 2
x2APIC ID shift value = 1
x2APIC ID of the Current Logical Processor = 0x9
CPUID.B.0B.1   00000004 0000000C 00000201 00000009
Topology Level = 1
Topology Type = Core
Number of Logical Processors at This Level Type = 12
x2APIC ID shift value = 4
x2APIC ID of the Current Logical Processor = 0x9
CPUID.B.0B.2   00000000 00000000 00000002 00000009
CPUID.B.0D.0   0000001F 00000440 00000440 00000000
Supported XSAVE States     = x87 SSE(xmm) AVX(ymm) MPX[0] MPX[1]
Not Supported XSAVE States = AVX512[0] AVX512[1] AVX512[2] PKRU
Max Size Required for Enabled Features = 1088
Max Size Required for All Features = 1088
CPUID.B.0D.1   0000000F 00000440 00000100 00000000
XSAVEOPT is available = Yes
Supported     = XSAVEC XGETBV_with_ECX1 XSAVES_and_IA32_XSS
Not Supported =
Size for XSAVE States with IA32_XSS = 1088
Supported IA32_XSS States     =
Not Supported IA32_XSS States = PT HWP
CPUID.B.0F     00000000 00000000 00000000 00000000
Max range of RMID within This Physical Processor = 0
Supported     =
Not Supported = L3_Cache_Intel_RDT_Monitoring
CPUID.E.00     80000008 00000000 00000000 00000000
Maximum Extended Leaf = 80000008
CPUID.E.01     00000000 00000000 00000121 2C100000
Supported     = LAHF64 LZCNT PREFETCHW NX 1GPAGE RDTSCP 64BIT
Not Supported = SYSCALL
CPUID.E.02     65746E49 2952286C 726F4320 4D542865
CPUID.E.03     37692029 3037382D 50432030 20402055
CPUID.E.04     30322E33 007A4847 00000000 00000000
Processor Brand String = Intel(R) Core(TM) i7-8700 CPU @ 3.20GHz
CPUID.E.06     00000000 00000000 01006040 00000000
Cache Line Size = 64B
L2 Associativity = 8-way
Cache Size = 256KB
CPUID.E.07     00000000 00000000 00000000 00000100
Supported     = InvariantTSC
Not Supported =
CPUID.E.08     00003027 00000000 00000000 00000000
Physical Address Bits = 39
Linear Address Bits = 48
```
