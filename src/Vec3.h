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

#ifndef VEC3_H
#define VEC3_H

#include <cmath>

namespace Math {

/*!
 * \brief Three component vector class.
 * \details Vec3 implements basic operations that are:
 *          * vector-vector addition, difference (both one and two operand);
 *          * vector-scalar multiplication (both one and two operand);
 *          * dot and cross product, normalization;
 *          * length, square length calculation.
 */
class Vec3 {
public:
    enum {
        X = 0,  /*!< X component index. */
        Y = 1,  /*!< Y component index. */
        Z = 2   /*!< Z component index. */
    };

    static const Vec3 UNIT_X;  /*!< X unit vector. */
    static const Vec3 UNIT_Y;  /*!< Y unit vector. */
    static const Vec3 UNIT_Z;  /*!< Z unit vector. */
    static const Vec3 ZERO;    /*!< Zero length vector. */

    /*!
     * \brief Default constructor.
     * \details Constructs three component vector initializing components with zeros.
     */
    Vec3() {
        for (int i = 0; i < 3; i++) {
            this->vector[i] = 0.0f;
        }
    }

    /*!
     * \brief Per-component constructor.
     * \details Constructs three component vector initializing components with arbitrary values.
     * \param x X component.
     * \param y Y component.
     * \param z Z component.
     */
    Vec3(float x, float y, float z) {
        this->vector[X] = x;
        this->vector[Y] = y;
        this->vector[Z] = z;
    }

    /*!
     * \brief Vector-vector difference.
     * \details Performs per-component vector-vector deduction.
     * \param vector Deducted vector.
     * \return Difference vector.
     */
    Vec3 operator -(const Vec3& vector) const {
        Vec3 me(*this);
        return me -= vector;
    }

    /*!
     * \brief Vector-vector addition.
     * \details Performs per-component vector-vector addition.
     * \param vector Summand vector.
     * \return Sum vector.
     */
    Vec3 operator +(const Vec3& vector) const {
        Vec3 me(*this);
        return me += vector;
    }

    /*!
     * \brief Vector-scalar multiplication.
     * \details Performs per-component vector-scalar multiplication.
     * \param scalar Scalar multiplier.
     * \return Product vector.
     */
    Vec3 operator *(float scalar) const {
        Vec3 me(*this);
        return me *= scalar;
    }

    /*!
     * \brief Vector substruction.
     * \details Performs per-component vector substruction.
     * \note Method has a side-effect.
     * \param vector Substructed vector.
     * \return Difference vector.
     */
    Vec3& operator -=(const Vec3& vector) {
        this->vector[X] -= vector.get(X);
        this->vector[Y] -= vector.get(Y);
        this->vector[Z] -= vector.get(Z);
        return *this;
    }

    /*!
     * \brief Vector addition.
     * \details Performs per-component vector addition.
     * \note Method has a side-effect.
     * \param vector Summand vector.
     * \return Sum vector.
     */
    Vec3& operator +=(const Vec3& vector) {
        this->vector[X] += vector.get(X);
        this->vector[Y] += vector.get(Y);
        this->vector[Z] += vector.get(Z);
        return *this;
    }

    /*!
     * \brief Scalar multiplication.
     * \details Performs per-component scalar multiplication.
     * \note Method has a side-effect.
     * \param scalar Scalar multiplier.
     * \return Product vector.
     */
    Vec3& operator *=(float scalar) {
        this->vector[X] *= scalar;
        this->vector[Y] *= scalar;
        this->vector[Z] *= scalar;
        return *this;
    }

    /*!
     * \brief Vectors comparsion.
     * \details Performs per-component vector-vector comparsion.
     * \param vector Compared vector.
     * \return true if vectors are equal, false otherwise.
     */
    bool operator ==(const Vec3& vector) const {
        return (this->vector[X] == vector.get(X)) &&
               (this->vector[Y] == vector.get(Y)) &&
               (this->vector[Z] == vector.get(Z));
    }

    /*!
     * \brief Vectors inequality check.
     * \details Performs per-component vector-vector comparsion.
     * \param vector Compared vector.
     * \return false if vectors are equal, true otherwise.
     */
    bool operator !=(const Vec3& vector) const {
        return !(*this == vector);
    }

    /*!
     * \brief Vector inversion.
     * \details Performs vector's components sign inversion.
     * \note Method has a side-effect.
     * \return Inverted vector.
     */
    Vec3 operator -() const {
        return Vec3(-this->vector[X],
                    -this->vector[Y],
                    -this->vector[Z]);
    }

    /*!
     * \brief Dot product calculation.
     * \details Multiplies vectors' components and adds the results.
     * \param vector Vector mutliplier.
     * \return Scalar (dot) product.
     */
    float dot(const Vec3& vector) const {
        return this->vector[X] * vector.get(X) +
               this->vector[Y] * vector.get(Y) +
               this->vector[Z] * vector.get(Z);
    }

    /*!
     * \brief Cross product calculation.
     * \details Performs two vectors' cross product operation.
     * \param vector Vector mutliplier.
     * \return Vector (cross) product.
     */
    Vec3 cross(const Vec3& vector) const {
        return Vec3(this->vector[Y] * vector.get(Z) - this->vector[Z] * vector.get(Y),
                    this->vector[Z] * vector.get(X) - this->vector[X] * vector.get(Z),
                    this->vector[X] * vector.get(Y) - this->vector[Y] * vector.get(X));
    }

    /*!
     * \brief Vector normalization.
     * \details Divides vector's components by the vector's length.
     * \note Method has a side-effect.
     * \return Normalized (unit) vector.
     */
    Vec3& normalize() {
        float length = this->length();
        this->vector[X] /= length;
        this->vector[Y] /= length;
        this->vector[Z] /= length;
        return *this;
    }

    /*!
     * \brief Vector's length calculation.
     * \details Derives a square root from vector's square length.
     * \return Vector length.
     */
    float length() const {
        return sqrtf(this->squareLength());
    }

    /*!
     * \brief Vector's square length calculation.
     * \details Multiplies vector's components by themselves and adds the results.
     * \return Vector square length.
     */
    float squareLength() const {
        return this->vector[X] * this->vector[X] +
               this->vector[Y] * this->vector[Y] +
               this->vector[Z] * this->vector[Z];
    }

    /*!
     * \brief Vector's components selector.
     * \details Gets vector components' values by their indexes. See X, Y, Z.
     * \param index Component's index.
     * \return Component value.
     */
    float get(int index) const {
        switch (index) {
            case X:
            case Y:
            case Z:
                return this->vector[index];

            default:
                return NAN;
        }
    }

    /*!
     * \brief Vector's components mutator.
     * \details Sets vector components' values. See X, Y, Z.
     * \param index Component's index.
     * \param value Component's new value.
     */
    void set(int index, float value) {
        switch (index) {
            case X:
            case Y:
            case Z:
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

private:
    float vector[3];
};

}  // namespace Math

#endif  // VEC3_H
