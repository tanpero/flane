#ifndef _COMPILER_EXPECTED_HH_
#define _COMPILER_EXPECTED_HH_

#include <iostream>
#include <new>
#include <utility>
#include <type_traits>

template <typename T, typename E>
class expected {
public:
    expected() noexcept : valid_(true), value_() {}
    expected(const T& value) : valid_(true), value_(value) {}
    expected(T&& value) : valid_(true), value_(std::move(value)) {}
    expected(const E& error) : valid_(false), error_(error) {}
    expected(E&& error) : valid_(false), error_(std::move(error)) {}

    expected(const expected& other)
        : valid_(other.valid_), value_(), error_() {
        if (valid_) {
            new (&value_) T(other.value_);
        }
        else {
            new (&error_) E(other.error_);
        }
    }

    expected(expected&& other) noexcept
        : valid_(other.valid_), value_(), error_() {
        if (valid_) {
            new (&value_) T(std::move(other.value_));
        }
        else {
            new (&error_) E(std::move(other.error_));
        }
    }

    ~expected() {
        if (valid_) {
            value_.~T();
        }
        else {
            error_.~E();
        }
    }

    expected& operator=(const expected& other) {
        if (this != &other) {
            if (valid_ && other.valid_) {
                value_ = other.value_;
            }
            else if (!valid_ && other.valid_) {
                value_.~T();
                new (&error_) E(other.error_);
                valid_ = false;
            }
            else if (valid_ && !other.valid_) {
                error_.~E();
                new (&value_) T(other.value_);
                valid_ = true;
            }
            else {
                error_ = other.error_;
            }
        }
        return *this;
    }

    expected& operator=(expected&& other) noexcept {
        if (this != &other) {
            if (valid_ && other.valid_) {
                value_ = std::move(other.value_);
            }
            else if (!valid_ && other.valid_) {
                value_.~T();
                new (&error_) E(std::move(other.error_));
                valid_ = false;
            }
            else if (valid_ && !other.valid_) {
                error_.~E();
                new (&value_) T(std::move(other.value_));
                valid_ = true;
            }
            else {
                error_ = std::move(other.error_);
            }
        }
        return *this;
    }

    // 成员访问函数
    const T& value() const& { return value_; }
    T& value()& { return value_; }
    const T&& value() const&& { return std::move(value_); }
    T&& value()&& { return std::move(value_); }

    const E& error() const& { return error_; }
    E& error()& { return error_; }
    const E&& error() const&& { return std::move(error_); }
    E&& error()&& { return std::move(error_); }

    // 成员函数
    bool has_value() const noexcept { return valid_; }
    explicit operator bool() const noexcept { return valid_; }

private:
    bool valid_;
    union {
        T value_;
        E error_;
    };
};


#endif // !_COMPILER_EXPECTED_HH_
