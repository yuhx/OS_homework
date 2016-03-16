#include <cstdio>
using namespace std;

unsigned int mem[128][32];
unsigned int disk[128][32];
unsigned int PDBR;

void initialize()
{
	int tem;
	FILE *f;
    f = fopen("mem.txt","r");
    for (int i = 0; i < 128; i ++)
    {
        fscanf(f,"page %x: ", &tem);
        for (int j = 0; j < 32; j ++)
        {
        	fscanf(f,"%x : ", &tem);
        	mem[i][j] = tem;
        }
    }
    fclose(f);

    f = fopen("disk.txt","r");
    for (int i = 0; i < 128; i ++)
    {
        fscanf(f,"disk %x: ", &tem);
        for (int j = 0; j < 32; j ++)
        {
        	fscanf(f,"%x : ", &tem);
        	disk[i][j] = tem;
        }
    }
    fclose(f);

    PDBR = 0xd80 >> 5;
}

void translate(unsigned int va)
{
	printf("Virtual Address %04x:\n", va);
	unsigned int pde_index = (va >> 10) & 0x1f;
	unsigned int pte_index = (va >> 5) & 0x1f;
	unsigned int phy_offset = va & 0x1f;
	printf("  --> pde index:0x%x  ", pde_index);
	unsigned int pde_contents = mem[PDBR][pde_index];
	printf("pde contents:0x%02x ", pde_contents);
	unsigned int pde_pfn = pde_contents & 0x7f;
	int pde_valid = (pde_contents >> 7) & 0x1;
	printf("(valid %d, pfn 0x%x)\n", pde_valid, pde_pfn);
	if (pde_valid == 0)
	{
		return;
	}
	printf("    --> pte index:0x%x  ", pte_index);
	unsigned int pte_contents = mem[pde_pfn][pte_index];
	printf("pte contents:0x%02x ", pte_contents);
	unsigned int pte_pfn = pte_contents & 0x7f;
	int pte_valid = (pte_contents >> 7) & 0x1;
	printf("(valid %d, pfn 0x%x)\n", pte_valid, pte_pfn);
	unsigned int address = (pte_pfn << 5) + phy_offset;
	if (pte_valid == 1)
	{
		printf("      --> To Physical Address 0x%x", address);
		printf(" --> Value: %02x", mem[pte_pfn][phy_offset]);
	}
	else
	{
		printf("      --> To Disk Sector Address 0x%x", address);
		printf(" --> Value: %02x", disk[pte_pfn][phy_offset]);
	}
}

int main()
{
	initialize();
	printf("please input Virtual Address:\n");
	unsigned int va;
	scanf("%04x: ", &va);
	translate(va);
	
	return 0;
}