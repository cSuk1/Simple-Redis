cmake_minimum_required(VERSION 3.27)
project(simple_kv_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(KVEngine main.cpp
        trie/include/trie.h
        trie/include/trie_store.h
        trie/trie.cpp
        trie/trie_store.cpp
        entry/client.cpp
        entry/include/client.h
        policy/evict_ploicy.cpp
        policy/include/evict_ploicy.h
        persistence/aof.cpp
        persistence/include/aof.h
        type/hash_type.cpp
        type/include/hash_type.h
        type/wrapper.cpp
        type/include/wrapper.h
)
