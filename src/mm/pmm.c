#include <limine.h>
#include <mm/pmm.h>
#include <dev/char/serial.h>

struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

struct limine_memmap_response* pmm_memmap;

u64 pmmTotalPages = 0;

void pmmInit()
{
    pmm_memmap = memmap_request.response;
    struct limine_memmap_entry** entries = pmm_memmap->entries;

    u64 higher_address;
    u64 top_address;

    dprintf("pmmInit(): entry count: %d\n", pmm_memmap->entry_count);

    for(u64 i = 0; i < pmm_memmap->entry_count; i++)
    {
        if(entries[i]->type != LIMINE_MEMMAP_USABLE)
            continue;   // skip unusable memmaps

        top_address = entries[i]->base + entries[i]->length;
        if(top_address > higher_address)
            higher_address = top_address;
    }

    pmmTotalPages = higher_address / PAGE_SIZE;

    dprintf("pmmInit(): total pages: %d\n", pmmTotalPages);
}
