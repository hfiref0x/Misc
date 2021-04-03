#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#include "pmdll.h"

int main()
{
	BOOL b=LoadPhyMemDriver();

	if (b==FALSE)
	{
		printf("load phymem.sys failed\n");
		exit(-1);
	}

	char *va=(char*)MapPhyMem(0xF7020, 20);
	printf("mapped virtual address = 0x%08x\n", va);
	UnmapPhyMem(va, 20);

/*
	DWORD d=ReadPortByte(0x379);
	WritePortLong(0x378, 10);
	d=ReadPortLong(0x378);
*/

	//enumerate PCI bus
	for (int bus=0; bus<=255; bus++)
	{
		for (int dev=0; dev<=31; dev++)
		{
			for (int func=0; func<=7; func++)
			{
				DWORD dev_ven;
				if (ReadPCI(bus, dev, func, 0, 4, &dev_ven))
				{
					if (LOWORD(dev_ven)!=0xFFFF)
						printf("Bus %d, Device %d, Function %d, Vendor ID 0x%x, Device ID 0x%x\n",
							bus, dev, func, LOWORD(dev_ven), HIWORD(dev_ven));
				}
			}
		}
	}

	printf("end");
	getchar();

	UnloadPhyMemDriver();
	return 0;
}
