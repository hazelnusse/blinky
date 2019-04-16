#include <cstdint>
#include <algorithm>

static const int a = 7;
static int b = 8;
static int sum;

extern "C" {

int main(void)
{
    sum = a + b;
    return sum;
}

extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern const uint32_t __data_flash_start__;
extern const uint32_t __data_flash_end__;
extern uint32_t __data_start__;
extern uint32_t __StackTop;

void Reset_Handler(void)
{
    //for (uint32_t *p = &__bss_start__; p != &__bss_end__; ++p)
    //{
    //    *p = 0;
    //}
    // TODO determine why this increases text section by 108 bytes compared to
    // above
    std::fill(&__bss_start__, &__bss_end__, 0);

    uint32_t *dst = &__data_start__;
    for (uint32_t const *p = &__data_flash_start__;
         p != &__data_flash_end__;
         ++p, ++dst)
    {
        *dst = *p;
    }

    // TODO determine why this increases text section and also figure out how
    // to supply memmove
    // std::copy(&__data_flash_start__, &__data_flash_end__, &__data_start__);

    int result = main();
    (void) result;

    while (1)
    {
       __asm("NOP");
    }
}

}

void *vector_table[] __attribute__((section(".vectors"))) =
{
    static_cast<void *>(&__StackTop),
    reinterpret_cast<void *>(Reset_Handler),
};
