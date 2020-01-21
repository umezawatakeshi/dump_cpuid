#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER)
#include <intrin.h>
#endif

struct cpuid_result
{
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
};

struct xgetbv_result
{
	uint32_t eax;
	uint32_t edx;
};

static inline void cpuid(cpuid_result *result, uint32_t leaf, uint32_t subleaf = 0)
{
#if defined(_MSC_VER)
	__cpuidex((int*)result, leaf, subleaf);
#elif defined(__GNUC__)
	__asm__ __volatile__
	(
		"cpuid"
		:
		"=a"(result->eax),
		"=b"(result->ebx),
		"=c"(result->ecx),
		"=d"(result->edx)
		:
		"a"(leaf),
		"c"(subleaf)
	);
#else
#error
#endif

	char buf[16];
	if (leaf >= 0x80000000)
		sprintf(buf, "E.%02X", leaf - 0x80000000);
	else if (leaf == 4 || leaf == 7 || leaf == 0x0b || leaf == 0x0d || leaf == 0x1f)
		sprintf(buf, "B.%02X.%d", leaf, subleaf);
	else
		sprintf(buf, "B.%02X", leaf);
	printf("CPUID.%-8s %08X %08X %08X %08X\n", buf,
		result->eax, result->ebx, result->ecx, result->edx);
}

static inline const char* yesno(bool b)
{
	return b ? "Yes" : "No";
}

#define SUPIMPL(t, f, value, bitpos, name) \
	do { \
		char* p = (value & (1 << bitpos)) ? t : f; \
		strcat(p, " "); \
		strcat(p, name); \
	} while(0)

#define SUP(value, bitpos, name) SUPIMPL(sup, nsup, value, bitpos, name)
#define NEGSUP(value, bitpos, name) SUPIMPL(nsup, sup, value, bitpos, name)


void basic_leaves()
{
	cpuid_result r;
	uint32_t maxleaf;
	char sup[1024];
	char nsup[1024];
	bool psn_supported;

	union {
		uint32_t reg[3];
		char vistr[13];
	} b0;
	cpuid(&r, 0x0);
	maxleaf = r.eax;
	printf("Maximum Basic Leaf = %08X\n", maxleaf);
	b0.reg[0] = r.ebx;
	b0.reg[1] = r.edx;
	b0.reg[2] = r.ecx;
	b0.vistr[12] = '\0';
	printf("Vendor Identification String = %s\n", b0.vistr);

	if (maxleaf < 0x1)
		return;
	static const char* const proctype_list[4] = {
		"Original OEM Processor",
		"Overdrive Processor",
		"Dual Processor",
		"(reserved)"
	};
	cpuid(&r, 0x1);
	printf("Processor Type = %s\n", proctype_list[(r.eax >> 12) & 3]);
	printf("Basic Family ID = %X\n", (r.eax >> 8) & 0xf);
	printf("Extended Family ID = %X\n", (r.eax >> 20) & 0xff);
	printf("Basic Model ID = %X\n", (r.eax >> 4) & 0xf);
	printf("Extended Model ID = %02X\n", (r.eax >> 16) & 0xf);
	unsigned family = (r.eax >> 8) & 0xf;
	if (family == 0xf)
		family += (r.eax >> 20) & 0xff;
	unsigned model = (r.eax >> 4) & 0xf;
	if (family == 0x6 || family == 0xf)
		model += ((r.eax >> 16) & 0xf) << 4;
	printf("Display Family ID = %02X\n", family);
	printf("Display Model ID = %02X\n", model);
	printf("Brand Index = %d\n", r.ebx & 0xff);
	printf("CLFLUSH Line Size = %dB\n", ((r.ebx >> 8) & 0xff) * 8);
	printf("HT Threads = %d\n", (r.ebx >> 16) & 0xff);
	*sup = *nsup = '\0';
	SUP(r.ecx,  0, "SSE3");
	SUP(r.ecx,  1, "PCLMULQDQ");
	SUP(r.ecx,  2, "DTES64");
	SUP(r.ecx,  3, "MONITOR");
	SUP(r.ecx,  4, "DS-CPL");
	SUP(r.ecx,  5, "VMX");
	SUP(r.ecx,  6, "SMX");
	SUP(r.ecx,  7, "EIST");
	SUP(r.ecx,  8, "TM2");
	SUP(r.ecx,  9, "SSSE3");
	SUP(r.ecx, 10, "CNXT-ID");
	SUP(r.ecx, 11, "SDBG");
	SUP(r.ecx, 12, "FMA");
	SUP(r.ecx, 13, "CMPXCHG16B");
	SUP(r.ecx, 14, "xTPR_Update_Control");
	SUP(r.ecx, 15, "PDCM");
	SUP(r.ecx, 17, "PCID");
	SUP(r.ecx, 18, "DCA");
	SUP(r.ecx, 19, "SSE4_1");
	SUP(r.ecx, 20, "SSE4_2");
	SUP(r.ecx, 21, "x2APIC");
	SUP(r.ecx, 22, "MOVBE");
	SUP(r.ecx, 23, "POPCNT");
	SUP(r.ecx, 24, "TSC-Deadline");
	SUP(r.ecx, 25, "AESNI");
	SUP(r.ecx, 26, "XSAVE");
	SUP(r.ecx, 27, "OSXSAVE");
	SUP(r.ecx, 28, "AVX");
	SUP(r.ecx, 29, "F16C");
	SUP(r.ecx, 30, "RDRAND");
	SUP(r.edx,  0, "FPU");
	SUP(r.edx,  1, "VME");
	SUP(r.edx,  2, "DE");
	SUP(r.edx,  3, "PSE");
	SUP(r.edx,  4, "TSC");
	SUP(r.edx,  5, "MSR");
	SUP(r.edx,  6, "PAE");
	SUP(r.edx,  7, "MCE");
	SUP(r.edx,  8, "CX8");
	SUP(r.edx,  9, "APIC");
	SUP(r.edx, 11, "SEP");
	SUP(r.edx, 12, "MTRR");
	SUP(r.edx, 13, "PGE");
	SUP(r.edx, 14, "MCA");
	SUP(r.edx, 15, "CMOV");
	SUP(r.edx, 16, "PAT");
	SUP(r.edx, 17, "PSE-36");
	SUP(r.edx, 18, "PSN");
	SUP(r.edx, 19, "CLFLUSH");
	SUP(r.edx, 21, "DS");
	SUP(r.edx, 22, "ACPI");
	SUP(r.edx, 23, "MMX");
	SUP(r.edx, 24, "FXSAVE");
	SUP(r.edx, 25, "SSE");
	SUP(r.edx, 26, "SSE2");
	SUP(r.edx, 27, "SS");
	SUP(r.edx, 28, "HTT");
	SUP(r.edx, 29, "TM");
	SUP(r.edx, 31, "PBE");
	printf("Supported     =%s\n", sup);
	printf("Not Supported =%s\n", nsup);
	psn_supported = r.edx & (1 << 18);

	if (maxleaf < 0x2)
		return;
	cpuid(&r, 0x2);
	// TODO: implement

	if (maxleaf < 0x3)
		return;
	cpuid(&r, 0x3);
	// Processor Serial Number Leaf

	if (maxleaf < 0x4)
		return;
	static const char* const cachetype_list[4] = {
		"(null)",
		"Data",
		"Instruction",
		"Unified",
	};
	for (uint32_t idx = 0; idx < 0xffffffff /* for safely */; ++idx) {
		cpuid(&r, 0x4, idx);
		auto level = (r.eax >> 5) & 7;
		auto cachetype = r.eax & 0x1f;
		if (cachetype == 0)
			break;
		auto cachetype_str = cachetype < 4 ? cachetype_list[cachetype] : "(reserved)";
		printf("Cache Type = L%d %s\n", level, cachetype_str);
		printf("Self Initializing = %s\n", yesno(r.eax & (1 << 8)));
		printf("Max Number of Addressable IDs for Logical Processors Sharing This Cache = %d\n", ((r.eax >> 14) & 0x3ff) + 1);
		printf("Max Number of Addressable IDs for Cores in Physical Package = %d\n", ((r.eax >> 26) & 0x3ff) + 1);
		printf("Associativity = ");
		auto ways = ((r.ebx >> 22) & 0x3ff) + 1;
		auto linesize = (r.ebx & 0xfff) + 1;
		auto partitions = ((r.ebx >> 12) & 0x3ff) + 1;
		auto sets = r.ecx + 1;
		if (r.eax & (1 << 9))
			printf("Full Associative\n");
		else if ((r.ebx >> 22) & 0x3ff == 0)
			printf("Direct Mapped\n");
		else
			printf("%d-way Set Associative\n", ways);
		printf("Coherency Line Size = %dB\n", linesize);
		printf("Physical Line Partitions = %d\n", partitions);
		printf("Number of Sets = %d\n", sets);
		auto totalsize = linesize * partitions * ways * sets;
		printf("Total Size = %dB (", totalsize);
		if (totalsize < 1024*1024)
			printf("%dKB", totalsize / 1024);
		else
			printf("%.1fMB", (double)totalsize / (1024*1024));
		printf(")\n");
		printf("Lower Level Invalidate Behavior = %s\n", r.edx & 1 ? "Not Guaranteed" : "Guaranteed");
		printf("Inclusiveness = %s\n", r.edx & (1 << 1) ? "Inclusive" : "Non-Inclusive");
		printf("Cache Indexing = %s\n", r.edx & (1 << 2) ? "Complex Function" : "Direct Mapped");
	}

	if (maxleaf < 0x5)
		return;
	cpuid(&r, 0x5);
	printf("Smallest Monitor-Line Size = %dB\n", r.eax & 0xffff);
	printf("Largest Monitor-Line Size = %dB\n", r.ebx & 0xffff);
	printf("Support Enumeration of Monitor-Mwait extensions = %s\n", yesno(r.ecx & (1 << 0)));
	printf("Support Interruption = %s\n", yesno(r.ecx & (1 << 1)));
	for (int state = 0; state <= 7; ++state)
		printf("Number of C%d Sub States = %d\n", state, (r.edx >> (state * 4)) & 0xf);

	if (maxleaf < 0x6)
		return;
	cpuid(&r, 0x6);
	*sup = *nsup = '\0';
	SUP(r.eax,  0, "TEMP");
	SUP(r.eax,  1, "TB");
	SUP(r.eax,  2, "ARAT");
	SUP(r.eax,  4, "PLN");
	SUP(r.eax,  5, "ECMD");
	SUP(r.eax,  6, "PTM");
	SUP(r.eax,  7, "HWP");
	SUP(r.eax,  8, "HWP_Notification");
	SUP(r.eax,  9, "HWP_Activity_Window");
	SUP(r.eax, 10, "HWP_Energy_Performance_Preference");
	SUP(r.eax, 11, "HWP_Package_Level_Request");
	SUP(r.eax, 13, "HDC");
	SUP(r.eax, 14, "TBMax");
	SUP(r.eax, 15, "HWP_Capabilities");
	SUP(r.eax, 16, "HWP_PECI_Override");
	SUP(r.eax, 17, "Flexible_HWP");
	SUP(r.eax, 18, "Fast_HWP_MSR");
	SUP(r.eax, 20, "Ignoring_Idle_Logical_Processor_HWP");
	printf("Supported     =%s\n", sup);
	printf("Not Supported =%s\n", nsup);
	printf("Number of Interrupt Thresholds in Digital Thermal Sensor = %d\n", r.ebx & 0xf);
	printf("Hardware Coordination Feedback Capability = %s\n", yesno(r.ecx & (1 << 1)));
	printf("Performance-Energy Bias Preference = %s\n", yesno(r.ecx & (1 << 3)));

	if (maxleaf < 0x7)
		return;
	cpuid(&r, 0x7, 0);
	auto max7subleaf = r.eax;
	*sup = *nsup = '\0';
	SUP(r.ebx,  0, "FSGSBASE");
	SUP(r.ebx,  1, "IA32_TSC_ADJUST_MSR");
	SUP(r.ebx,  2, "SGX");
	SUP(r.ebx,  3, "BMI1");
	SUP(r.ebx,  4, "HLE");
	SUP(r.ebx,  5, "AVX2");
	SUP(r.ebx,  6, "FDP_EXCEPTN_ONLY");
	SUP(r.ebx,  7, "SMEP");
	SUP(r.ebx,  8, "BMI2");
	SUP(r.ebx,  9, "Enhanced_REP_MOVSB");
	SUP(r.ebx, 10, "INVPCID");
	SUP(r.ebx, 11, "RTM");
	SUP(r.ebx, 12, "RDT-M");
	SUP(r.ebx, 13, "Deprecates_FPU_CS/DS");
	SUP(r.ebx, 14, "MPX");
	SUP(r.ebx, 15, "RDT-A");
	SUP(r.ebx, 16, "AVX512F");
	SUP(r.ebx, 17, "AVX512DQ");
	SUP(r.ebx, 18, "RDSEED");
	SUP(r.ebx, 19, "ADX");
	SUP(r.ebx, 20, "SMAP");
	SUP(r.ebx, 21, "AVX512_IFMA");
	SUP(r.ebx, 23, "CLFLUSHOPT");
	SUP(r.ebx, 24, "CLWB");
	SUP(r.ebx, 25, "Intel_Processor_Trace");
	SUP(r.ebx, 26, "AVX512PF");
	SUP(r.ebx, 27, "AVX512ER");
	SUP(r.ebx, 28, "AVX512CD");
	SUP(r.ebx, 29, "SHA");
	SUP(r.ebx, 30, "AVX512BW");
	SUP(r.ebx, 31, "AVX512VL");
	SUP(r.ecx,  0, "PREFETCHWT1");
	SUP(r.ecx,  1, "AVX512_VBMI");
	SUP(r.ecx,  2, "UMIP");
	SUP(r.ecx,  3, "PKU");
	SUP(r.ecx,  4, "OSPKE");
	SUP(r.ecx,  5, "WAITPKG");
	SUP(r.ecx,  6, "AVX512_VBMI2");
	SUP(r.ecx,  7, "CET_SS");
	SUP(r.ecx,  8, "GFNI");
	SUP(r.ecx,  9, "VAES");
	SUP(r.ecx, 10, "VPCLMULQDQ");
	SUP(r.ecx, 11, "AVX512_VNNI");
	SUP(r.ecx, 12, "AVX512_BITALG");
	SUP(r.ecx, 14, "AVX512_VPOPCNTDQ");
	SUP(r.ecx, 22, "RDPID");
	SUP(r.ecx, 25, "CLDEMOTE");
	SUP(r.ecx, 27, "MOVDIRI");
	SUP(r.ecx, 28, "MOVDIRI64B");
	SUP(r.ecx, 30, "SGX_LC");
	SUP(r.edx,  2, "AVX512_4VNNIW");
	SUP(r.edx,  3, "AVX512_4FMAPS");
	SUP(r.edx,  4, "Fast_Short_REP_MOV");
	SUP(r.edx, 20, "CET_IBT");
	SUP(r.edx, 26, "Enumerate_IBRS/IBPB");
	SUP(r.edx, 27, "Enumerate_STIBP");
	SUP(r.edx, 28, "Enumerate_L1D_FLUSH");
	SUP(r.edx, 29, "Enumerate_IA32_ARCH_CAPABILITIES_MSR");
	SUP(r.edx, 30, "Enumerate_IA32_CORE_CAPABILITIES_MSR");
	SUP(r.edx, 31, "Enumerate_SSBD");
	printf("Supported     =%s\n", sup);
	printf("Not Supported =%s\n", nsup);
	printf("MAWAU in 64-bit Mode = %d\n", (r.ecx >> 17) & 0x1f);
	printf("Hybrid Part = %s\n", yesno(r.edx & (1 << 15)));

	for (uint32_t subleaf = 1; subleaf <= max7subleaf; ++subleaf)
		cpuid(&r, 0x7, subleaf);

	/* Leaf 0x8 seems not to exist */

	if (maxleaf < 0x9)
		return;
	cpuid(&r, 0x9);
	printf("IA32_PLATFORM_DCA_CAP MSR[31:0] = %08X\n", r.eax);

	if (maxleaf < 0xa)
		return;
	cpuid(&r, 0xa);
	printf("Performance Monitoring Version ID = %d\n", r.eax & 0xff);
	printf("Number of GP Performance Monitoring Counters per Logical Processor = %d\n", (r.eax >> 8) & 0xff);
	printf("Bit Width of GP Performance Monitoring Counter = %d\n", (r.eax >> 16) & 0xff);
	auto maxebxbit = (r.eax >> 24) & 0xff;
	*sup = *nsup = '\0';
	if (maxebxbit > 0) NEGSUP(r.ebx,  0, "Core_cycle");
	if (maxebxbit > 1) NEGSUP(r.ebx,  1, "Instruction_retired");
	if (maxebxbit > 2) NEGSUP(r.ebx,  2, "Reference_cycles");
	if (maxebxbit > 3) NEGSUP(r.ebx,  3, "Last-level_cache_reference");
	if (maxebxbit > 4) NEGSUP(r.ebx,  4, "Last-level_cache_misses");
	if (maxebxbit > 5) NEGSUP(r.ebx,  5, "Branch_instruction_retired");
	if (maxebxbit > 6) NEGSUP(r.ebx,  6, "Branch_mispredict_retired");
	printf("Supported Events     =%s\n", sup);
	printf("Not Supported Events =%s\n", nsup);
	if (r.eax & 0xff > 1) {
		printf("Number of FF Performance Counters = %d\n", r.edx & 0x1f);
		printf("Bit Width of FF Performance Monitoring Counter = %d\n", (r.edx >> 5) & 0xff);
	}
	printf("AnyThread deprecation = %s\n", yesno(r.edx & (1 << 15)));

	if (maxleaf < 0xb)
		return;
	for (uint32_t subleaf = 0;; ++subleaf) {
		cpuid(&r, 0xb, subleaf);
		auto topotype = (r.ecx >> 8) & 0xff;
		if (topotype == 0)
			break;
		static const char* const topotype_list[3] = {
			"(invalid)",
			"SMT",
			"Core",
		};
		printf("Topology Level = %d\n", r.ecx & 0xff);
		auto topotype_str = topotype < 3 ? topotype_list[topotype] : "(reserved)";
		printf("Topology Type = %s\n", topotype_str);
		printf("Number of Logical Processors at This Level Type = %d\n", r.ebx & 0xffff);
		printf("x2APIC ID shift value = %d\n", r.eax & 0x1f);
		printf("x2APIC ID of the Current Logical Processor = 0x%x\n", r.edx);
	}

	if (maxleaf < 0xd)
		return;
	cpuid(&r, 0xd, 0);
	*sup = *nsup = '\0';
	SUP(r.eax,  0, "x87");
	SUP(r.eax,  1, "SSE(xmm)");
	SUP(r.eax,  2, "AVX(ymm)");
	SUP(r.eax,  3, "MPX[0]");
	SUP(r.eax,  4, "MPX[1]");
	SUP(r.eax,  5, "AVX512[0]");
	SUP(r.eax,  6, "AVX512[1]");
	SUP(r.eax,  7, "AVX512[2]");
	//SUP(r.eax,  8, "IA32_XSS");
	SUP(r.eax,  9, "PKRU");
	//SUP(r.eax, 13, "IA32_XSS");
	printf("Supported XSAVE States     =%s\n", sup);
	printf("Not Supported XSAVE States =%s\n", nsup);
	printf("Max Size Required for Enabled Features = %d\n", r.ebx);
	printf("Max Size Required for All Features = %d\n", r.ecx);
	//printf("...", r.edx);

	cpuid(&r, 0xd, 1);
	printf("XSAVEOPT is available = %s\n", yesno(r.eax & (1 >> 0)));
	*sup = *nsup = '\0';
	SUP(r.eax,  1, "XSAVEC");
	SUP(r.eax,  2, "XGETBV_with_ECX1");
	SUP(r.eax,  3, "XSAVES_and_IA32_XSS");
	printf("Supported     =%s\n", sup);
	printf("Not Supported =%s\n", nsup);
	printf("Size for XSAVE States with IA32_XSS = %d\n", r.ebx);
	*sup = *nsup = '\0';
	SUP(r.eax,  8, "PT");
	SUP(r.eax, 13, "HWP");
	printf("Supported IA32_XSS States     =%s\n", sup);
	printf("Not Supported IA32_XSS States =%s\n", nsup);
	//printf("...", r.edx);

	//cpuid(&r, 0xd, 2);

	if (maxleaf < 0xf)
		return;
	cpuid(&r, 0xf, 0);
	printf("Max range of RMID within This Physical Processor = %d\n", r.ebx);
	auto leaf_0f_bitmap = r.edx;
	*sup = *nsup = '\0';
	SUP(r.edx,  1, "L3_Cache_Intel_RDT_Monitoring");
	printf("Supported     =%s\n", sup);
	printf("Not Supported =%s\n", nsup);

	if (leaf_0f_bitmap & (1 << 1)) {
		cpuid(&r, 0xf, 1);
		printf("Conversion factor = %d\n", r.ebx);
		printf("Max range of RMID of L3 Cache Monitoring = %d\n", r.ecx);
		*sup = *nsup = '\0';
		SUP(r.edx,  0, "Occupancy");
		SUP(r.edx,  1, "Total_Bandwidth");
		SUP(r.edx,  2, "Local_Bandwidth");
		printf("Supported L3 Monitoring     =%s\n", sup);
		printf("Not Supported L3 Monitoring =%s\n", nsup);
	}

	/*
	cpuid(&r, 0x10, 0);
	cpuid(&r, 0x12, 0);
	cpuid(&r, 0x14, 0);
	cpuid(&r, 0x15);
	cpuid(&r, 0x16);
	cpuid(&r, 0x17, 0);
	cpuid(&r, 0x18, 0);
	cpuid(&r, 0x1a, 0);
	*/

	if (maxleaf < 0x1f)
		return;
	for (uint32_t subleaf = 0;; ++subleaf) {
		cpuid(&r, 0x1f, subleaf);
		auto topotype = (r.ecx >> 8) & 0xff;
		if (topotype == 0)
			break;
		static const char* const topotype_list[6] = {
			"(invalid)",
			"SMT",
			"Core",
			"Module",
			"Tile",
			"Die",
		};
		printf("Topology Level = %d\n", r.ecx & 0xff);
		auto topotype_str = topotype < 6 ? topotype_list[topotype] : "(reserved)";
		printf("Topology Type = %s\n", topotype_str);
		printf("Number of Logical Processors at This Level Type = %d\n", r.ebx & 0xffff);
		printf("x2APIC ID shift value = %d\n", r.eax & 0x1f);
		printf("x2APIC ID of the Current Logical Processor = 0x%x\n", r.edx);
	}

#if 0
	SUP(r.ecx,  0, "");
	SUP(r.ecx,  1, "");
	SUP(r.ecx,  2, "");
	SUP(r.ecx,  3, "");
	SUP(r.ecx,  4, "");
	SUP(r.ecx,  5, "");
	SUP(r.ecx,  6, "");
	SUP(r.ecx,  7, "");
	SUP(r.ecx,  8, "");
	SUP(r.ecx,  9, "");
	SUP(r.ecx, 10, "");
	SUP(r.ecx, 11, "");
	SUP(r.ecx, 12, "");
	SUP(r.ecx, 13, "");
	SUP(r.ecx, 14, "");
	SUP(r.ecx, 15, "");
	SUP(r.ecx, 16, "");
	SUP(r.ecx, 17, "");
	SUP(r.ecx, 18, "");
	SUP(r.ecx, 19, "");
	SUP(r.ecx, 20, "");
	SUP(r.ecx, 21, "");
	SUP(r.ecx, 22, "");
	SUP(r.ecx, 23, "");
	SUP(r.ecx, 24, "");
	SUP(r.ecx, 25, "");
	SUP(r.ecx, 26, "");
	SUP(r.ecx, 27, "");
	SUP(r.ecx, 28, "");
	SUP(r.ecx, 29, "");
	SUP(r.ecx, 30, "");
	SUP(r.ecx, 31, "");
#endif
}

void extended_leaves()
{
	cpuid_result r;
	uint32_t maxleaf;
	char sup[1024];
	char nsup[1024];

	cpuid(&r, 0x80000000);
	maxleaf = r.eax;
	printf("Maximum Extended Leaf = %08X\n", maxleaf);

	if (maxleaf < 0x80000001)
		return;
	cpuid(&r, 0x80000001);
	*sup = *nsup = '\0';
	SUP(r.ecx,  0, "LAHF64");
	SUP(r.ecx,  5, "LZCNT");
	SUP(r.ecx,  8, "PREFETCHW");
	SUP(r.edx, 11, "SYSCALL");
	SUP(r.edx, 20, "NX");
	SUP(r.edx, 26, "1GPAGE");
	SUP(r.edx, 27, "RDTSCP");
	SUP(r.edx, 29, "64BIT");
	printf("Supported     =%s\n", sup);
	printf("Not Supported =%s\n", nsup);

	if (maxleaf < 0x80000004)
		return;
	union {
		cpuid_result r[3];
		char pbstr[49];
	} e2;
	cpuid(&e2.r[0], 0x80000002);
	cpuid(&e2.r[1], 0x80000003);
	cpuid(&e2.r[2], 0x80000004);
	e2.pbstr[48] = '\0';
	printf("Processor Brand String = %s\n", e2.pbstr);

	if (maxleaf < 0x80000006)
		return;
	static const char* const l2assoc_list[16] = {
		"disabled",
		"direct mapped",
		"2-way",
		"(reserved)",
		"4-way",
		"(reserved)",
		"8-way",
		"(see leaf 4-2)",
		"16-way",
		"(reserved)",
		"32-way",
		"48-way",
		"64-way",
		"96-way",
		"128-way",
		"fully associative"
	};
	cpuid(&r, 0x80000006);
	printf("Cache Line Size = %dB\n", r.ecx & 0xff);
	printf("L2 Associativity = %s\n", l2assoc_list[(r.ecx >> 12) & 0xf]);
	printf("Cache Size = %dKB\n", r.ecx >> 16);

	if (maxleaf < 0x80000007)
		return;
	cpuid(&r, 0x80000007);
	*sup = *nsup = '\0';
	SUP(r.edx, 8, "InvariantTSC");
	printf("Supported     =%s\n", sup);
	printf("Not Supported =%s\n", nsup);

	if (maxleaf < 0x80000008)
		return;
	cpuid(&r, 0x80000008);
	printf("Physical Address Bits = %d\n", r.eax & 0xff);
	printf("Linear Address Bits = %d\n", (r.eax >> 8) & 0xff);

	for (uint32_t leaf = 0x80000009; leaf <= maxleaf; ++leaf) {
		cpuid(&r, leaf);
	}
}

int main(void)
{
	basic_leaves();
	extended_leaves();
	return 0;
}
