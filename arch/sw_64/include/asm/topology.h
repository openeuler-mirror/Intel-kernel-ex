/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_SW64_TOPOLOGY_H
#define _ASM_SW64_TOPOLOGY_H

#include <linux/smp.h>
#include <linux/threads.h>
#include <linux/cpumask.h>
#include <asm/core.h>
#include <asm/smp.h>

#define THREAD_ID_SHIFT	5
#define THREAD_ID_MASK	1
#define CORE_ID_MASK ((1 << THREAD_ID_SHIFT) - 1)

extern struct cpu_topology cpu_topology[NR_CPUS];

#define topology_physical_package_id(cpu)	(cpu_topology[cpu].package_id)
#define topology_core_id(cpu)			(cpu_topology[cpu].core_id)
#define topology_core_cpumask(cpu)		(&cpu_topology[cpu].core_sibling)
#define topology_sibling_cpumask(cpu)		(&cpu_topology[cpu].thread_sibling)
#define topology_llc_cpumask(cpu)		(&cpu_topology[cpu].llc_sibling)

void init_cpu_topology(void);
void store_cpu_topology(int cpuid);
void remove_cpu_topology(int cpuid);
const struct cpumask *cpu_coregroup_mask(int cpu);

static inline int rcid_to_package(int rcid)
{
	return rcid >> CORES_PER_NODE_SHIFT;
}

#ifdef CONFIG_NUMA

#ifndef CONFIG_USE_PERCPU_NUMA_NODE_ID
extern int cpuid_to_nid(int cpuid);
static inline int cpu_to_node(int cpu)
{
	int node;

	node = cpuid_to_nid(cpu);

#ifdef DEBUG_NUMA
	BUG_ON(node < 0);
#endif

	return node;
}

static inline void set_cpu_numa_node(int cpu, int node) { }
#endif /* CONFIG_USE_PERCPU_NUMA_NODE_ID */

extern const struct cpumask *cpumask_of_node(int node);
extern void numa_add_cpu(unsigned int cpu);
extern void numa_remove_cpu(unsigned int cpu);
extern void numa_store_cpu_info(unsigned int cpu);
#define parent_node(node) (node)
#define cpumask_of_pcibus(bus)	(cpu_online_mask)
#else /* !CONFIG_NUMA */
static inline void numa_add_cpu(unsigned int cpu) { }
static inline void numa_remove_cpu(unsigned int cpu) { }
static inline void numa_store_cpu_info(unsigned int cpu) { }
#endif /* CONFIG_NUMA */
#include <asm-generic/topology.h>

static inline void arch_fix_phys_package_id(int num, u32 slot) { }

#endif /* _ASM_SW64_TOPOLOGY_H */
