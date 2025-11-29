#pragma once
#include <deque>
#include <utility>

template<typename T, std::size_t MaxSize = 50>
class FixedStack {
public:
    void push(const T& value) {
        if (data.size() == MaxSize)
            data.pop_front();
        data.push_back(value);   // copy
    }

    void push(T&& value) {
        if (data.size() == MaxSize)
            data.pop_front();
        data.push_back(std::move(value));   // move
    }

    void pop() {
        data.pop_back();
    }

    T& top() {
        return data.back();
    }

    const T& top() const {
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    std::size_t size() const {
        return data.size();
    }

private:
    std::deque<T> data;
};