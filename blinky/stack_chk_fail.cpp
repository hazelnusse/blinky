#include <cstdint>

extern "C" {

extern const uintptr_t __stack_chk_guard = 0xdeadbeef;

[[noreturn]]
void __stack_chk_fail()
{
    while (1) {}
}

}
