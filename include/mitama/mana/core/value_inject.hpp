#ifndef MITAMA_MANA_CORE_VALUE_INJECT_HPP
#define MITAMA_MANA_CORE_VALUE_INJECT_HPP

namespace mitama::mana::core {
    template <auto V>
    struct value_inject {
        static constexpr auto value = V;
    };
}

#endif
