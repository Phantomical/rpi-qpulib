#pragma once

namespace qpu
{
	namespace reg
	{
		static constexpr size_t V3D_RANGE = 0x00F20;
#define V3D_OFFSET(x) (volatile void*)((volatile char*)V3D_BASE + x)

		void initialize(volatile void* V3D_BASE);

		volatile void* V3D_IDENT0  = nullptr;
		volatile void* V3D_IDENT1  = nullptr;
		volatile void* V3D_IDENT2  = nullptr;
		volatile void* V3D_SCRATCH = nullptr;
		volatile void* V3D_L2CACTL = nullptr;
		volatile void* V3D_SLCACTL = nullptr;
		volatile void* V3D_INTCTL  = nullptr;
		volatile void* V3D_INTENA  = nullptr;
		volatile void* V3D_INTDIS  = nullptr;
		volatile void* V3D_CT0CS   = nullptr;
		volatile void* V3D_CT1CS   = nullptr;
		volatile void* V3D_CT0EA   = nullptr;
		volatile void* V3D_CT1EA   = nullptr;
		volatile void* V3D_CT0CA   = nullptr;
		volatile void* V3D_CT1CA   = nullptr;
		volatile void* V3D_CT00RA0 = nullptr;
		volatile void* V3D_CT01RA0 = nullptr;
		volatile void* V3D_CT0LC   = nullptr;
		volatile void* V3D_CT1LC   = nullptr;
		volatile void* V3D_CT0PC   = nullptr;
		volatile void* V3D_CT1PC   = nullptr;
		volatile void* V3D_PCS     = nullptr;
		volatile void* V3D_BFC     = nullptr;
		volatile void* V3D_RFC     = nullptr;
		volatile void* V3D_BPCA    = nullptr;
		volatile void* V3D_BPCS    = nullptr;
		volatile void* V3D_BPOA    = nullptr;
		volatile void* V3D_BPOS    = nullptr;
		volatile void* V3D_BXCF    = nullptr;
		volatile void* V3D_SQRSV0  = nullptr;
		volatile void* V3D_SQRSV1  = nullptr;
		volatile void* V3D_SQCNTL  = nullptr;
		volatile void* V3D_SRQPC   = nullptr;
		volatile void* V3D_SRQUA   = nullptr;
		volatile void* V3D_SRQUL   = nullptr;
		volatile void* V3D_SRQCS   = nullptr;
		volatile void* V3D_VPACNTL = nullptr;
		volatile void* V3D_VPMBASE = nullptr;
		volatile void* V3D_PCTRC   = nullptr;
		volatile void* V3D_PCTRE   = nullptr;
		volatile void* V3D_PCTR0   = nullptr;
		volatile void* V3D_PCTRS0  = nullptr;
		volatile void* V3D_PCTR1   = nullptr;
		volatile void* V3D_PCTRS1  = nullptr;
		volatile void* V3D_PCTR2   = nullptr;
		volatile void* V3D_PCTRS2  = nullptr;
		volatile void* V3D_PCTR3   = nullptr;
		volatile void* V3D_PCTRS3  = nullptr;
		volatile void* V3D_PCTR4   = nullptr;
		volatile void* V3D_PCTRS4  = nullptr;
		volatile void* V3D_PCTR5   = nullptr;
		volatile void* V3D_PCTRS5  = nullptr;
		volatile void* V3D_PCTR6   = nullptr;
		volatile void* V3D_PCTRS6  = nullptr;
		volatile void* V3D_PCTR7   = nullptr;
		volatile void* V3D_PCTRS7  = nullptr;
		volatile void* V3D_PCTR8   = nullptr;
		volatile void* V3D_PCTRS8  = nullptr;
		volatile void* V3D_PCTR9   = nullptr;
		volatile void* V3D_PCTRS9  = nullptr;
		volatile void* V3D_PCTR10  = nullptr;
		volatile void* V3D_PCTRS10 = nullptr;
		volatile void* V3D_PCTR11  = nullptr;
		volatile void* V3D_PCTRS11 = nullptr;
		volatile void* V3D_PCTR12  = nullptr;
		volatile void* V3D_PCTRS12 = nullptr;
		volatile void* V3D_PCTR13  = nullptr;
		volatile void* V3D_PCTRS13 = nullptr;
		volatile void* V3D_PCTR14  = nullptr;
		volatile void* V3D_PCTRS14 = nullptr;
		volatile void* V3D_PCTR15  = nullptr;
		volatile void* V3D_PCTRS15 = nullptr;
		volatile void* V3D_DBGE    = nullptr;
		volatile void* V3D_FBDGO   = nullptr;
		volatile void* VED_FBDGB   = nullptr;
		volatile void* V3D_FDBGR   = nullptr;
		volatile void* V3D_FDBGS   = nullptr;
		volatile void* V3D_ERRSTAT = nullptr;
		
	}
}
