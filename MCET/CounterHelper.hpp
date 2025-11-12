#pragma once
#include <stdint.h>

template <typename T>
class CounterHelper {
public:
    explicit CounterHelper(T maxVal) : m_maxVal(maxVal), m_value(0) {}

    // Increments and wraps around automatically
    T increment() noexcept {
        m_value = (m_value + 1) % (m_maxVal + 1);
        return m_value;
    }

    // Decrements and wraps around automatically
    T decrement() noexcept {
        if (m_value == 0)
            m_value = m_maxVal;
        else
            --m_value;
        return m_value;
    }

    void reset(T val = 0) noexcept { m_value = val % (m_maxVal + 1); }

    T value() const noexcept { return m_value; }

private:
    T m_maxVal;
    T m_value;
};
