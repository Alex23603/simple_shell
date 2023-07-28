#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 *
 * ugufuhf uerfguygufergf efer
 * fuerufuryfuygfuygyfueygrfuguy ufefegruygeurfg
 * fgyfufgurgfuyrgfuegfuyerfyrfefi
 * efrburyryf frufygryufgrf rufyeurfygreufygruf fr
 *
 * hferfehrferjfhfhjfuefe
 * eferbfbfhrfb
 * rfjrefhuie
 * rrufueyrfyefuyerfuyerfyergfuye
 *
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
