/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_SW64_MODULE_H
#define _ASM_SW64_MODULE_H

struct mod_arch_specific {
	unsigned int gotsecindex;
};

#define Elf_Sym		Elf64_Sym
#define Elf_Shdr	Elf64_Shdr
#define Elf_Ehdr	Elf64_Ehdr
#define Elf_Phdr	Elf64_Phdr
#define Elf_Dyn		Elf64_Dyn
#define Elf_Rel		Elf64_Rel
#define Elf_Rela	Elf64_Rela

#define ARCH_SHF_SMALL	SHF_SW64_GPREL

#ifdef MODULE
asm(".section .got, \"aw\", @progbits; .align 3; .previous");
#endif

#endif /* _ASM_SW64_MODULE_H */
