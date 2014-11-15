/*
 * Quantum++
 *
 * Copyright (c) 2013 - 2014 Vlad Gheorghiu (vgheorgh@gmail.com)
 *
 * This file is part of Quantum++.
 *
 * Quantum++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Quantum++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Quantum++.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDE_FUNCTIONS_H_
#define INCLUDE_FUNCTIONS_H_

// Collection of generic quantum computing functions

namespace qpp
{

// Eigen function wrappers
/**
* \brief Transpose
*
* \param A Eigen expression
* \return Transpose of \a A, as a dynamic matrix
* over the same scalar field as \a A
*/
template<typename Derived>
DynMat<typename Derived::Scalar> transpose(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::transpose()", Exception::Type::ZERO_SIZE);

    return rA.transpose();
}

/**
* \brief Complex conjugate
*
* \param A Eigen expression
* \return Complex conjugate of \a A, as a dynamic matrix
* over the same scalar field as \a A
*/
template<typename Derived>
DynMat<typename Derived::Scalar> conjugate(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::conjugate()", Exception::Type::ZERO_SIZE);

    return rA.conjugate();
}

/**
* \brief Adjoint
*
* \param A Eigen expression
* \return Adjoint (Hermitian conjugate) of \a A, as a dynamic matrix
* over the same scalar field as \a A
*/
template<typename Derived>
DynMat<typename Derived::Scalar> adjoint(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::adjoint()", Exception::Type::ZERO_SIZE);

    return rA.adjoint();
}

/**
* \brief Inverse
*
* \param A Eigen expression
* \return Inverse of \a A, as a dynamic matrix
* over the same scalar field as \a A
*/
template<typename Derived>
DynMat<typename Derived::Scalar> inverse(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::inverse()", Exception::Type::ZERO_SIZE);

    return rA.inverse();
}

/**
* \brief Trace
*
* \param A Eigen expression
* \return Trace of \a A, as a scalar in the same scalar field as \a A
*/
template<typename Derived>
typename Derived::Scalar trace(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::trace()", Exception::Type::ZERO_SIZE);

    return rA.trace();
}

/**
* \brief Determinant
*
* \param A Eigen expression
* \return Determinant of \a A, as a scalar in the same scalar field as \a A.
* Returns \f$\pm \infty\f$ when the determinant overflows/underflows.
*/
template<typename Derived>
typename Derived::Scalar det(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::det()", Exception::Type::ZERO_SIZE);

    return rA.determinant();
}

/**
* \brief Logarithm of the determinant
*
* Useful when the determinant overflows/underflows
*
* \param A Eigen expression
* \return Logarithm of the determinant of \a A, as a scalar
* in the same scalar field as \a A
*/
template<typename Derived>
typename Derived::Scalar logdet(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::logdet()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::logdet()",
                Exception::Type::MATRIX_NOT_SQUARE);

    Eigen::PartialPivLU<DynMat<typename Derived::Scalar>> lu(rA);
    DynMat<typename Derived::Scalar> U =
            lu.matrixLU().template triangularView<Eigen::Upper>();
    typename Derived::Scalar result = std::log(U(0, 0));

    for (std::size_t i = 1; i < static_cast<std::size_t>(rA.rows()); ++i)
        result += std::log(U(i, i));

    return result;

}

/**
* \brief Element-wise sum of \a A
*
* \param A Eigen expression
* \return Element-wise sum of \a A, as a scalar
* in the same scalar field as \a A
*/
template<typename Derived>
typename Derived::Scalar sum(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::sum()", Exception::Type::ZERO_SIZE);

    return rA.sum();
}

/**
* \brief Element-wise product of \a A
*
* \param A Eigen expression
* \return Element-wise product of \a A, as a scalar
* in the same scalar field as \a A
*/
template<typename Derived>
typename Derived::Scalar prod(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::sum()", Exception::Type::ZERO_SIZE);

    return rA.prod();
}

/**
* \brief Frobenius norm
*
* \param A Eigen expression
* \return Frobenius norm of \a A, as a real number
*/
template<typename Derived>
double norm(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::norm()", Exception::Type::ZERO_SIZE);

    // convert matrix to complex then return its norm
    return (rA.template cast<cplx>()).norm();
}

/**
* \brief Eigenvalues
*
* \param A Eigen expression
* \return Eigenvalues of \a A, as a complex dynamic column vector
*/
template<typename Derived>
DynColVect<cplx> evals(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::evals()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::evals()", Exception::Type::MATRIX_NOT_SQUARE);

    Eigen::ComplexEigenSolver<cmat> es(rA.template cast<cplx>());

    return es.eigenvalues();
}

/**
* \brief Eigenvectors
*
* \param A Eigen expression
* \return Eigenvectors of \a A, as columns of a complex matrix
*/
template<typename Derived>
cmat evects(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::evects()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::evects()", Exception::Type::MATRIX_NOT_SQUARE);

    Eigen::ComplexEigenSolver<cmat> es(rA.template cast<cplx>());

    return es.eigenvectors();
}

/**
* \brief Hermitian eigenvalues
*
* \param A Eigen expression
* \return Eigenvalues of Hermitian \a A, as a real dynamic column vector
*/
template<typename Derived>
DynColVect<double> hevals(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::hevals()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::hevals()", Exception::Type::MATRIX_NOT_SQUARE);

    Eigen::SelfAdjointEigenSolver<cmat> es(rA.template cast<cplx>());

    return es.eigenvalues();
}

/**
* \brief Hermitian eigenvectors
*
* \param A Eigen expression
* \return Eigenvectors of Hermitian \a A, as columns of a complex matrix
*/
template<typename Derived>
cmat hevects(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::hevects()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::hevects()",
                Exception::Type::MATRIX_NOT_SQUARE);

    Eigen::SelfAdjointEigenSolver<cmat> es(rA.template cast<cplx>());

    return es.eigenvectors();
}

/**
* \brief Singular values, in decreasing order
*
* \param A Eigen expression
* \return Singular values of \a A, in decreasing order,
* as a real dynamic column vector
*/
template<typename Derived>
DynColVect<double> svals(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::svals()", Exception::Type::ZERO_SIZE);

    Eigen::JacobiSVD<DynMat<typename Derived::Scalar>> svd(rA);

    return svd.singularValues();
}

/**
* \brief Left singular vectors
*
* \param A Eigen expression
* \return Complex dynamic matrix, whose columns are the left singular
* vectors of \a A
*/
template<typename Derived>
cmat svdU(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::svdU()", Exception::Type::ZERO_SIZE);

    Eigen::JacobiSVD<DynMat<typename Derived::Scalar>> svd(rA,
            Eigen::DecompositionOptions::ComputeFullU);

    return svd.matrixU();
}

/**
* \brief Right singular vectors
*
* \param A Eigen expression
* \return Complex dynamic matrix, whose columns are the right singular
* vectors of \a A
*/
template<typename Derived>
cmat svdV(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::svdV()", Exception::Type::ZERO_SIZE);

    Eigen::JacobiSVD<DynMat<typename Derived::Scalar>> svd(rA,
            Eigen::DecompositionOptions::ComputeFullV);

    return svd.matrixV();
}

// Matrix functional calculus

/**
* \brief Functional calculus f(A)
*
* \param A Eigen expression
* \param f Pointer-to-function from complex to complex
* \return \a \f$f(A)\f$
*/
template<typename Derived>
cmat funm(const Eigen::MatrixBase<Derived>& A, cplx (* f)(const cplx&))
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::funm()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::funm()", Exception::Type::MATRIX_NOT_SQUARE);

    Eigen::ComplexEigenSolver<cmat> es(rA.template cast<cplx>());
    cmat evects = es.eigenvectors();
    cmat evals = es.eigenvalues();
    for (std::size_t i = 0; i < static_cast<std::size_t>(evals.rows()); ++i)
        evals(i) = (*f)(evals(i)); // apply f(x) to each eigenvalue

    cmat evalsdiag = evals.asDiagonal();

    return evects * evalsdiag * evects.inverse();
}

/**
* \brief Matrix square root
*
* \param A Eigen expression
* \return Matrix square root of \a A
*/
template<typename Derived>
cmat sqrtm(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::sqrtm()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::sqrtm()", Exception::Type::MATRIX_NOT_SQUARE);

    return funm(rA, &std::sqrt);
}

/**
* \brief Matrix absolut value
*
* \param A Eigen expression
* \return Matrix absolut value of \a A
*/
template<typename Derived>
cmat absm(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::absm()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::absm()", Exception::Type::MATRIX_NOT_SQUARE);

    return sqrtm(adjoint(rA) * rA);
}

/**
* \brief Matrix exponential
*
* \param A Eigen expression
* \return Matrix exponential of \a A
*/
template<typename Derived>
cmat expm(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::expm()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::expm()", Exception::Type::MATRIX_NOT_SQUARE);

    return funm(rA, &std::exp);
}

/**
* \brief Matrix logarithm
*
* \param A Eigen expression
* \return Matrix logarithm of \a A
*/
template<typename Derived>
cmat logm(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::logm()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::logm()", Exception::Type::MATRIX_NOT_SQUARE);

    return funm(rA, &std::log);
}

/**
* \brief Matrix sin
*
* \param A Eigen expression
* \return Matrix sine of \a A
*/
template<typename Derived>
cmat sinm(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::sinm()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::sinm()", Exception::Type::MATRIX_NOT_SQUARE);

    return funm(rA, &std::sin);
}

/**
* \brief Matrix cos
*
* \param A Eigen expression
* \return Matrix cosine of \a A
*/
template<typename Derived>
cmat cosm(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::cosm()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::cosm()", Exception::Type::MATRIX_NOT_SQUARE);

    return funm(rA, &std::cos);
}

/**
* \brief Matrix power
*
* Uses the spectral decomposition of \a A to compute the matrix power.
* By convention \f$A^0 = I\f$.
*
* \param A Eigen expression
* \param z Complex number
* \return Matrix power \f$A^z\f$
*/
template<typename Derived>
cmat spectralpowm(const Eigen::MatrixBase<Derived>& A, const cplx z)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::spectralpowm()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::spectralpowm()",
                Exception::Type::MATRIX_NOT_SQUARE);

    // Define A^0 = Id, for z IDENTICALLY zero
    if (real(z) == 0 && imag(z) == 0)
        return cmat::Identity(rA.rows(), rA.rows());

    Eigen::ComplexEigenSolver<cmat> es(rA.template cast<cplx>());
    cmat evects = es.eigenvectors();
    cmat evals = es.eigenvalues();
    for (std::size_t i = 0; i < static_cast<std::size_t>(evals.rows()); ++i)
        evals(i) = std::pow(evals(i), z);

    cmat evalsdiag = evals.asDiagonal();

    return evects * evalsdiag * evects.inverse();

}

/**
* \brief Matrix power
*
* Explicitly multiplies the matrix \a A with itself \a n times.
* By convention \f$A^0 = I\f$.
*
* \param A Eigen expression
* \param n Non-negative integer
* \return Matrix power \f$A^n\f$, as a dynamic matrix
* over the same scalar field as \a A
*/
template<typename Derived>
DynMat<typename Derived::Scalar> powm(const Eigen::MatrixBase<Derived>& A,
        std::size_t n)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::powm()", Exception::Type::ZERO_SIZE);

    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::powm()", Exception::Type::MATRIX_NOT_SQUARE);

    DynMat<typename Derived::Scalar> result = rA;

    if (n == 0)
        return DynMat<typename Derived::Scalar>::Identity(
                rA.rows(), rA.rows());

    for (std::size_t i = 1; i < n; ++i)
        result *= rA;

    return result;
}

/**
* \brief Schatten norm
*
* \param A Eigen expression
* \param p Integer, greater or equal to 1
* \return Schatten-\a p norm of \a A, as a real number
*/
template<typename Derived>
double schatten(const Eigen::MatrixBase<Derived>& A, std::size_t p)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::schatten()", Exception::Type::ZERO_SIZE);
    if (p < 1)
        throw Exception("qpp::schatten()", Exception::Type::OUT_OF_RANGE);

    if (p == infty) // infinity norm (largest singular value)
        return svals(rA)[0];

    return std::pow(trace(powm(absm(rA), p)).real(), 1. / p);
}

// other functions

/**
* \brief Functor
*
* \param A Eigen expression
* \param f Pointer-to-function from scalars of \a A to \a OutputScalar
* \return Component-wise \f$f(A)\f$, as a dynamic matrix
* over the \a OutputScalar scalar field
*/
template<typename OutputScalar, typename Derived>
DynMat<OutputScalar> cwise(const Eigen::MatrixBase<Derived>& A,
        OutputScalar (* f)(const typename Derived::Scalar&))
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::cwise()", Exception::Type::ZERO_SIZE);

    DynMat<OutputScalar> result(rA.rows(), rA.cols());

#pragma omp parallel for collapse(2)
    for (std::size_t j = 0; j < static_cast<std::size_t>(rA.cols()); ++j)
        for (std::size_t i = 0; i < static_cast<std::size_t>(rA.rows()); ++i)
            result(i, j) = (*f)(rA(i, j));

    return result;
}

// Kronecker product of multiple matrices, preserve return type
// variadic template
/**
* \brief Kronecker product
*
* Used to stop the recursion for the variadic template version of
* qpp::kron()
*
* \param head Eigen expression
* \return Its argument \a head
*/
template<typename T>
DynMat<typename T::Scalar> kron(const T& head)
{
    return head;
}

/**
* \brief Kronecker product
*
* \param head Eigen expression
* \param tail Variadic Eigen expression (zero or more parameters)
* \return Kronecker product of all input parameters,
* evaluated from left to right, as a dynamic matrix
* over the same scalar field as its arguments
*/
template<typename T, typename ... Args>
DynMat<typename T::Scalar> kron(const T& head, const Args& ... tail)
{
    return internal::_kron2(head, kron(tail...));
}

/**
* \brief Kronecker product
*
* \param As std::vector of Eigen expressions
* \return Kronecker product of all elements in \a As,
* evaluated from left to right, as a dynamic matrix
* over the same scalar field as its arguments
*/
template<typename Derived>
DynMat<typename Derived::Scalar> kron(const std::vector<Derived>& As)
{
    if (As.size() == 0)
        throw Exception("qpp::kron()", Exception::Type::ZERO_SIZE);

    for (auto&& it : As)
        if (!internal::_check_nonzero_size(it))
            throw Exception("qpp::kron()", Exception::Type::ZERO_SIZE);

    DynMat<typename Derived::Scalar> result = As[0];
    for (std::size_t i = 1; i < As.size(); ++i)
    {
        result = kron(result, As[i]);
    }

    return result;
}

// Kronecker product of a list of matrices, preserve return type
// deduce the template parameters from initializer_list
/**
* \brief Kronecker product
*
* \param As std::initializer_list of Eigen expressions,
* such as \a {A1, A2, ... ,Ak}
* \return Kronecker product of all elements in \a As,
* evaluated from left to right, as a dynamic matrix
* over the same scalar field as its arguments
*/
template<typename Derived>
DynMat<typename Derived::Scalar> kron(const std::initializer_list<Derived>& As)
{
    return kron(std::vector<Derived>(As));
}

/**
* \brief Kronecker power
*
* \param A Eigen expression
* \param n Non-negative integer
* \return Kronecker product of \a A with itself \a n times \f$A^{\otimes n}\f$,
* as a dynamic matrix over the same scalar field as \a A
*/
template<typename Derived>
DynMat<typename Derived::Scalar> kronpow(const Eigen::MatrixBase<Derived>& A,
        std::size_t n)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::kronpow()", Exception::Type::ZERO_SIZE);

    // check out of range
    if (n == 0)
        throw Exception("qpp::kronpow()", Exception::Type::OUT_OF_RANGE);

    DynMat<typename Derived::Scalar> result = rA;
    for (std::size_t i = 1; i < n; ++i)
        result = kron(result, rA);

    return result;
}

/**
* \brief Reshape
*
*  Uses column-major order when reshaping (same as MATLAB)
*
* \param A Eigen expression
* \param rows Number of rows of the reshaped matrix
* \param cols Number of columns of the reshaped matrix
* \return Reshaped matrix with \a rows rows and \a cols columns,
* as a dynamic matrix over the same scalar field as \a A
*/
template<typename Derived>
DynMat<typename Derived::Scalar> reshape(const Eigen::MatrixBase<Derived>& A,
        std::size_t rows, std::size_t cols)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    std::size_t Arows = static_cast<std::size_t>(rA.rows());
    std::size_t Acols = static_cast<std::size_t>(rA.cols());

    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::reshape()", Exception::Type::ZERO_SIZE);

    if (Arows * Acols != rows * cols)
        throw Exception("qpp::reshape()",
                Exception::Type::DIMS_MISMATCH_MATRIX);

    return Eigen::Map<DynMat<typename Derived::Scalar>>(
            const_cast<typename Derived::Scalar*>(rA.data()), rows, cols);
}

/**
* \brief Commutator
*
*  Commutator \f$ [A,B] = AB - BA \f$.
*  Both \a A and \a B must be Eigen expressions over the same scalar field.
*
* \param A Eigen expression
* \param B Eigen expression
* \return Commutator \f$AB -BA\f$, as a dynamic matrix
* over the same scalar field as \a A
*/
template<typename Derived1, typename Derived2>
DynMat<typename Derived1::Scalar> comm(const Eigen::MatrixBase<Derived1>& A,
        const Eigen::MatrixBase<Derived2>& B)
{
    const DynMat<typename Derived1::Scalar>& rA = A;
    const DynMat<typename Derived2::Scalar>& rB = B;

    // EXCEPTION CHECKS

    // check types
    if (!std::is_same<typename Derived1::Scalar,
            typename Derived2::Scalar>::value)
        throw Exception("qpp::comm()", Exception::Type::TYPE_MISMATCH);

    // check zero-size
    if (!internal::_check_nonzero_size(rA)
            || !internal::_check_nonzero_size(rB))
        throw Exception("qpp::comm()", Exception::Type::ZERO_SIZE);

    // check square matrices
    if (!internal::_check_square_mat(rA) || !internal::_check_square_mat(rB))
        throw Exception("qpp::comm()", Exception::Type::MATRIX_NOT_SQUARE);

    // check equal dimensions
    if (rA.rows() != rB.rows())
        throw Exception("qpp::comm()", Exception::Type::DIMS_NOT_EQUAL);

    return rA * rB - rB * rA;
}

/**
* \brief Anti-commutator
*
*  Anti-commutator \f$ \{A,B\} = AB + BA \f$.
*  Both \a A and \a B must be Eigen expressions over the same scalar field.
*
* \param A Eigen expression
* \param B Eigen expression
* \return Anti-commutator \f$AB +BA\f$, as a dynamic matrix
* over the same scalar field as \a A
*/
template<typename Derived1, typename Derived2>
DynMat<typename Derived1::Scalar> anticomm(
        const Eigen::MatrixBase<Derived1>& A,
        const Eigen::MatrixBase<Derived2>& B)
{
    const DynMat<typename Derived1::Scalar>& rA = A;
    const DynMat<typename Derived2::Scalar>& rB = B;

    // EXCEPTION CHECKS

    // check types
    if (!std::is_same<typename Derived1::Scalar,
            typename Derived2::Scalar>::value)
        throw Exception("qpp::anticomm()", Exception::Type::TYPE_MISMATCH);

    // check zero-size
    if (!internal::_check_nonzero_size(rA)
            || !internal::_check_nonzero_size(rB))
        throw Exception("qpp::anticomm()", Exception::Type::ZERO_SIZE);

    // check square matrices
    if (!internal::_check_square_mat(rA) || !internal::_check_square_mat(rB))
        throw Exception("qpp::anticomm()",
                Exception::Type::MATRIX_NOT_SQUARE);

    // check equal dimensions
    if (rA.rows() != rB.rows())
        throw Exception("qpp::anticomm()", Exception::Type::DIMS_NOT_EQUAL);

    return rA * rB + rB * rA;
}

/**
* \brief Projector
*
*  Normalized projector onto state vector
*
* \param V Eigen expression
* \return Projector onto the state vector \a V, or the matrix \a Zero
* if \a V has norm zero (i.e. smaller than qpp::eps),
* as a dynamic matrix over the same scalar field as \a A
*/
template<typename Derived>
DynMat<typename Derived::Scalar> prj(const Eigen::MatrixBase<Derived>& V)
{
    const DynMat<typename Derived::Scalar>& rV = V;

    // check zero-size
    if (!internal::_check_nonzero_size(rV))
        throw Exception("qpp::prj()", Exception::Type::ZERO_SIZE);

    // check column vector
    if (!internal::_check_col_vector(rV))
        throw Exception("qpp::prj()", Exception::Type::MATRIX_NOT_CVECTOR);

    double normV = norm(rV);
    if (normV > eps)
        return rV * adjoint(rV) / (normV * normV);
    else
        return DynMat<typename Derived::Scalar>::Zero(rV.rows(), rV.rows());

}

/**
* \brief Gram-Schmidt orthogonalization
*
* \param Vs std::vector of Eigen expressions as column vectors
* \return Gram-Schmidt vectors of \a Vs as columns of a dynamic matrix
* over the same scalar field as its arguments
*/
template<typename Derived>
DynMat<typename Derived::Scalar> grams(const std::vector<Derived>& Vs)
{
    // check empty list
    if (!internal::_check_nonzero_size(Vs))
        throw Exception("qpp::grams()", Exception::Type::ZERO_SIZE);

    for (auto&& it : Vs)
        if (!internal::_check_nonzero_size(it))
            throw Exception("qpp::grams()", Exception::Type::ZERO_SIZE);

    // check that Vs[0] is a column vector
    if (!internal::_check_col_vector(Vs[0]))
        throw Exception("qpp::grams()", Exception::Type::MATRIX_NOT_CVECTOR);

    // now check that all the rest match the size of the first vector
    for (auto&& it : Vs)
        if (it.rows() != Vs[0].rows() || it.cols() != 1)
            throw Exception("qpp::grams()", Exception::Type::DIMS_NOT_EQUAL);

    DynMat<typename Derived::Scalar> cut =
            DynMat<typename Derived::Scalar>::Identity(Vs[0].rows(),
                    Vs[0].rows());

    DynMat<typename Derived::Scalar> vi =
            DynMat<typename Derived::Scalar>::Zero(Vs[0].rows(), 1);

    std::vector<DynMat<typename Derived::Scalar>> outvecs;
    // find the first non-zero vector in the list
    std::size_t pos = 0;
    for (pos = 0; pos < Vs.size(); ++pos)
    {
        if (norm(Vs[pos]) > eps) // add it as the first element
        {
            outvecs.push_back(Vs[pos]);
            break;
        }
    }

    // start the process
    for (std::size_t i = pos + 1; i < Vs.size(); ++i)
    {
        cut -= prj(outvecs[i - 1 - pos]);
        vi = cut * Vs[i];
        outvecs.push_back(vi);
    }

    DynMat<typename Derived::Scalar> result(Vs[0].rows(), outvecs.size());

    std::size_t cnt = 0;
    for (auto&& it : outvecs)
    {
        double normV = norm(it);
        if (normV > eps) // we add only the non-zero vectors
        {
            result.col(cnt) = it / normV;
            cnt++;
        }
    }

    return result.block(0, 0, Vs[0].rows(), cnt);
}

// deduce the template parameters from initializer_list
/**
* \brief Gram-Schmidt orthogonalization
*
* \param Vs std::initializer_list of Eigen expressions as column vectors
* \return Gram-Schmidt vectors of \a Vs as columns of a dynamic matrix
* over the same scalar field as its arguments
*/
template<typename Derived>
DynMat<typename Derived::Scalar> grams(
        const std::initializer_list<Derived>& Vs)
{
    return grams(std::vector<Derived>(Vs));
}

/**
* \brief Gram-Schmidt orthogonalization
*
* \param A Eigen expression, the input vectors are the columns of \a A
* \return Gram-Schmidt vectors of the columns of \a A,
* as columns of a dynamic matrix over the same scalar field as \a A
*/
template<typename Derived>
DynMat<typename Derived::Scalar> grams(const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::grams()", Exception::Type::ZERO_SIZE);

    std::vector<DynMat<typename Derived::Scalar>> input;

    for (std::size_t i = 0; i < static_cast<std::size_t>(rA.cols()); ++i)
        input.push_back(rA.col(i));

    return grams<DynMat<typename Derived::Scalar>>(input);
}

/**
* \brief Non-negative integer index to multi-index
*
* Uses standard lexicographical order, i.e. 00...0, 00...1 etc.
*
* \param n Non-negative integer index
* \param dims Dimensions of the multi-partite system
* \return Multi-index of the same size as \a dims
*/
std::vector<std::size_t> n2multiidx(std::size_t n,
        const std::vector<std::size_t>& dims)
{
    if (!internal::_check_dims(dims))
        throw Exception("qpp::n2multiidx()", Exception::Type::DIMS_INVALID);

    auto multiply = [](const std::size_t x, const std::size_t y) -> std::size_t
    {
        return x * y;
    };

    if (n >= std::accumulate(std::begin(dims), std::end(dims), 1u, multiply))
        throw Exception("qpp::n2multiidx()", Exception::Type::OUT_OF_RANGE);

    // double the size for matrices reshaped as vectors
    std::size_t result[2 * maxn];
    internal::_n2multiidx(n, dims.size(), dims.data(), result);

    return std::vector<std::size_t>(result, result + dims.size());
}

/**
* \brief Multi-index to non-negative integer index
*
* Uses standard lexicographical order, i.e. 00...0, 00...1 etc.
*
* \param midx Multi-index
* \param dims Dimensions of the multi-partite system
* \return Non-negative integer index
*/
std::size_t multiidx2n(const std::vector<std::size_t>& midx,
        const std::vector<std::size_t>& dims)
{
    if (!internal::_check_dims(dims))
        throw Exception("qpp::multiidx2n()", Exception::Type::DIMS_INVALID);

    for (std::size_t i = 0; i < dims.size(); ++i)
        if (midx[i] >= dims[i])
            throw Exception("qpp::multiidx2n()",
                    Exception::Type::OUT_OF_RANGE);

    return internal::_multiidx2n(midx.data(), dims.size(), dims.data());
}

/**
* \brief Multi-partite qudit ket
*
* Constructs the multi-partite qudit ket \f$|\mathrm{mask}\rangle\f$,
* where \a mask is a std::vector of non-negative integers.
* Each element in \a mask has to be smaller than the corresponding element
* in \a dims.
*
* \param mask std::vector of non-negative integers
* \param dims Dimensions of the multi-partite system
* \return Multi-partite qudit state vector, as a complex dynamic column vector
*/
ket mket(const std::vector<std::size_t>& mask,
        const std::vector<std::size_t>& dims)
{
    std::size_t n = mask.size();
    auto multiply = [](std::size_t x, std::size_t y) -> std::size_t
    {
        return x * y;
    };

    std::size_t D = std::accumulate(std::begin(dims), std::end(dims), 1u,
            multiply);

    // check zero size
    if (n == 0)
        throw Exception("qpp::mket()", Exception::Type::ZERO_SIZE);
    // check valid dims
    if (!internal::_check_dims(dims))
        throw Exception("qpp::mket()", Exception::Type::DIMS_INVALID);
    // check mask and dims have the same size
    if (mask.size() != dims.size())
        throw Exception("qpp::mket()", Exception::Type::SUBSYS_MISMATCH_DIMS);
    // check mask is a valid vector
    for (std::size_t i = 0; i < n; ++i)
        if (mask[i] >= dims[i])
            throw Exception("qpp::mket()",
                    Exception::Type::SUBSYS_MISMATCH_DIMS);

    ket result = ket::Zero(D);
    std::size_t pos = multiidx2n(mask, dims);
    result(pos) = 1;

    return result;
}

/**
* \brief Multi-partite qudit ket
*
* Constructs the multi-partite qudit ket \f$|\mathrm{mask}\rangle\f$,
* all subsystem having equal dimension \a d.
* \a mask is a std::vector of non-negative integers, and
* each element in \a mask has to be strictly smaller than \a d.
*
* \param mask std::vector of non-negative integers
* \param d Subsystem dimensions
* \return Multi-partite qudit state vector, as a complex dynamic column vector
*/
ket mket(const std::vector<std::size_t>& mask, std::size_t d = 2)
{
    std::size_t n = mask.size();
    std::size_t D = static_cast<std::size_t>(std::llround(std::pow(d, n)));

    // check zero size
    if (n == 0)
        throw Exception("qpp::mket()", Exception::Type::ZERO_SIZE);
    // check valid dims
    if (d == 0)
        throw Exception("qpp::mket()", Exception::Type::DIMS_INVALID);
    // check mask is a valid vector
    for (std::size_t i = 0; i < n; ++i)
        if (mask[i] >= d)
            throw Exception("qpp::mket()",
                    Exception::Type::SUBSYS_MISMATCH_DIMS);

    ket result = ket::Zero(D);
    std::vector<std::size_t> dims(n, d);
    std::size_t pos = multiidx2n(mask, dims);
    result(pos) = 1;

    return result;
}

/**
* \brief Projector onto multi-partite qudit ket
*
* Constructs the projector onto the multi-partite qudit ket
* \f$|\mathrm{mask}\rangle\f$,
* where \a mask is a std::vector of non-negative integers.
* Each element in \a mask has to be smaller than the corresponding element
* in \a dims.
*
* \param mask std::vector of non-negative integers
* \param dims Dimensions of the multi-partite system
* \return Projector onto multi-partite qudit state vector,
* as a complex dynamic matrix
*/
cmat mprj(const std::vector<std::size_t>& mask,
        const std::vector<std::size_t>& dims)
{
    std::size_t n = mask.size();
    auto multiply = [](std::size_t x, std::size_t y) -> std::size_t
    {
        return x * y;
    };

    std::size_t D = std::accumulate(std::begin(dims), std::end(dims), 1u,
            multiply);

    // check zero size
    if (n == 0)
        throw Exception("qpp::mprj()", Exception::Type::ZERO_SIZE);
    // check valid dims
    if (!internal::_check_dims(dims))
        throw Exception("qpp::mprj()", Exception::Type::DIMS_INVALID);
    // check mask and dims have the same size
    if (mask.size() != dims.size())
        throw Exception("qpp::mprj()", Exception::Type::SUBSYS_MISMATCH_DIMS);
    // check mask is a valid vector
    for (std::size_t i = 0; i < n; ++i)
        if (mask[i] >= dims[i])
            throw Exception("qpp::mprj()",
                    Exception::Type::SUBSYS_MISMATCH_DIMS);

    cmat result = cmat::Zero(D, D);
    std::size_t pos = multiidx2n(mask, dims);
    result(pos, pos) = 1;

    return result;
}

/**
* \brief Projector onto multi-partite qudit ket
*
* Constructs the projector onto the multi-partite qudit ket
* \f$|\mathrm{mask}\rangle\f$,
* all subsystem having equal dimension \a d.
* \a mask is a std::vector of non-negative integers, and
* each element in \a mask has to be strictly smaller than \a d.
*
* \param mask std::vector of non-negative integers
* \param d Subsystem dimensions
* \return Projector onto multi-partite qudit state vector,
* as a complex dynamic matrix
*/
cmat mprj(const std::vector<std::size_t>& mask, std::size_t d = 2)
{
    std::size_t n = mask.size();
    std::size_t D = static_cast<std::size_t>(std::llround(std::pow(d, n)));

    // check zero size
    if (n == 0)
        throw Exception("qpp::mprj()", Exception::Type::ZERO_SIZE);
    // check valid dims
    if (d == 0)
        throw Exception("qpp::mprj()", Exception::Type::DIMS_INVALID);
    // check mask is a valid vector
    for (std::size_t i = 0; i < n; ++i)
        if (mask[i] >= d)
            throw Exception("qpp::mprj()",
                    Exception::Type::SUBSYS_MISMATCH_DIMS);

    cmat result = cmat::Zero(D, D);
    std::vector<std::size_t> dims(n, d);
    std::size_t pos = multiidx2n(mask, dims);
    result(pos, pos) = 1;

    return result;
}

/**
* \brief Computes the absolut values squared of a range of complex numbers

* \param first Iterator to the first element of the range
* \param last  Iterator to the last element of the range
* \return Real vector consisting of the range's absolut values squared
*/
template<typename InputIterator>
std::vector<double> abssq(InputIterator first, InputIterator last)
{
    std::vector<double> weights(last - first);
    std::transform(first, last, std::begin(weights),
            [](const cplx& z) -> double
            {
                return std::pow(std::abs(z), 2);
            });

    return weights;
}

/**
* \brief Computes the absolut values squared of a column vector

* \param V Eigen expression
* \return Real vector consisting of the absolut values squared
*/
template<typename Derived>
std::vector<double> abssq(const Eigen::MatrixBase<Derived>& V)
{
    const DynMat<typename Derived::Scalar>& rV = V;

    // check zero-size
    if (!internal::_check_nonzero_size(rV))
        throw Exception("qpp::abssq()", Exception::Type::ZERO_SIZE);

    // check column vector
    if (!internal::_check_col_vector(rV))
        throw Exception("qpp::abssq()", Exception::Type::MATRIX_NOT_CVECTOR);

    std::vector<double> weights(rV.rows());
    std::transform(rV.data(), rV.data() + rV.rows(), std::begin(weights),
            [](const cplx& z) -> double
            {
                return std::pow(std::abs(z), 2);
            });

    return weights;
}

/**
* \brief Element-wise sum of a range
*
* \param first Iterator to the first element of the range
* \param last  Iterator to the last element of the range
* \return Element-wise sum of the range,
* as a scalar in the same scalar field as the range
*/
template<typename InputIterator>
auto sum(InputIterator first,
        InputIterator last) -> typename InputIterator::value_type
{
    return std::accumulate(first, last,
            static_cast<typename InputIterator::value_type>(0));
}

/**
* \brief Element-wise product of a range
*
* \param first Iterator to the first element of the range
* \param last  Iterator to the last element of the range
* \return Element-wise product of the range,
* as a scalar in the same scalar field as the range
*/
template<typename InputIterator>
auto prod(InputIterator first,
        InputIterator last) -> typename InputIterator::value_type
{
    return std::accumulate(first, last,
            static_cast<typename InputIterator::value_type>(1),
            [](const typename InputIterator::value_type& x,
                    const typename InputIterator::value_type& y)
            {
                return x * y;
            });
}

/**
* \brief Finds the pure state representation of a matrix
* proportional to a projector onto a pure state
*
* \note No purity check is done, the input state \a A must have rank one,
* otherwise the function returs the first non-zero eigenvector of \a A
*
* \param A Eigen expression, assumed to be proportional
* to a projector onto a pure state, i.e. \a A is assumed to have rank one
* \return The unique non-zero eigenvector of \a A,
* as a dynamic column vector over the same scalar field as \a A
*/
template<typename Derived>
DynColVect<typename Derived::Scalar> rho2pure(
        const Eigen::MatrixBase<Derived>& A)
{
    const DynMat<typename Derived::Scalar>& rA = A;

    // EXCEPTION CHECKS
    // check zero-size
    if (!internal::_check_nonzero_size(rA))
        throw Exception("qpp::rho2pure()", Exception::Type::ZERO_SIZE);
    // check square matrix
    if (!internal::_check_square_mat(rA))
        throw Exception("qpp::rho2pure()", Exception::Type::MATRIX_NOT_SQUARE);
    // END EXPCEPTION CHECKS

    DynColVect<double> tmp_evals = hevals(rA);
    cmat tmp_evects = hevects(rA);
    DynColVect<typename Derived::Scalar> result =
            DynColVect<typename Derived::Scalar>::Zero(rA.rows());
    // find the non-zero eigenvector
    // there is only one, assuming the state is pure
    for (std::size_t k = 0; k < static_cast<std::size_t>(rA.rows()); ++k)
    {
        if (std::abs(tmp_evals(k)) > eps)
        {
            result = tmp_evects.col(k);
            break;
        }
    }

    return result;
}

} /* namespace qpp */

#endif /* INCLUDE_FUNCTIONS_H_ */
