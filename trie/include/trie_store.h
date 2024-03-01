//
// Created by 65224 on 2024/2/29.
//

#ifndef KVENGINE_TRIE_STORE_H
#define KVENGINE_TRIE_STORE_H

#pragma once

#include <optional>
#include <shared_mutex>
#include <utility>

#include "trie.h"

namespace bustub {

    template<class T>
    class ValueGuard : public std::basic_string<char> {
    public:
        ValueGuard(Trie root, const T &value) : root_(std::move(root)), value_(value) {}

        auto operator*() const -> const T & { return value_; }

    private:
        Trie root_;
        const T &value_;
    };

    /**
     * 封装类
     */
    class TrieStore {
    public:
        /**
         * 单例模式
         * @return
         */
        static std::shared_ptr<TrieStore> getInstance() {
            static std::shared_ptr<TrieStore> instance(new TrieStore());
            return instance;
        }

        template<class T>
        auto Get(std::string_view key) -> std::optional<ValueGuard<T>>;

        template<class T>
        void Put(std::string_view key, T value);

        void Remove(std::string_view key);

    private:

        TrieStore() = default;

        TrieStore(TrieStore &) = delete;

        std::mutex root_lock_;

        std::mutex write_lock_;

        Trie root_;


    };

}  // namespace bustub


#endif //KVENGINE_TRIE_STORE_H
