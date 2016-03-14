#include <cstdio>
using namespace std;

void translate(unsigned int va, unsigned int pa)
{
	unsigned int pde_idx = (va >> 22) & 0x3ff;
	unsigned int pde_ctx = ((pde_idx - 0x300 + 1) << 12) + 3;
	unsigned int pte_idx = (va >> 12) & 0x3ff;
	unsigned int pte_ctx = (pa & 0xfffff000) + 3;
	printf("va 0x%08x, pa 0x%08x, pde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x\n", va, pa, pde_idx, pde_ctx, pte_idx, pte_ctx);
 }

int main()
{
	unsigned int va, pa;
	scanf("va 0x%x, pa 0x%x", &va, &pa);
	translate(va, pa);
	return 0;
}