//
// Created by 65224 on 2024/2/29.
//

#include "include/trie_store.h"
//#include "common/exception.h"

namespace bustub {

    template<class T>
    auto TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<T>> {

        // access lock
        std::unique_lock<std::mutex> lock(this->root_lock_);
        Trie root = this->root_;
        lock.unlock();
        // 获取键值
        const T *val = root.Get<T>(key);
        // 封装
        if (val != nullptr) {
            return ValueGuard<T>(root, *val);
        }
        return std::nullopt;
    }

    template<class T>
    void TrieStore::Put(std::string_view key, T value) {

        // 先获取写锁
        std::unique_lock<std::mutex> wlock(this->write_lock_);
        // 向root中插入kv，并得到新的trie
        const Trie trie = this->root_.Put<T>(key, std::move(value));
        // 再获取访问锁
        std::unique_lock<std::mutex> alock(this->root_lock_);
        // 更新root
        this->root_ = trie;
        // 释放锁
        alock.unlock();
        wlock.unlock();
    }

    void TrieStore::Remove(std::string_view key) {

        // 先获取写锁
        std::unique_lock<std::mutex> wlock(this->write_lock_);
        // 删除key，并得到新的trie
        const Trie trie = this->root_.Remove(key);
        // 再获取访问锁
        std::unique_lock<std::mutex> alock(this->root_lock_);
        // 更新root
        this->root_ = trie;
        // 释放锁
        alock.unlock();
        wlock.unlock();
    }

// Below are explicit instantiation of template functions.

    template auto TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<uint32_t>>;

    template void TrieStore::Put(std::string_view key, uint32_t value);

    template auto TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<std::string>>;

    template void TrieStore::Put(std::string_view key, std::string value);

    template auto
    TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<std::unordered_map<std::string, std::string>>>;

    template void TrieStore::Put(std::string_view key, std::unordered_map<std::string, std::string> value);
    
    using Integer = std::unique_ptr<uint32_t>;

    template auto TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<Integer>>;

    template void TrieStore::Put(std::string_view key, Integer value);

    template auto TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<MoveBlocked>>;

    template void TrieStore::Put(std::string_view key, MoveBlocked value);

}  // namespace bustub

