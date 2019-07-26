#ifndef MITAMA_MANA_CORE_TYPE_INJECT_HPP
#define MITAMA_MANA_CORE_TYPE_INJECT_HPP

namespace mitama::mana::core {
    template <class T>
    struct type_inject {
        using type = T;
    };
}

#endif
