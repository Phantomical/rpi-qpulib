
#include "registers.h"
#include "mailbox.h"

#ifdef HAVE_DLSYM_H
#include <dlfcn.h>
#endif

namespace qpu
{
	namespace reg
	{
		void* base_addr = nullptr;
		uint32_t peri_addr = 0;
		uint32_t peri_size = 0;

#ifdef HAVE_DLSYM_H
		volatile void* map_base_addr()
		{
			if (!!base_addr)
				return base_addr;

			uint32_t(*bcm_host_get_peripheral_address)(void);
			uint32_t(*bcm_host_get_peripheral_size)   (void);

			void* handle = dlopen("libbcm_host.so", RTLD_LAZY);

			if (!handle)
				return nullptr;
						
			*(void **) (&bcm_host_get_peripheral_address) = dlsym(handle, "bcm_host_get_peripheral_address");
			*(void **) (&bcm_host_get_peripheral_size)    = dlsym(handle, "bcm_host_get_peripheral_size");

			if (!bcm_host_get_peripheral_address ||
				!bcm_host_get_peripheral_size)
			{
				dlclose(handle);
				return nullptr;
			}

			peri_addr = bcm_host_get_peripheral_address();
			peri_size = bcm_host_get_peripheral_size();

			dlclose(handle);

			return base_addr = mapmem(peri_addr, peri_size);
		}
#else
		volatile void* map_base_addr()
		{
			return nullptr;
		}
#endif

		void deinitialize()
		{
			if (!!base_addr)
			{
				unmapmem(base_addr, peri_size);
				peri_addr = 0;
				peri_size = 0;
			}
		}
#define V3D_OFFSET(x) (volatile uint32_t*)((volatile char*)V3D_BASE + x)
		bool initialize()
		{
			volatile void* V3D_BASE = map_base_addr();

			if (!V3D_BASE)
				return false;

			V3D_IDENT0  = V3D_OFFSET(0x00000);
			V3D_IDENT1  = V3D_OFFSET(0x00004);
			V3D_IDENT2  = V3D_OFFSET(0x00008);
			V3D_SCRATCH = V3D_OFFSET(0x00010);
			V3D_L2CACTL = V3D_OFFSET(0x00020);
			V3D_SLCACTL = V3D_OFFSET(0x00024);
			V3D_INTCTL  = V3D_OFFSET(0x00030);
			V3D_INTENA  = V3D_OFFSET(0x00034);
			V3D_INTDIS  = V3D_OFFSET(0x00038);
			V3D_CT0CS   = V3D_OFFSET(0x00100);
			V3D_CT1CS   = V3D_OFFSET(0x00104);
			V3D_CT0EA   = V3D_OFFSET(0x00108);
			V3D_CT1EA   = V3D_OFFSET(0x0010C);
			V3D_CT0CA   = V3D_OFFSET(0x00110);
			V3D_CT1CA   = V3D_OFFSET(0x00114);
			V3D_CT00RA0 = V3D_OFFSET(0x00118);
			V3D_CT01RA0 = V3D_OFFSET(0x0011C);
			V3D_CT0LC   = V3D_OFFSET(0x00120);
			V3D_CT1LC   = V3D_OFFSET(0x00124);
			V3D_CT0PC   = V3D_OFFSET(0x00128);
			V3D_CT1PC   = V3D_OFFSET(0x0012C);
			V3D_PCS     = V3D_OFFSET(0x00130);
			V3D_BFC     = V3D_OFFSET(0x00134);
			V3D_RFC     = V3D_OFFSET(0x00138);
			V3D_BPCA    = V3D_OFFSET(0x00300);
			V3D_BPCS    = V3D_OFFSET(0x00304);
			V3D_BPOA    = V3D_OFFSET(0x00308);
			V3D_BPOS    = V3D_OFFSET(0x0030C);
			V3D_BXCF    = V3D_OFFSET(0x00310);
			V3D_SQRSV0  = V3D_OFFSET(0x00410);
			V3D_SQRSV1  = V3D_OFFSET(0x00414);
			V3D_SQCNTL  = V3D_OFFSET(0x00418);
			V3D_SRQPC   = V3D_OFFSET(0x00430);
			V3D_SRQUA   = V3D_OFFSET(0x00434);
			V3D_SRQUL   = V3D_OFFSET(0x00438);
			V3D_SRQCS   = V3D_OFFSET(0x0043C);
			V3D_VPACNTL = V3D_OFFSET(0x00500);
			V3D_VPMBASE = V3D_OFFSET(0x00504);
			V3D_PCTRC   = V3D_OFFSET(0x00670);
			V3D_PCTRE   = V3D_OFFSET(0x00674);
			V3D_PCTR0   = V3D_OFFSET(0x00680);
			V3D_PCTRS0  = V3D_OFFSET(0x00684);
			V3D_PCTR1   = V3D_OFFSET(0x00688);
			V3D_PCTRS1  = V3D_OFFSET(0x0068C);
			V3D_PCTR2   = V3D_OFFSET(0x00690);
			V3D_PCTRS2  = V3D_OFFSET(0x00694);
			V3D_PCTR3   = V3D_OFFSET(0x00698);
			V3D_PCTRS3  = V3D_OFFSET(0x0069C);
			V3D_PCTR4   = V3D_OFFSET(0x006A0);
			V3D_PCTRS4  = V3D_OFFSET(0x006A4);
			V3D_PCTR5   = V3D_OFFSET(0x006A8);
			V3D_PCTRS5  = V3D_OFFSET(0x006AC);
			V3D_PCTR6   = V3D_OFFSET(0x006B0);
			V3D_PCTRS6  = V3D_OFFSET(0x006B4);
			V3D_PCTR7   = V3D_OFFSET(0x006B8);
			V3D_PCTRS7  = V3D_OFFSET(0x006BC);
			V3D_PCTR8   = V3D_OFFSET(0x006C0);
			V3D_PCTRS8  = V3D_OFFSET(0x006C4);
			V3D_PCTR9   = V3D_OFFSET(0x006C8);
			V3D_PCTRS9  = V3D_OFFSET(0x006CC);
			V3D_PCTR10  = V3D_OFFSET(0x006D0);
			V3D_PCTRS10 = V3D_OFFSET(0x006D4);
			V3D_PCTR11  = V3D_OFFSET(0x006D8);
			V3D_PCTRS11 = V3D_OFFSET(0x006DC);
			V3D_PCTR12  = V3D_OFFSET(0x006E0);
			V3D_PCTRS12 = V3D_OFFSET(0x006E4);
			V3D_PCTR13  = V3D_OFFSET(0x006E8);
			V3D_PCTRS13 = V3D_OFFSET(0x006EC);
			V3D_PCTR14  = V3D_OFFSET(0x006F0);
			V3D_PCTRS14 = V3D_OFFSET(0x006F4);
			V3D_PCTR15  = V3D_OFFSET(0x006F8);
			V3D_PCTRS15 = V3D_OFFSET(0x006FC);
			V3D_DBGE    = V3D_OFFSET(0x00F00);
			V3D_FBDGO   = V3D_OFFSET(0x00F04);
			VED_FBDGB   = V3D_OFFSET(0x00F08);
			V3D_FDBGR   = V3D_OFFSET(0x00F0C);
			V3D_FDBGS   = V3D_OFFSET(0x00F10);
			V3D_ERRSTAT = V3D_OFFSET(0x00F20);
		
			return true;
		}

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
