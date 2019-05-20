/*
 * Copyright (c) 2013 Pavlo Lavrenenko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <Vec3.h>
#include <Vec4.h>
#include <cmath>
#include <cassert>

namespace Math {

const Vec4 Vec4::ZERO(0.0f, 0.0f, 0.0f, 0.0f);

Vec4::Vec4() {
    this->vector[X] = 0.0f;
    this->vector[Y] = 0.0f;
    this->vector[Z] = 0.0f;
    this->vector[W] = 1.0f;
}

Vec4::Vec4(float x, float y, float z, float w) {
    this->vector[X] = x;
    this->vector[Y] = y;
    this->vector[Z] = z;
    this->vector[W] = w;
}

Vec4::Vec4(const Vec3& vector, float w) {
    this->vector[X] = vector.get(Vec3::X);
    this->vector[Y] = vector.get(Vec3::Y);
    this->vector[Z] = vector.get(Vec3::Z);
    this->vector[W] = w;
}

Vec4 Vec4::operator -(const Vec4& vector) const {
    Vec4 me(*this);
    return me -= vector;
}

Vec4 Vec4::operator +(const Vec4& vector) const {
    Vec4 me(*this);
    return me += vector;
}

Vec4 Vec4::operator *(float scalar) const {
    Vec4 me(*this);
    return me *= scalar;
}

Vec4& Vec4::operator -=(const Vec4& vector) {
    this->vector[X] -= vector.get(X);
    this->vector[Y] -= vector.get(Y);
    this->vector[Z] -= vector.get(Z);
    this->vector[W] -= vector.get(W);
    return *this;
}

Vec4& Vec4::operator +=(const Vec4& vector) {
    this->vector[X] += vector.get(X);
    this->vector[Y] += vector.get(Y);
    this->vector[Z] += vector.get(Z);
    this->vector[W] += vector.get(W);
    return *this;
}

Vec4& Vec4::operator *=(float scalar) {
    this->vector[X] *= scalar;
    this->vector[Y] *= scalar;
    this->vector[Z] *= scalar;
    this->vector[W] *= scalar;
    return *this;
}

bool Vec4::operator ==(const Vec4& vector) const {
    return (this->vector[X] == vector.get(X)) &&
           (this->vector[Y] == vector.get(Y)) &&
           (this->vector[Z] == vector.get(Z)) &&
           (this->vector[W] == vector.get(W));
}

bool Vec4::operator !=(const Vec4& vector) const {
    return !(*this == vector);
}

Vec4 Vec4::operator -() const {
    return Vec4(-this->vector[X],
                -this->vector[Y],
                -this->vector[Z],
                -this->vector[W]);
}

float Vec4::dot(const Vec4& vector) const {
    return this->vector[X] * vector.get(X) +
           this->vector[Y] * vector.get(Y) +
           this->vector[Z] * vector.get(Z) +
           this->vector[W] * vector.get(W);
}

float Vec4::get(int index) const {
    assert(index >= X && index <= W);
    return this->vector[index];
}

void Vec4::set(int index, float value) {
    assert(index >= X && index <= W);
    this->vector[index] = value;
}

const float* Vec4::data() const {
    return (float*)&this->vector;
}

Vec3 Vec4::extractVec3() const {
    return Vec3(this->vector[X], this->vector[Y], this->vector[Z]);
}

}  // namespace Math
