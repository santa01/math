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

#ifndef QUATERNION_H
#define QUATERNION_H

#include <Platform.h>

namespace Math {

class Vec3;
class Mat4;

/*!
 * \brief %Quaternion representation.
 * \details Quaternion implements basic operations that are:
 *          * multiplication;
 *          * normalization;
 *          * euler angles and Mat4 rotation matrix extraction.
 */
class LIBRARY_EXPORT Quaternion {
public:
    enum {
        X = 0,  /*!< X component index. */
        Y = 1,  /*!< Y component index. */
        Z = 2,  /*!< Z component index. */
        W = 3   /*!< W component index. */
    };

    /*!
     * \brief Default constructor.
     * \details Constructs a unit quaternion initializing every but W component with zero.
     */
    Quaternion();

    /*!
     * \brief Per-component constructor.
     * \details Constructs arbitrary quaternion based on x, y, z, w values.
     * \param x X component.
     * \param y Y component.
     * \param z Z component.
     * \param w W component.
     */
    Quaternion(float x, float y, float z, float w);

    /*!
     * \brief Axis-angle based constructor.
     * \details Constructs a quaternion describing arbitrary rotation around axis vector on angle radians.
     * \param axis Rotation axis vector.
     * \param angle Rotation angle in radians.
     */
    Quaternion(const Vec3& axis, float angle);

    /*!
     * \brief Quaternions multiplication.
     * \param quaternion %Quaternion multiplier.
     * \return Product quaternion.
     */
    Quaternion operator *(const Quaternion& quaternion) const;

    /*!
     * \brief %Quaternion normalization.
     * \return Normalized quaternion.
     * \note Method has a side-effect.
     */
    Quaternion& normalize();

    /*!
     * \brief %Quaternion's length calculation.
     * \return %Quaternion length.
     */
    float length() const;

    /*!
     * \brief %Quaternion's component selector.
     * \param index Component's index.
     * \return Component's value.
     * \note You are advised to use #X, #Y, #Z, #W constants as indices.
     */
    float get(int index) const;

    /*!
     * \brief %Quaternion's component mutator.
     * \param index Component's index.
     * \param value Component's new value.
     * \note You are advised to use #X, #Y, #Z, #W constants as indices.
     */
    void set(int index, float value);

    /*!
     * \brief Mat4 matrix extraction.
     * \details Composes Mat4 rotation matrix.
     * \return 4x4 two dimetional matrix.
     */
    Mat4 extractMat4() const;

    /*!
     * \brief Euler angles extraction.
     * \details Derives roll, yaw, pitch angle values in radians.
     * \param xAngle Rotation angle around X axis.
     * \param yAngle Rotation angle around Y axis.
     * \param zAngle Rotation angle around Z axis.
     */
    void extractEulerAngles(float& xAngle, float& yAngle, float& zAngle) const;

private:
    float vector[4];
};

}  // namespace Math

#endif  // QUATERNION_H
