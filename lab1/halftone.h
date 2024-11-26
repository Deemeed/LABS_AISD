#include <iostream>
#include <iomanip>
#include <random>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <type_traits>


template<typename T>
class Halftone {
private:
    T* _data;
    size_t _height, _width;

public:
    Halftone(size_t height, size_t width, bool random = false);
    Halftone(const Halftone& other);
    ~Halftone();

    double fillfactor() const;

    Halftone& operator=(const Halftone& other);
    bool operator==(const Halftone& other) const;
    bool operator!=(const Halftone& other) const { return !(*this == other); }

    Halftone operator!() const;

    Halftone& operator+=(const Halftone& other) const;
    Halftone& operator*=(const Halftone& other) const;

    Halftone& operator+=(T constant);
    Halftone& operator*=(T constant);

    T& operator()(size_t x, size_t y) { return _data[y * _width + x]; }
    const T& operator()(size_t x, size_t y) const { return _data[y * _width + x]; }

    size_t size() const { return _height * _width; }
    size_t height() const { return _height; }
    size_t width() const { return _width; }

    friend std::ostream& operator<<(std::ostream& os, const Halftone& obj) {
        for (size_t y = 0; y < obj._height; ++y) {
            for (size_t x = 0; x < obj._width; ++x) {
                os << std::setw(10) << obj(x, y) << " ";
            }
            os << "\n";
        }
        return os;
    }
};


template<typename T>
Halftone<T>::Halftone(size_t height, size_t width, bool random)
    : _height(height), _width(width), _data(new T[height * width]) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if (random) {
        if constexpr (std::is_same_v<T, float>)
            for (size_t i = 0; i < size(); ++i) _data[i] = std::uniform_real_distribution<>(0.0, 127.0)(gen);
        else if constexpr (std::is_same_v<T, short> || std::is_same_v<T, char>)
            for (size_t i = 0; i < size(); ++i) _data[i] = std::uniform_int_distribution<>(0, 127)(gen);
        else if constexpr (std::is_same_v<T, bool>)
            for (size_t i = 0; i < size(); ++i) _data[i] = std::uniform_int_distribution<>(0, 1)(gen);
    }
    else {
        for (size_t i = 0; i < size(); ++i) _data[i] = T{};
    }
}


template<typename T>
Halftone<T>::Halftone(const Halftone<T>& other)
    : _height(other._height), _width(other._width), _data(new T[other.size()]) {
    std::copy(other._data, other._data + other.size(), _data);
}


template<typename T>
Halftone<T>::~Halftone() {
    delete[] _data;
}


template<typename T>
Halftone<T>& Halftone<T>::operator=(const Halftone<T>& other) {
    if (this != &other) {
        delete[] _data;
        _height = other._height;
        _width = other._width;
        _data = new T[other.size()];
        std::copy(other._data, other._data + other.size(), _data);
    }
    return *this;
}


template<typename T>
bool Halftone<T>::operator==(const Halftone<T>& other) const {
    if (_height != other._height || _width != other._width) return false;
    if constexpr (std::is_same_v<T, float>) {
        for (size_t i = 0; i < size(); ++i)
            if (std::fabs(_data[i] - other._data[i]) > 0.0001f) return false;
    }
    else {
        for (size_t i = 0; i < size(); ++i)
            if (_data[i] != other._data[i]) return false;
    }
    return true;
}


template<typename T>
double Halftone<T>::fillfactor() const {
    double sum = 0;
    for (size_t i = 0; i < size(); ++i) sum += _data[i];
    return sum / (size() * static_cast<double>(std::numeric_limits<T>::max()));
}


template<typename T>
Halftone<T> Halftone<T>::operator!() const {
    Halftone<T> result(*this);
    if constexpr (std::is_same_v<T, bool>) {
        for (size_t i = 0; i < size(); ++i) result._data[i] = !_data[i];
    }
    else {
        for (size_t i = 0; i < size(); ++i) result._data[i] *= -1;
    }
    return result;
}

// Matrix
template<typename T>
Halftone<T> Halftone<T>::operator+(const Halftone<T>& other) const {
    size_t height = std::max(_height, other._height);
    size_t width = std::max(_width, other._width);
    Halftone<T> result(height, width);

    for (size_t y = 0; y < height; ++y)
        for (size_t x = 0; x < width; ++x) {
            T v1 = (x < _width && y < _height) ? (*this)(x, y) : T{};
            T v2 = (x < other._width && y < other._height) ? other(x, y) : T{};
            result(x, y) = std::min<T>(v1 + v2, std::numeric_limits<T>::max());
        }

    return result;
}


template<typename T>
Halftone<T> Halftone<T>::operator*(const Halftone<T>& other) const {
    if (_height != other._height || _width != other._width) throw std::invalid_argument("Sizes don't match!");
    Halftone<T> result(*this);
    for (size_t i = 0; i < size(); ++i) {
        result._data[i] = _data[i] * other._data[i];
    }
    return result;
}
//Matrix

template<typename T>
Halftone<T> operator+(const Halftone<T>& image, T constant) {
    Halftone<T> result(image);
    for (size_t i = 0; i < image.size(); ++i) {
        result._data[i] = std::min<T>(image._data[i] + constant, std::numeric_limits<T>::max());
    }
    return result;
}

template<typename T>
Halftone<T> operator+(T constant, const Halftone<T>& image) {
    return image + constant;
}

template<typename T>
Halftone<T> operator*(const Halftone<T>& image, T constant) {
    Halftone<T> result(image);
    for (size_t i = 0; i < image.size(); ++i) {
        result._data[i] = std::min<T>(image._data[i] * constant, std::numeric_limits<T>::max());
    }
    return result;
}

template<typename T>
Halftone<T> operator*(T constant, const Halftone<T>& image) {
    return image * constant;
}

template<typename T>
Halftone<T>& Halftone<T>::operator+=(T constant) {
    for (size_t i = 0; i < size(); ++i) {
        _data[i] = std::min<T>(_data[i] + constant, std::numeric_limits<T>::max());
    }
    return *this;
}

template<typename T>
Halftone<T>& Halftone<T>::operator*=(T constant) {
    for (size_t i = 0; i < size(); ++i) {
        _data[i] = std::min<T>(_data[i] * constant, std::numeric_limits<T>::max());
    }
    return *this;
}



template<typename T>
Halftone<T>& paint_square(Halftone<T>& img, size_t x1, size_t y1, size_t x2, size_t y2, T fill) {
    if (x1 >= img.width() || x2 >= img.width() || y1 >= img.height() || y2 >= img.height())
        throw std::invalid_argument("Sizes don't match!");

    for (size_t y = std::min(y1, y2); y <= std::max(y1, y2); ++y)
        for (size_t x = std::min(x1, x2); x <= std::max(x1, x2); ++x)
            img(x, y) = fill;

    return img;
}
