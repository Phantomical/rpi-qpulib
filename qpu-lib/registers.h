#pragma once

#include <cstdint>

namespace qpu
{
	namespace reg
	{
		static constexpr size_t V3D_RANGE = 0x00F20;

		void initialize(volatile void* V3D_BASE);

		volatile uint32_t* V3D_IDENT0  = nullptr;
		volatile uint32_t* V3D_IDENT1  = nullptr;
		volatile uint32_t* V3D_IDENT2  = nullptr;
		volatile uint32_t* V3D_SCRATCH = nullptr;
		volatile uint32_t* V3D_L2CACTL = nullptr;
		volatile uint32_t* V3D_SLCACTL = nullptr;
		volatile uint32_t* V3D_INTCTL  = nullptr;
		volatile uint32_t* V3D_INTENA  = nullptr;
		volatile uint32_t* V3D_INTDIS  = nullptr;
		volatile uint32_t* V3D_CT0CS   = nullptr;
		volatile uint32_t* V3D_CT1CS   = nullptr;
		volatile uint32_t* V3D_CT0EA   = nullptr;
		volatile uint32_t* V3D_CT1EA   = nullptr;
		volatile uint32_t* V3D_CT0CA   = nullptr;
		volatile uint32_t* V3D_CT1CA   = nullptr;
		volatile uint32_t* V3D_CT00RA0 = nullptr;
		volatile uint32_t* V3D_CT01RA0 = nullptr;
		volatile uint32_t* V3D_CT0LC   = nullptr;
		volatile uint32_t* V3D_CT1LC   = nullptr;
		volatile uint32_t* V3D_CT0PC   = nullptr;
		volatile uint32_t* V3D_CT1PC   = nullptr;
		volatile uint32_t* V3D_PCS     = nullptr;
		volatile uint32_t* V3D_BFC     = nullptr;
		volatile uint32_t* V3D_RFC     = nullptr;
		volatile uint32_t* V3D_BPCA    = nullptr;
		volatile uint32_t* V3D_BPCS    = nullptr;
		volatile uint32_t* V3D_BPOA    = nullptr;
		volatile uint32_t* V3D_BPOS    = nullptr;
		volatile uint32_t* V3D_BXCF    = nullptr;
		volatile uint32_t* V3D_SQRSV0  = nullptr;
		volatile uint32_t* V3D_SQRSV1  = nullptr;
		volatile uint32_t* V3D_SQCNTL  = nullptr;
		volatile uint32_t* V3D_SRQPC   = nullptr;
		volatile uint32_t* V3D_SRQUA   = nullptr;
		volatile uint32_t* V3D_SRQUL   = nullptr;
		volatile uint32_t* V3D_SRQCS   = nullptr;
		volatile uint32_t* V3D_VPACNTL = nullptr;
		volatile uint32_t* V3D_VPMBASE = nullptr;
		volatile uint32_t* V3D_PCTRC   = nullptr;
		volatile uint32_t* V3D_PCTRE   = nullptr;
		volatile uint32_t* V3D_PCTR0   = nullptr;
		volatile uint32_t* V3D_PCTRS0  = nullptr;
		volatile uint32_t* V3D_PCTR1   = nullptr;
		volatile uint32_t* V3D_PCTRS1  = nullptr;
		volatile uint32_t* V3D_PCTR2   = nullptr;
		volatile uint32_t* V3D_PCTRS2  = nullptr;
		volatile uint32_t* V3D_PCTR3   = nullptr;
		volatile uint32_t* V3D_PCTRS3  = nullptr;
		volatile uint32_t* V3D_PCTR4   = nullptr;
		volatile uint32_t* V3D_PCTRS4  = nullptr;
		volatile uint32_t* V3D_PCTR5   = nullptr;
		volatile uint32_t* V3D_PCTRS5  = nullptr;
		volatile uint32_t* V3D_PCTR6   = nullptr;
		volatile uint32_t* V3D_PCTRS6  = nullptr;
		volatile uint32_t* V3D_PCTR7   = nullptr;
		volatile uint32_t* V3D_PCTRS7  = nullptr;
		volatile uint32_t* V3D_PCTR8   = nullptr;
		volatile uint32_t* V3D_PCTRS8  = nullptr;
		volatile uint32_t* V3D_PCTR9   = nullptr;
		volatile uint32_t* V3D_PCTRS9  = nullptr;
		volatile uint32_t* V3D_PCTR10  = nullptr;
		volatile uint32_t* V3D_PCTRS10 = nullptr;
		volatile uint32_t* V3D_PCTR11  = nullptr;
		volatile uint32_t* V3D_PCTRS11 = nullptr;
		volatile uint32_t* V3D_PCTR12  = nullptr;
		volatile uint32_t* V3D_PCTRS12 = nullptr;
		volatile uint32_t* V3D_PCTR13  = nullptr;
		volatile uint32_t* V3D_PCTRS13 = nullptr;
		volatile uint32_t* V3D_PCTR14  = nullptr;
		volatile uint32_t* V3D_PCTRS14 = nullptr;
		volatile uint32_t* V3D_PCTR15  = nullptr;
		volatile uint32_t* V3D_PCTRS15 = nullptr;
		volatile uint32_t* V3D_DBGE    = nullptr;
		volatile uint32_t* V3D_FBDGO   = nullptr;
		volatile uint32_t* VED_FBDGB   = nullptr;
		volatile uint32_t* V3D_FDBGR   = nullptr;
		volatile uint32_t* V3D_FDBGS   = nullptr;
		volatile uint32_t* V3D_ERRSTAT = nullptr;
		
	}
}
