#ifndef __GDT_H
#define __GDT_H

#include <types.h>

struct SegmentDescriptor
{
	uint16_t limit_lo;
	uint16_t base_lo;
	uint8_t base_hi;
	uint8_t type;
	uint8_t limit_hi;
	uint8_t base_vhi;
}

void InitSegmentDescriptor(struct SegmentDescriptor* sd, uint32_t base, uint32_t limit, uint8_t type);
void Base(struct SegmentDescriptor* sd);
void Limit(struct SegmentDescriptor* sd)

struct GlobalDescriptorTable
{
	struct SegmentDescriptor nullSegmentSelector;
	struct SegmentDescriptor unusedSegmentSelector;
	struct SegmentDescriptor codeSegmentSelector;
	struct SegmentDescriptor dataSegmentSelector;
}

void InitGlobalDescriptorTable(struct GlobalDescriptorTable* gdt);
void FreeGlobalDescriptorTable(struct GlobalDescriptorTable* gdt);
uint16_t CodeSegmentSelector();
uint16_t DataSegmentSelector();

#endif
