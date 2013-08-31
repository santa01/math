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

#ifndef VEC4_H
#define VEC4_H

#include <Vec3.h>
#include <cmath>

namespace Math {

/*!
 * \brief Four component vector class.
 * \details Vec4 implements basic operations that are:
 *          * vector-vector addition, difference (both one and two operand);
 *          * vector-scalar multiplication (both one and two operand);
 *          * dot product calculation.
 */
class Vec4 {
public:
    enum {
        X = 0,  /*!< X component index. */
        Y = 1,  /*!< Y component index. */
        Z = 2,  /*!< Z component index. */
        W = 3   /*!< W component index. */
    };

    static const Vec4 ZERO;  /*!< Zero length vector. */

    /*!
     * \brief Default constructor.
     * \details Constructs four component vector initializing components with zeros.
     *          W component is initialized with 1.0f.
     */
    Vec4() {
        this->vector[X] = 0.0f;
        this->vector[Y] = 0.0f;
        this->vector[Z] = 0.0f;
        this->vector[W] = 1.0f;
    }

    /*!
     * \brief Per-component constructor.
     * \details Constructs four component vector initializing components with arbitrary values.
     * \param x X component.
     * \param y Y component.
     * \param z Z component.
     * \param w W component.
     */
    Vec4(float x, float y, float z, float w) {
        this->vector[X] = x;
        this->vector[Y] = y;
        this->vector[Z] = z;
        this->vector[W] = w;
    }

    /*!
     * \brief Vec3-based constructor.
     * \details Constructs four component vector initializing X, Y, Z components
     *          from Vec3 vector and W component with arbitrary value.
     * \param vector Source three component vector.
     * \param w W component.
     */
    Vec4(const Vec3& vector, float w) {
        this->vector[X] = vector.get(Vec3::X);
        this->vector[Y] = vector.get(Vec3::Y);
        this->vector[Z] = vector.get(Vec3::Z);
        this->vector[W] = w;
    }

    /*!
     * \brief Vector-vector difference.
     * \details Performs per-component vector-vector deduction.
     * \param vector Deducted vector.
     * \return Difference vector.
     */
    Vec4 operator -(const Vec4& vector) const {
        Vec4 me(*this);
        return me -= vector;
    }

    /*!
     * \brief Vector-vector addition.
     * \details Performs per-component vector-vector addition.
     * \param vector Summand vector.
     * \return Sum vector.
     */
    Vec4 operator +(const Vec4& vector) const {
        Vec4 me(*this);
        return me += vector;
    }

    /*!
     * \brief Vector-scalar multiplication.
     * \details Performs per-component vector-scalar multiplication.
     * \param scalar Scalar multiplier.
     * \return Product vector.
     */
    Vec4 operator *(float scalar) const {
        Vec4 me(*this);
        return me *= scalar;
    }

    /*!
     * \brief Vector substruction.
     * \details Performs per-component vector substruction.
     * \note Method has a side-effect.
     * \param vector Substructed vector.
     * \return Difference vector.
     */
    Vec4& operator -=(const Vec4& vector) {
        this->vector[X] -= vector.get(X);
        this->vector[Y] -= vector.get(Y);
        this->vector[Z] -= vector.get(Z);
        this->vector[W] -= vector.get(W);
        return *this;
    }

    /*!
     * \brief Vector addition.
     * \details Performs per-component vector addition.
     * \note Method has a side-effect.
     * \param vector Summand vector.
     * \return Sum vector.
     */
    Vec4& operator +=(const Vec4& vector) {
        this->vector[X] += vector.get(X);
        this->vector[Y] += vector.get(Y);
        this->vector[Z] += vector.get(Z);
        this->vector[W] += vector.get(W);
        return *this;
    }

    /*!
     * \brief Scalar multiplication.
     * \details Performs per-component scalar multiplication.
     * \note Method has a side-effect.
     * \param scalar Scalar multiplier.
     * \return Product vector.
     */
    Vec4& operator *=(float scalar) {
        this->vector[X] *= scalar;
        this->vector[Y] *= scalar;
        this->vector[Z] *= scalar;
        this->vector[W] *= scalar;
        return *this;
    }

    /*!
     * \brief Vectors comparsion.
     * \details Performs per-component vector-vector comparsion.
     * \param vector Compared vector.
     * \return true if vectors are equal, false otherwise.
     */
    bool operator ==(const Vec4& vector) const {
        return (this->vector[X] == vector.get(X)) &&
               (this->vector[Y] == vector.get(Y)) &&
               (this->vector[Z] == vector.get(Z)) &&
               (this->vector[W] == vector.get(W));
    }

    /*!
     * \brief Vectors inequality check.
     * \details Performs per-component vector-vector comparsion.
     * \param vector Compared vector.
     * \return false if vectors are equal, true otherwise.
     */
    bool operator !=(const Vec4& vector) const {
        return !(*this == vector);
    }

    /*!
     * \brief Vector inversion.
     * \details Performs vector's components sign inversion.
     * \note Method has a side-effect.
     * \return Inverted vector.
     */
    Vec4 operator -() const {
        return Vec4(-this->vector[X],
                    -this->vector[Y],
                    -this->vector[Z],
                    -this->vector[W]);
    }

    /*!
     * \brief Dot product calculation.
     * \details Performs vectors' components multiplication and adds the results.
     * \param vector Vector mutliplier.
     * \return Scalar (dot) product.
     */
    float dot(const Vec4& vector) const {
        return this->vector[X] * vector.get(X) +
               this->vector[Y] * vector.get(Y) +
               this->vector[Z] * vector.get(Z) +
               this->vector[W] * vector.get(W);
    }

    /*!
     * \brief Vector's components selector.
     * \details Gets vector components' values by their indexes. See X, Y, Z, W.
     * \param index Component's index.
     * \return Component value.
     */
    float get(int index) const {
        switch (index) {
            case X:
            case Y:
            case Z:
            case W:
                return this->vector[index];

            default:
                return NAN;
        }
    }

    /*!
     * \brief Vector's components mutator.
     * \details Sets vector components' values. See X, Y, Z, W.
     * \param index Component's index.
     * \param value Component's new value.
     */
    void set(int index, float value) {
        switch (index) {
            case X:
            case Y:
            case Z:
            case W:
                this->vector[index] = value;
                break;
        }
    }

    /*!
     * \brief Vector's data accessor.
     * \details Gets a constant pointer to vector's data array.
     * \return Vector's data pointer.
     */
    const float* data() const  {
        return (float*)&this->vector;
    }

    /*!
     * \brief Three dimentional vector extractor.
     * \details Composes Vec3 from X, Y, Z Vec4 components.
     * \return Three dimentional vector.
     */
    Vec3 extractVec3() const {
        return Vec3(this->vector[X],
                    this->vector[Y],
                    this->vector[Z]);
    }

private:
    float vector[4];
};

}  // namespace Math

#endif  // VEC4_H
