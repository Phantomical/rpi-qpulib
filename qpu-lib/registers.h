#pragma once

#include <cstdint>
#include <cstdlib>

namespace qpu
{
	namespace reg
	{
		static constexpr size_t V3D_RANGE = 0x00F20;

		bool initialize();
		void deinitialiez();
		
		extern volatile uint32_t* V3D_IDENT0;
		extern volatile uint32_t* V3D_IDENT1;
		extern volatile uint32_t* V3D_IDENT2;
		extern volatile uint32_t* V3D_SCRATCH;
		extern volatile uint32_t* V3D_L2CACTL;
		extern volatile uint32_t* V3D_SLCACTL;
		extern volatile uint32_t* V3D_INTCTL;
		extern volatile uint32_t* V3D_INTENA;
		extern volatile uint32_t* V3D_INTDIS;
		extern volatile uint32_t* V3D_CT0CS;
		extern volatile uint32_t* V3D_CT1CS;
		extern volatile uint32_t* V3D_CT0EA;
		extern volatile uint32_t* V3D_CT1EA;
		extern volatile uint32_t* V3D_CT0CA;
		extern volatile uint32_t* V3D_CT1CA;
		extern volatile uint32_t* V3D_CT00RA0;
		extern volatile uint32_t* V3D_CT01RA0;
		extern volatile uint32_t* V3D_CT0LC;
		extern volatile uint32_t* V3D_CT1LC;
		extern volatile uint32_t* V3D_CT0PC;
		extern volatile uint32_t* V3D_CT1PC;
		extern volatile uint32_t* V3D_PCS;
		extern volatile uint32_t* V3D_BFC;
		extern volatile uint32_t* V3D_RFC;
		extern volatile uint32_t* V3D_BPCA;
		extern volatile uint32_t* V3D_BPCS;
		extern volatile uint32_t* V3D_BPOA;
		extern volatile uint32_t* V3D_BPOS;
		extern volatile uint32_t* V3D_BXCF;
		extern volatile uint32_t* V3D_SQRSV0;
		extern volatile uint32_t* V3D_SQRSV1;
		extern volatile uint32_t* V3D_SQCNTL;
		extern volatile uint32_t* V3D_SRQPC;
		extern volatile uint32_t* V3D_SRQUA;
		extern volatile uint32_t* V3D_SRQUL;
		extern volatile uint32_t* V3D_SRQCS;
		extern volatile uint32_t* V3D_VPACNTL;
		extern volatile uint32_t* V3D_VPMBASE;
		extern volatile uint32_t* V3D_PCTRC;
		extern volatile uint32_t* V3D_PCTRE;
		extern volatile uint32_t* V3D_PCTR0;
		extern volatile uint32_t* V3D_PCTRS0;
		extern volatile uint32_t* V3D_PCTR1;
		extern volatile uint32_t* V3D_PCTRS1;
		extern volatile uint32_t* V3D_PCTR2;
		extern volatile uint32_t* V3D_PCTRS2;
		extern volatile uint32_t* V3D_PCTR3;
		extern volatile uint32_t* V3D_PCTRS3;
		extern volatile uint32_t* V3D_PCTR4;
		extern volatile uint32_t* V3D_PCTRS4;
		extern volatile uint32_t* V3D_PCTR5;
		extern volatile uint32_t* V3D_PCTRS5;
		extern volatile uint32_t* V3D_PCTR6;
		extern volatile uint32_t* V3D_PCTRS6;
		extern volatile uint32_t* V3D_PCTR7;
		extern volatile uint32_t* V3D_PCTRS7;
		extern volatile uint32_t* V3D_PCTR8;
		extern volatile uint32_t* V3D_PCTRS8;
		extern volatile uint32_t* V3D_PCTR9;
		extern volatile uint32_t* V3D_PCTRS9;
		extern volatile uint32_t* V3D_PCTR10;
		extern volatile uint32_t* V3D_PCTRS10;
		extern volatile uint32_t* V3D_PCTR11;
		extern volatile uint32_t* V3D_PCTRS11;
		extern volatile uint32_t* V3D_PCTR12;
		extern volatile uint32_t* V3D_PCTRS12;
		extern volatile uint32_t* V3D_PCTR13;
		extern volatile uint32_t* V3D_PCTRS13;
		extern volatile uint32_t* V3D_PCTR14;
		extern volatile uint32_t* V3D_PCTRS14;
		extern volatile uint32_t* V3D_PCTR15;
		extern volatile uint32_t* V3D_PCTRS15;
		extern volatile uint32_t* V3D_DBGE;
		extern volatile uint32_t* V3D_FBDGO;
		extern volatile uint32_t* VED_FBDGB;
		extern volatile uint32_t* V3D_FDBGR;
		extern volatile uint32_t* V3D_FDBGS;
		extern volatile uint32_t* V3D_ERRSTAT;

	}
}
