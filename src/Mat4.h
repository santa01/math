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

#ifndef MAT4_H
#define MAT4_H

#include <Platform.h>

namespace Math {

class Mat3;
class Vec4;

/*!
 * \brief 4x4 two dimentional matrix.
 * \details Mat4 implements basic operations that are:
 *          * matrix-matrix addition, difference, multiplication;
 *          * matrix-vector multiplication;
 *          * transposition, LU decomposition, inversion.
 */
class LIBRARY_EXPORT Mat4 {
public:
    /*!
     * \brief Default constructor.
     * \details Constructs the identity matrix.
     */
    Mat4();

    /*!
     * \brief Matrices multiplication.
     * \param matrix Matrix multiplier.
     * \return Product matrix.
     */
    Mat4 operator *(const Mat4& matrix) const;

    /*!
     * \brief Matrix by vector multiplication.
     * \param vector Vector multiplier.
     * \return Product vector.
     */
    Vec4 operator *(const Vec4& vector) const;

    /*!
     * \brief Matrix by scalar multiplication.
     * \param scalar Scalar multiplier.
     * \return Product matrix.
     */
    Mat4 operator *(float scalar) const;

    /*!
     * \brief Matrices addition.
     * \param matrix Summand matrix.
     * \return Sum matrix.
     */
    Mat4 operator +(const Mat4& matrix) const;
    /*!
     * \brief Matrices substraction.
     * \param matrix Substracted matrix.
     * \return Difference matrix.
     */
    Mat4 operator -(const Mat4& matrix) const;

    /*!
     * \brief Matrices equalty check.
     * \param matrix Compared matrix.
     * \return true if matrices are equal, false otherwise.
     */
    bool operator ==(const Mat4& matrix) const;

    /*!
     * \brief Matrices inequalty check.
     * \param matrix Compared matrix.
     * \return false if matrices are equal, true otherwise.
     */
    bool operator !=(const Mat4& matrix) const;

    /*!
     * \brief Matrix transposition.
     * \return Transposed matrix.
     * \note Method has a side-effect.
     */
    Mat4& transpose();

    /*!
     * \brief Matrix LU decomposition.
     * \details This method implements doolitle LU decomposition argorithm. References:
     *           * http://www.engr.colostate.edu/~thompson/hPage/CourseMat/Tutorials/CompMethods/doolittle.pdf
     *           * https://vismor.com/documents/network_analysis/matrix_algorithms/S4.SS2.php
     *           * http://en.wikipedia.org/wiki/LU_decomposition#Doolittle_algorithm
     *
     * \param lower Lower triangular matrix.
     * \param upper Upper triangular matrix.
     */
    void decompose(Mat4& lower, Mat4& upper) const;

    /*!
     * \brief Matrix inversion.
     * \details This methos finds inverse matrix by LU-decomposition and further equation solving:
     *           -# L * Z = I
     *           -# U * X = Z
     *           -# L * U * X = I
     *
     *           Where:
     *            * L and U are lower and upper triangular matrices got by decompose(),
     *            * X and I are respective columns of inverse and identity matrices.
     *
     * \return Inverted matrix.
     */
    Mat4& invert();

    /*!
     * \brief Solve matrix equation with a lower triangular matrix.
     * \details Performs forward substitution for lower triangular marix. References:
     *           * http://en.wikipedia.org/wiki/Triangular_matrix#Forward_and_back_substitution
     *
     * \param absolute Vector of absolute values.
     * \return Vector of unknown values.
     * \note Matrix is assumed to be triangular, no check is performed.
     */
    Vec4 solveL(const Vec4& absolute) const;

    /*!
     * \brief Solve matrix equation with an upper triangular matrix.
     * \details Performs backward substitution for upper triangular marix. References:
     *           * http://en.wikipedia.org/wiki/Triangular_matrix#Forward_and_back_substitution
     *
     * \param absolute Vector of absolute values.
     * \return Vector of unknown values.
     * \note Matrix is assumed to be triangular, no check is performed.
     */
    Vec4 solveU(const Vec4& absolute) const;

    /*!
     * \brief Matrix's element selector.
     * \param row Element's row.
     * \param column Element's column.
     * \return Element's value.
     */
    float get(int row, int column) const;

    /*!
     * \brief Matrix's element mutator.
     * \param row Element's row.
     * \param column Element's column.
     * \param value Element's new value.
     */
    void set(int row, int column, float value);

    /*!
     * \brief Matrix's data accessor.
     * \return Matrix's data pointer.
     */
    const float* data() const;

    /*!
     * \brief Mat3 matrix extraction.
     * \details Composes Mat3 from first three rows and columns.
     * \return 3x3 two dimetional matrix.
     */
    Mat3 extractMat3() const;

private:
    float matrix[4][4];
};

}  // namespace Math

#endif  // MAT4_H
