//
// Created by 65224 on 2024/2/29.
//

#ifndef KVENGINE_TRIE_H
#define KVENGINE_TRIE_H

#pragma once

#include <algorithm>
#include <cstddef>
#include <future>  // NOLINT
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace bustub {
    class MoveBlocked {
    public:
        explicit MoveBlocked(std::future<int> wait) : wait_(std::move(wait)) {}

        MoveBlocked(const MoveBlocked &) = delete;

        MoveBlocked(MoveBlocked &&that) noexcept {
            if (!that.waited_) {
                that.wait_.get();
            }
            that.waited_ = waited_ = true;
        }

        auto operator=(const MoveBlocked &) -> MoveBlocked & = delete;

        auto operator=(MoveBlocked &&that) noexcept -> MoveBlocked & {
            if (!that.waited_) {
                that.wait_.get();
            }
            that.waited_ = waited_ = true;
            return *this;
        }

        bool waited_{false};
        std::future<int> wait_;
    };

    /**
     * 前缀树节点
     */
    class TrieNode {
    public:

        TrieNode() = default;

        explicit TrieNode(std::map<char, std::shared_ptr<const TrieNode>> children) : children_(std::move(children)) {}

        virtual ~TrieNode() = default;

        /**
         * 升级为带val的节点
         * @tparam T
         * @param key
         * @param val
         */
        template<class T>
        void Put(std::string_view key, T val);

        virtual auto Clone() const -> std::unique_ptr<TrieNode> { return std::make_unique<TrieNode>(children_); }

        std::map<char, std::shared_ptr<const TrieNode>> children_;

        bool is_value_node_{false};

    };

    /**
     * 带值的前缀树节点
     * @tparam T
     */
    template<class T>
    class TrieNodeWithValue : public TrieNode {
    public:
        explicit TrieNodeWithValue(std::shared_ptr<T> value) : value_(std::move(value)) { this->is_value_node_ = true; }

        TrieNodeWithValue(std::map<char, std::shared_ptr<const TrieNode>> children, std::shared_ptr<T> value)
                : TrieNode(std::move(children)), value_(std::move(value)) {
            this->is_value_node_ = true;
        }

        auto Clone() const -> std::unique_ptr<TrieNode> override {
            return std::make_unique<TrieNodeWithValue<T>>(children_, value_);
        }

        std::shared_ptr<T> value_;
    };

    /**
     * 前缀树
     */
    class Trie {
    private:
        std::shared_ptr<const TrieNode> root_{nullptr};

        explicit Trie(std::shared_ptr<const TrieNode> root) : root_(std::move(root)) {}

    public:
        Trie() = default;

        /**
         * 获取节点
         * @tparam T
         * @param key
         * @return
         */
        template<class T>
        auto Get(std::string_view key) const -> const T *;

        /**
         *  设置节点
         * @tparam T
         * @param key
         * @param value
         * @return
         */
        template<class T>
        auto Put(std::string_view key, T value) const -> Trie;

        /**
         * 移除节点
         * @param key
         * @return
         */
        auto Remove(std::string_view key) const -> Trie;

        /**
         * 获取根节点
         * @return
         */
        auto GetRoot() const -> std::shared_ptr<const TrieNode> { return root_; }
    };

}  // namespace bustub



#endif //KVENGINE_TRIE_H
