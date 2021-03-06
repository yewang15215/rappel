#include <sys/ptrace.h>
#include <linux/elf.h>

#include "common.h"
#include "arch.h"

void ptrace_reset_x86(
		const pid_t child_pid,
		const unsigned long start)
{
	struct user_regs_struct_x86 regs_struct = {};
	struct iovec regs = {.iov_base = &regs_struct, .iov_len = sizeof(regs_struct) };

	REQUIRE (ptrace(PTRACE_GETREGSET, child_pid, NT_PRSTATUS, &regs) == 0);

	regs_struct.eip = start;

	REQUIRE (ptrace(PTRACE_SETREGSET, child_pid, NT_PRSTATUS, &regs) == 0);
}
