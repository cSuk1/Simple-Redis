//
// Created by 65224 on 2024/3/1.
//

#ifndef KVENGINE_WRAPPER_H
#define KVENGINE_WRAPPER_H

#include "../../trie/include/trie.h"

namespace bustub {
    template<typename V>
    class wrapper {
    private:
        std::shared_ptr<V> value;
    public:
        wrapper(std::shared_ptr<V> value) : value(value) {}

        wrapper() = default;

        std::shared_ptr<V> get() {
            return value;
        }

        void set(std::shared_ptr<V> value) {
            this->value = value;
        }

    };
}


#endif //KVENGINE_WRAPPER_H
