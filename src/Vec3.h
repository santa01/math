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

#include <MathApi.h>

namespace Math {

/*!
 * \brief Three component vector.
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

    MATH_API static const Vec3 UNIT_X;  /*!< X unit vector. */
    MATH_API static const Vec3 UNIT_Y;  /*!< Y unit vector. */
    MATH_API static const Vec3 UNIT_Z;  /*!< Z unit vector. */
    MATH_API static const Vec3 ZERO;    /*!< Zero length vector. */

    /*!
     * \brief Default constructor.
     * \details Constructs zero-length vector.
     */
    MATH_API Vec3();

    /*!
     * \brief Per-component constructor.
     * \details Constructs arbitrary vector based on x, y, z values.
     * \param x X component.
     * \param y Y component.
     * \param z Z component.
     */
    MATH_API Vec3(float x, float y, float z);

    /*!
     * \brief Vectors substraction.
     * \param vector Substructed vector.
     * \return Difference vector.
     */
    MATH_API Vec3 operator -(const Vec3& vector) const;

    /*!
     * \brief Vectors addition.
     * \param vector Summand vector.
     * \return Sum vector.
     */
    MATH_API Vec3 operator +(const Vec3& vector) const;

    /*!
     * \brief Vector by scalar multiplication.
     * \param scalar Scalar multiplier.
     * \return Product vector.
     */
    MATH_API Vec3 operator *(float scalar) const;

    /*!
     * \brief Vector substruction.
     * \param vector Substructed vector.
     * \return Difference vector.
     * \note Method has a side-effect.
     */
    MATH_API Vec3& operator -=(const Vec3& vector);

    /*!
     * \brief Vector addition.
     * \param vector Summand vector.
     * \return Sum vector.
     * \note Method has a side-effect.
     */
    MATH_API Vec3& operator +=(const Vec3& vector);

    /*!
     * \brief Scalar multiplication.
     * \param scalar Scalar multiplier.
     * \return Product vector.
     * \note Method has a side-effect.
     */
    MATH_API Vec3& operator *=(float scalar);

    /*!
     * \brief Vectors equalty check.
     * \param vector Compared vector.
     * \return true if vectors are equal, false otherwise.
     */
    MATH_API bool operator ==(const Vec3& vector) const;

    /*!
     * \brief Vectors inequalty check.
     * \param vector Compared vector.
     * \return false if vectors are equal, true otherwise.
     */
    MATH_API bool operator !=(const Vec3& vector) const;

    /*!
     * \brief Vector inversion.
     * \return Inverted vector.
     * \note Method has a side-effect.
     */
    MATH_API Vec3 operator -() const;

    /*!
     * \brief Dot product calculation.
     * \param vector Vector mutliplier.
     * \return Scalar (dot) product.
     */
    MATH_API float dot(const Vec3& vector) const;

    /*!
     * \brief Cross product calculation.
     * \param vector Vector mutliplier.
     * \return Vector (cross) product.
     */
    MATH_API Vec3 cross(const Vec3& vector) const;

    /*!
     * \brief Vector normalization.
     * \return Normalized (unit) vector.
     * \note Method has a side-effect.
     */
    MATH_API Vec3& normalize();

    /*!
     * \brief Vector's length calculation.
     * \return Vector length.
     */
    MATH_API float length() const;

    /*!
     * \brief Vector's square length calculation.
     * \return Vector square length.
     */
    MATH_API float squareLength() const;

    /*!
     * \brief Vector's component selector.
     * \param index Component's index.
     * \return Component's value.
     * \note You are advised to use #X, #Y, #Z constants as indices.
     */
    MATH_API float get(int index) const;

    /*!
     * \brief Vector's component mutator.
     * \param index Component's index.
     * \param value Component's new value.
     * \note You are advised to use #X, #Y, #Z constants as indices.
     */
    MATH_API void set(int index, float value);

    /*!
     * \brief Vector's data accessor.
     * \return Vector's data pointer.
     */
    MATH_API const float* data() const;

private:
    float vector[3];
};

}  // namespace Math

#endif  // VEC3_H
