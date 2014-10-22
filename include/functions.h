/*
 * functions.h
 *
 *  Created on: Mar 27, 2014
 *      Author: vlad
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

// Collection of quantum computing useful functions
namespace qpp
{
// Eigen function wrappers

/**
 * @brief Transpose
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Transpose of @a A, as a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> transpose(
		const Eigen::MatrixBase<Derived>& A)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("transpose", Exception::Type::ZERO_SIZE);

	return rA.transpose();
}

/**
 * @brief Complex conjugate
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Complex conjugate of @a A, as a dynamic matrix
 * over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> conjugate(
		const Eigen::MatrixBase<Derived>& A)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("conjugate", Exception::Type::ZERO_SIZE);

	return rA.conjugate();
}

/**
 * @brief Adjoint
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Adjoint (Hermitian conjugate) of @a A, as a dynamic matrix
 * over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> adjoint(
		const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("adjoint", Exception::Type::ZERO_SIZE);

	return rA.adjoint();
}

/**
 * @brief Inverse
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Inverse of @a A, as a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> inverse(
		const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("inverse", Exception::Type::ZERO_SIZE);

	return rA.inverse();
}

/**
 * @brief Trace
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Trace of @a A, as a dynamic matrix over the same scalar field
 */
template<typename Derived>
typename Derived::Scalar trace(const Eigen::MatrixBase<Derived>& A)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("trace", Exception::Type::ZERO_SIZE);

	return rA.trace();
}

/**
 * @brief Determinant
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Determinant of @a A, as a dynamic matrix over the same scalar field\n
 * Returns \f$\pm \infty\f$ when the determinant overflows/underflows
 *
 *
 */
template<typename Derived>
typename Derived::Scalar det(const Eigen::MatrixBase<Derived>& A)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("det", Exception::Type::ZERO_SIZE);

	return rA.determinant();
}


/**
 * @brief Logarithm of the determinant
 *
 * Especially useful when the determinant overflows/underflows\n
 *
 */
/**
 * @param A Eigen expression
 * @return Logarithm of the determinant of @a A, as a dynamic matrix
 * over the same scalar field
 *
 */
template<typename Derived>
typename Derived::Scalar logdet(const Eigen::MatrixBase<Derived>& A)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("logdet", Exception::Type::ZERO_SIZE);

	// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("logdet", Exception::Type::MATRIX_NOT_SQUARE);

	Eigen::PartialPivLU<types::DynMat<typename Derived::Scalar>> lu(rA);
	types::DynMat<typename Derived::Scalar> U =
			lu.matrixLU().template triangularView<Eigen::Upper>();
	typename Derived::Scalar result = std::log(U(0, 0));

	for (std::size_t i = 1; i < static_cast<std::size_t>(rA.rows()); i++)
		result += std::log(U(i, i));

	return result;

}

/**
 * @brief Element-wise sum
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Element-wise sum of @a A, as a dynamic matrix
 * over the same scalar field
 */
template<typename Derived>
typename Derived::Scalar sum(const Eigen::MatrixBase<Derived>& A)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("sum", Exception::Type::ZERO_SIZE);

	return rA.sum();
}

/**
 * @brief Trace norm
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Trace norm (Frobenius norm) of @a A, as a real number
 */
template<typename Derived>
double norm(const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("norm", Exception::Type::ZERO_SIZE);

// convert matrix to complex then return its norm
	return (rA.template cast<types::cplx>()).norm();
}

/**
 * @brief Eigenvalues
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Eigenvalues of @a A, as a diagonal dynamic matrix
 * over the complex field, with eigenvalues on the diagonal
 */
template<typename Derived>
types::cmat evals(const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("evals", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("evals", Exception::Type::MATRIX_NOT_SQUARE);

	Eigen::ComplexEigenSolver<types::cmat> es(rA.template cast<types::cplx>());
	return es.eigenvalues();
}

/**
 * @brief Eigenvectors
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Eigenvectors of @a A, as columns
 * of a dynamic matrix over the complex field
 */
template<typename Derived>
types::cmat evects(const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("evects", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("evects", Exception::Type::MATRIX_NOT_SQUARE);

	Eigen::ComplexEigenSolver<types::cmat> es(rA.template cast<types::cplx>());
	return es.eigenvectors();
}

/**
 * @brief Hermitian eigenvalues
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Eigenvalues of Hermitian @a A, as a diagonal dynamic matrix
 * over the real field, with eigenvalues on the diagonal
 */
template<typename Derived>
types::dmat hevals(const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("hevals", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("hevals", Exception::Type::MATRIX_NOT_SQUARE);

	Eigen::SelfAdjointEigenSolver<types::cmat> es(
			rA.template cast<types::cplx>());
	return es.eigenvalues();
}

/**
 * @brief Hermitian eigenvectors
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Eigenvectors of Hermitian @a A, as columns
 * of a dynamic matrix over the complex field
 */
template<typename Derived>
types::cmat hevects(const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("hevects", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("hevects", Exception::Type::MATRIX_NOT_SQUARE);

	Eigen::SelfAdjointEigenSolver<types::cmat> es(
			rA.template cast<types::cplx>());
	return es.eigenvectors();
}

// Matrix functional calculus
/**
 * @brief Functional calculus f(A)
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @param f Pointer-to-function from complex to complex
 * @return @a f(A), as a dynamic matrix over the complex field
 */
template<typename Derived>
types::cmat funm(const Eigen::MatrixBase<Derived> &A,
		types::cplx (*f)(const types::cplx &))
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("funm", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("funm", Exception::Type::MATRIX_NOT_SQUARE);

	Eigen::ComplexEigenSolver<types::cmat> es(rA.template cast<types::cplx>());
	types::cmat evects = es.eigenvectors();
	types::cmat evals = es.eigenvalues();
	for (std::size_t i = 0; i < static_cast<std::size_t>(evals.rows()); i++)
		evals(i) = (*f)(evals(i)); // apply f(x) to each eigenvalue

	types::cmat evalsdiag = evals.asDiagonal();

	return evects * evalsdiag * evects.inverse();
}

/**
 * @brief Matrix square root
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Matrix square root of @a A, as a dynamic matrix
 * over the complex field
 */
template<typename Derived>
types::cmat sqrtm(const Eigen::MatrixBase<Derived> &A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("sqrtm", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("sqrtm", Exception::Type::MATRIX_NOT_SQUARE);

	return funm(rA, &std::sqrt);
}

/**
 * @brief Matrix absolut value
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Matrix absolut value of @a A, as a dynamic matrix
 * over the complex field
 */
template<typename Derived>
types::cmat absm(const Eigen::MatrixBase<Derived> &A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("absm", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("absm", Exception::Type::MATRIX_NOT_SQUARE);

	return sqrtm(adjoint(rA) * rA);
}

/**
 * @brief Matrix exponential
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Matrix exponential of @a A, as a dynamic matrix
 * over the complex field
 */
template<typename Derived>
types::cmat expm(const Eigen::MatrixBase<Derived> &A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("expm", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("expm", Exception::Type::MATRIX_NOT_SQUARE);

	return funm(rA, &std::exp);
}

/**
 * @brief Matrix logarithm
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Matrix logarithm of @a A, as a dynamic matrix over the complex field
 */
template<typename Derived>
types::cmat logm(const Eigen::MatrixBase<Derived> &A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("logm", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("logm", Exception::Type::MATRIX_NOT_SQUARE);

	return funm(rA, &std::log);
}

/**
 * @brief Matrix sin
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Matrix sine of @a A, as a dynamic matrix over the complex field
 */
template<typename Derived>
types::cmat sinm(const Eigen::MatrixBase<Derived> &A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("sinm", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("sinm", Exception::Type::MATRIX_NOT_SQUARE);

	return funm(rA, &std::sin);
}

/**
 * @brief Matrix cos
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @return Matrix cosine of @a A, as a dynamic matrix over the complex field
 */
template<typename Derived>
types::cmat cosm(const Eigen::MatrixBase<Derived> &A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("cosm", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("cosm", Exception::Type::MATRIX_NOT_SQUARE);

	return funm(rA, &std::cos);
}

/**
 * @brief Matrix power
 *
 * By convention \f$A^0 = I\f$\n
 * Uses the spectral decomposition of @a A to compute the matrix power
 */
/**
 *
 * @param A Eigen expression
 * @param z Complex number
 * @return Matrix power \f$A^z\f$, as a dynamic matrix over the complex field
 */
template<typename Derived>
types::cmat spectralpowm(const Eigen::MatrixBase<Derived> &A,
		const types::cplx z)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("spectralpowm", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("spectralpowm", Exception::Type::MATRIX_NOT_SQUARE);

// Define A^0 = Id, for z IDENTICALLY zero
	if (real(z) == 0 && imag(z) == 0)
	{
		types::cmat result(rA.rows(), rA.rows());
		return result.setIdentity();;
	}

	Eigen::ComplexEigenSolver<types::cmat> es(rA.template cast<types::cplx>());
	types::cmat evects = es.eigenvectors();
	types::cmat evals = es.eigenvalues();
	for (std::size_t i = 0; i < static_cast<std::size_t>(evals.rows()); i++)
		evals(i) = std::pow(static_cast<types::cplx>(evals(i)),
				static_cast<types::cplx>(z));

	types::cmat evalsdiag = evals.asDiagonal();

	return evects * evalsdiag * evects.inverse();

}

/**
 * @brief Matrix power
 *
 * By convention \f$A^0 = I\f$\n
 * Explicitly multiplies the matrix @a A with itself @a n times
 */
/**
 *
 * @param A Eigen expression
 * @param n Non-negative integer
 * @return Matrix power \f$A^n\f$, as a dynamic matrix
 * over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> powm(
		const Eigen::MatrixBase<Derived> &A, std::size_t n)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("powm", Exception::Type::ZERO_SIZE);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("powm", Exception::Type::MATRIX_NOT_SQUARE);

	types::DynMat<typename Derived::Scalar> result = rA;

	if (n == 0)
		return result.setIdentity();

	for (std::size_t i = 1; i < n; i++)
		result *= rA;

	return result;
}

// other functions


/**
 * @brief Functor
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @param f Pointer-to-function from scalars of @a A to @a OutputScalar
 * @return Component-wise \f$f(A)\f$, as a dynamic matrix
 * over the @a OutputScalar scalar field
 */
template<typename OutputScalar, typename Derived>
types::DynMat<OutputScalar> cwise(const Eigen::MatrixBase<Derived> &A,
		OutputScalar (*f)(const typename Derived::Scalar &))
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("cwise", Exception::Type::ZERO_SIZE);

	types::DynMat<OutputScalar> result(rA.rows(), rA.cols());

	for (std::size_t j = 0; j < static_cast<std::size_t>(rA.cols()); j++)
#pragma omp parallel for
		for (std::size_t i = 0; i < static_cast<std::size_t>(rA.rows()); i++)
			result(i, j) = (*f)(rA(i, j));

	return result;
}

// Kronecker product of multiple matrices, preserve return type
// variadic template
/**
 * @brief Kronecker product (variadic overload)
 *
 * Used to stop the recursion for the variadic template version of
 * @a qpp::kron(...)
 */
/**
 *
 * @param head Eigen expression
 * @return Its argument @a head
 */
template<typename T>
types::DynMat<typename T::Scalar> kron(const T& head)
{
	return head;
}

/**
 * @brief Kronecker product (variadic overload)
 *
 *
 */
/**
 *
 * @param head Eigen expression
 * @param tail Variadic Eigen expression (zero or more parameters)
 * @return Kronecker product of all input parameters,
 * evaluated from left to right, as a dynamic matrix over the same scalar field
 */
template<typename T, typename ... Args>
types::DynMat<typename T::Scalar> kron(const T& head, const Args&... tail)
{
	return internal::_kron2(head, kron(tail...));
}

/**
 * @brief Kronecker product (std::vector overload)
 *
 *
 */
/**
 *
 * @param As std::vector of Eigen expressions
 * @return Kronecker product of all elements in @a As,
 * evaluated from left to right, as a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> kron(const std::vector<Derived> &As)

{
	if (As.size() == 0)
		throw Exception("kron", Exception::Type::ZERO_SIZE);

	for (auto it : As)
		if (it.size() == 0)
			throw Exception("kron", Exception::Type::ZERO_SIZE);

	types::DynMat<typename Derived::Scalar> result = As[0];
	for (std::size_t i = 1; i < As.size(); i++)
	{
		result = kron(result, As[i]);
	}
	return result;
}

// Kronecker product of a list of matrices, preserve return type
// deduce the template parameters from initializer_list
/**
 * @brief Kronecker product (std::initializer_list overload)
 *
 *
 */
/**
 *
 * @param As std::initializer_list of Eigen expressions,
 * such as @a {A1, A2, ... ,Ak}
 * @return Kronecker product of all elements in @a As,
 * evaluated from left to right, as a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> kron(
		const std::initializer_list<Derived> &As)
{
	return kron(std::vector<Derived>(As));
}

/**
 * @brief Kronecker power
 *
 *
 */
/**
 *
 * @param A Eigen expression
 * @param n Non-negative integer
 * @return Kronecker product of @a A with itself @a n times \f$A^{\otimes n}\f$,
 * as a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> kronpow(
		const Eigen::MatrixBase<Derived>& A, std::size_t n)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("kronpow", Exception::Type::ZERO_SIZE);

// check out of range
	if (n == 0)
		throw Exception("kronpow", Exception::Type::OUT_OF_RANGE);

	types::DynMat<typename Derived::Scalar> result = rA;
	for (std::size_t i = 1; i < n; i++)
		result = kron(result, rA);
	return result;
}

/**
 * @brief Reshape
 *
 *  Uses column-major order when reshaping (same as MATLAB)
 */
/**
 *
 * @param A Eigen expression
 * @param rows Number of rows of the reshaped matrix
 * @param cols Number of columns of the reshaped matrix
 * @return Reshaped matrix with @a rows rows and @a cols columns,
 * as a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> reshape(
		const Eigen::MatrixBase<Derived>& A, std::size_t rows, std::size_t cols)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	std::size_t Arows = static_cast<std::size_t>(rA.rows());
	std::size_t Acols = static_cast<std::size_t>(rA.cols());

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("reshape", Exception::Type::ZERO_SIZE);

	if (Arows * Acols != rows * cols)
		throw Exception("reshape", Exception::Type::DIMS_MISMATCH_MATRIX);

	return Eigen::Map<types::DynMat<typename Derived::Scalar>>(
			const_cast<typename Derived::Scalar*>(rA.data()), rows, cols);
}

/**
 * @brief System permutation
 *
 * Permutes the subsystems in a state vector or density matrix\n
 * The qubit @a perm[@a i] is permuted to the location @a i
 */
/**
 *
 * @param A Eigen expression
 * @param perm Permutation
 * @param dims Subsystems' dimensions
 * @return Permuted system, as a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> syspermute(
		const Eigen::MatrixBase<Derived>& A,
		const std::vector<std::size_t>& perm,
		const std::vector<std::size_t>& dims)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// Error checks

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("syspermute", Exception::Type::ZERO_SIZE);

	// check that dims is a valid dimension vector
	if (!internal::_check_dims(dims))
		throw Exception("syspermute", Exception::Type::DIMS_INVALID);

	// check that we have a valid permutation
	if (!internal::_check_perm(perm))
		throw Exception("syspermute", Exception::Type::PERM_INVALID);

	// check permutation size
	if (perm.size() != dims.size())
		throw Exception("syspermute", Exception::Type::PERM_INVALID);

	std::size_t D = static_cast<std::size_t>(rA.rows());
	std::size_t numdims = dims.size();

	types::DynMat<typename Derived::Scalar> result;

	auto worker =
			[](std::size_t i, std::size_t numdims, const std::size_t* cdims,
					const std::size_t* cperm)
			{
				// use static allocation for speed,
				// double the size for matrices reshaped as vectors
				std::size_t midx[2 * ct::maxn];
				std::size_t midxtmp[2 * ct::maxn];
				std::size_t permdims[2 * ct::maxn];

				/* compute the multi-index */
				internal::_n2multiidx(i, numdims, cdims, midx);

				for (std::size_t k = 0; k < numdims; k++)
				{
					permdims[k] = cdims[cperm[k]]; // permuted dimensions
					midxtmp[k] = midx[cperm[k]];// permuted multi-indexes
				}
				return internal::_multiidx2n(midxtmp, numdims, permdims);
			};

// check column vector
	if (internal::_check_col_vector(rA)) // we have a column vector
	{
		std::size_t cdims[ct::maxn];
		std::size_t cperm[ct::maxn];

		// check that dims match the dimension of rA
		if (!internal::_check_dims_match_cvect(dims, rA))
			throw Exception("syspermute",
					Exception::Type::DIMS_MISMATCH_CVECTOR);

		// copy dims in cdims and perm in cperm
		for (std::size_t i = 0; i < numdims; i++)
		{
			cdims[i] = dims[i];
			cperm[i] = perm[i];
		}
		result.resize(D, 1);

#pragma omp parallel for
		for (std::size_t i = 0; i < D; i++)
			result(worker(i, numdims, cdims, cperm)) = rA(i);

		return result;
	}

	else if (internal::_check_square_mat(rA)) // we have a square matrix
	{
		std::size_t cdims[2 * ct::maxn];
		std::size_t cperm[2 * ct::maxn];

		// check that dims match the dimension of rA
		if (!internal::_check_dims_match_mat(dims, rA))
			throw Exception("syspermute",
					Exception::Type::DIMS_MISMATCH_MATRIX);

		// copy dims in cdims and perm in cperm
		for (std::size_t i = 0; i < numdims; i++)
		{
			cdims[i] = dims[i];
			cdims[i + numdims] = dims[i];
			cperm[i] = perm[i];
			cperm[i + numdims] = perm[i] + numdims;
		}
		result.resize(D * D, 1);
		// map A to a column vector
		types::DynMat<typename Derived::Scalar> vectA = Eigen::Map<
				types::DynMat<typename Derived::Scalar>>(
				const_cast<typename Derived::Scalar*>(rA.data()), D * D, 1);

#pragma omp parallel for
		for (std::size_t i = 0; i < D * D; i++)
			result(worker(i, 2 * numdims, cdims, cperm)) = rA(i);

		return reshape(result, D, D);
	}

	else
		throw Exception("syspermute",
				Exception::Type::MATRIX_NOT_SQUARE_OR_CVECTOR);
}

/**
 * @brief Partial trace
 *
 *  Partial trace of density matrix
 *  over the first subsystem in a bi-partite system
 */
/**
 *
 * @param A Eigen expression
 * @param dims Dimensions of bi-partite system
 * (must be a std::vector with 2 elements)
 * @return Partial trace \f$Tr_{A}(\cdot)\f$ over the first subsytem \f$A\f$
 * in a bi-partite system \f$A\otimes B\f$, as a dynamic matrix
 * over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> ptrace1(
		const Eigen::MatrixBase<Derived>& A,
		const std::vector<std::size_t>& dims)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// Error checks

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("ptrace1", Exception::Type::ZERO_SIZE);

// check that dims is a valid dimension vector
	if (!internal::_check_dims(dims))
		throw Exception("ptrace1", Exception::Type::DIMS_INVALID);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("ptrace1", Exception::Type::MATRIX_NOT_SQUARE);

// check dims has only 2 elements
	if (dims.size() != 2)
		throw Exception("ptrace1", Exception::Type::NOT_BIPARTITE);

// check that dims match the dimension of A
	if (!internal::_check_dims_match_mat(dims, rA))
		throw Exception("ptrace1", Exception::Type::DIMS_MISMATCH_MATRIX);

	std::size_t DA = dims[0];
	std::size_t DB = dims[1];

	types::DynMat<typename Derived::Scalar> result = types::DynMat<
			typename Derived::Scalar>::Zero(DB, DB);

	auto worker = [&](std::size_t i, std::size_t j)
	{
		typename Derived::Scalar sum = 0;
		for (std::size_t m = 0; m < DA; m++)
		sum += rA(m * DB + i, m * DB + j);
		return sum;
	};

	for (std::size_t j = 0; j < DB; j++) // column major order for speed
#pragma omp parallel for
		for (std::size_t i = 0; i < DB; i++)
			result(i, j) = worker(i, j);

	return result;
}

/**
 * @brief Partial trace
 *
 *  Partial trace of density matrix
 *  over the second subsystem in a bi-partite system
 */
/**
 *
 * @param A Eigen expression
 * @param dims Dimensions of bi-partite system
 * (must be a std::vector with 2 elements)
 * @return Partial trace \f$Tr_{B}(\cdot)\f$ over the second subsytem \f$B\f$
 * in a bi-partite system \f$A\otimes B\f$, as a dynamic matrix
 * over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> ptrace2(
		const Eigen::MatrixBase<Derived>& A,
		const std::vector<std::size_t>& dims)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// Error checks

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("ptrace2", Exception::Type::ZERO_SIZE);

// check that dims is a valid dimension vector
	if (!internal::_check_dims(dims))
		throw Exception("ptrace2", Exception::Type::DIMS_INVALID);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("ptrace2", Exception::Type::MATRIX_NOT_SQUARE);

// check dims has only 2 elements
	if (dims.size() != 2)
		throw Exception("ptrace2", Exception::Type::NOT_BIPARTITE);

// check that dims match the dimension of A
	if (!internal::_check_dims_match_mat(dims, rA))
		throw Exception("ptrace2", Exception::Type::DIMS_MISMATCH_MATRIX);

	std::size_t DA = dims[0];
	std::size_t DB = dims[1];

	types::DynMat<typename Derived::Scalar> result = types::DynMat<
			typename Derived::Scalar>::Zero(DA, DA);

	for (std::size_t j = 0; j < DA; j++) // column major order for speed
#pragma omp parallel for
		for (std::size_t i = 0; i < DA; i++)
			result(i, j) = trace(rA.block(i * DB, j * DB, DB, DB));

	return result;
}

/**
 * @brief Partial trace
 *
 *  Partial trace of the multi-partite density matrix
 *  over a list of subsystems
 */
/**
 *
 * @param A Eigen expression
 * @param subsys Subsystems' indexes
 * @param dims Dimensions of the multi-partite system
 * @return Partial trace \f$Tr_{subsys}(\cdot)\f$ over the subsytems @a subsys
 * in a multi-partite system, as a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> ptrace(
		const Eigen::MatrixBase<Derived>& A,
		const std::vector<std::size_t>& subsys,
		const std::vector<std::size_t>& dims)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// error checks

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("ptrace", Exception::Type::ZERO_SIZE);

// check that dims is a valid dimension vector
	if (!internal::_check_dims(dims))
		throw Exception("ptrace", Exception::Type::DIMS_INVALID);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("ptrace", Exception::Type::MATRIX_NOT_SQUARE);

// check that dims match the dimension of A
	if (!internal::_check_dims_match_mat(dims, rA))
		throw Exception("ptrace", Exception::Type::DIMS_MISMATCH_MATRIX);

	if (subsys.size() == dims.size())
	{
		types::DynMat<typename Derived::Scalar> result = types::DynMat<
				typename Derived::Scalar>(1, 1);
		result(0, 0) = rA.trace();
		return result;
	}
	if (subsys.size() == 0)
		return rA;
	// check that subsys are valid
	if (!internal::_check_subsys_match_dims(subsys, dims))
		throw Exception("ptrace", Exception::Type::SUBSYS_MISMATCH_DIMS);

	std::size_t D = static_cast<std::size_t>(rA.rows());
	std::size_t n = dims.size();
	std::size_t nsubsys = subsys.size();
	std::size_t nsubsysbar = n - nsubsys;
	std::size_t dimsubsys = 1;
	for (std::size_t i = 0; i < nsubsys; i++)
		dimsubsys *= dims[subsys[i]];
	std::size_t dimsubsysbar = D / dimsubsys;

	std::size_t Cdims[ct::maxn];
	std::size_t Csubsys[ct::maxn];
	std::size_t Cdimssubsys[ct::maxn];
	std::size_t Csubsysbar[ct::maxn];
	std::size_t Cdimssubsysbar[ct::maxn];

	for (std::size_t i = 0; i < n; i++)
		Cdims[i] = dims[i];
	for (std::size_t i = 0; i < nsubsys; i++)
	{
		Csubsys[i] = subsys[i];
		Cdimssubsys[i] = dims[subsys[i]];
	}
	// construct the complement of subsys
	std::size_t cnt = 0;
	for (std::size_t i = 0; i < n; i++)
	{
		bool found = false;
		for (std::size_t m = 0; m < nsubsys; m++)
			if (subsys[m] == i)
			{
				found = true;
				break;
			}
		if (!found)
		{
			Csubsysbar[cnt] = i;
			Cdimssubsysbar[cnt] = dims[i];
			cnt++;
		}
	}

	types::DynMat<typename Derived::Scalar> result = types::DynMat<
			typename Derived::Scalar>(dimsubsysbar, dimsubsysbar);

	auto worker = [&](std::size_t i, std::size_t j)
	{
		// use static allocation for speed!

			std::size_t Cmidxrow[ct::maxn];
			std::size_t Cmidxcol[ct::maxn];
			std::size_t Cmidxrowsubsysbar[ct::maxn];
			std::size_t Cmidxcolsubsysbar[ct::maxn];
			std::size_t Cmidxsubsys[ct::maxn];

			/* get the row/col multi-indexes of the complement */
			internal::_n2multiidx(i, nsubsysbar, Cdimssubsysbar, Cmidxrowsubsysbar);
			internal::_n2multiidx(j, nsubsysbar, Cdimssubsysbar, Cmidxcolsubsysbar);
			/* write them in the global row/col multi-indexes */
			for(std::size_t k=0;k<nsubsysbar;k++)
			{
				Cmidxrow[Csubsysbar[k]]=Cmidxrowsubsysbar[k];
				Cmidxcol[Csubsysbar[k]]=Cmidxcolsubsysbar[k];
			}
			typename Derived::Scalar sm = 0;
			for(std::size_t a=0; a<dimsubsys; a++)
			{
				// get the multi-index over which we do the summation
				internal::_n2multiidx(a, nsubsys, Cdimssubsys, Cmidxsubsys);
				// write it into the global row/col multi-indexes
				for(std::size_t k=0;k<nsubsys;k++)
				Cmidxrow[Csubsys[k]]=Cmidxcol[Csubsys[k]]=Cmidxsubsys[k];

				// now do the sum
				sm+= rA(internal::_multiidx2n(Cmidxrow,n,Cdims),
						internal::_multiidx2n(Cmidxcol,n,Cdims));
			}

			return sm;
		};

	for (std::size_t i = 0; i < dimsubsysbar; i++)
#pragma omp parallel for
		for (std::size_t j = 0; j < dimsubsysbar; j++)
			result(i, j) = worker(i, j);

	return result;
}

/**
 * @brief Partial transpose
 *
 *  Partial transpose of the multi-partite density matrix
 *  over a list of subsystems
 */
/**
 *
 * @param A Eigen expression
 * @param subsys Subsystems' indexes
 * @param dims Dimensions of the multi-partite system
 * @return Partial transpose \f$(\cdot)^{T_{subsys}}\f$
 * over the subsytems @a subsys in a multi-partite system, as a dynamic matrix
 * over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> ptranspose(
		const Eigen::MatrixBase<Derived>& A,
		const std::vector<std::size_t>& subsys,
		const std::vector<std::size_t>& dims)

{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// error checks

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("ptranspose", Exception::Type::ZERO_SIZE);

// check that dims is a valid dimension vector
	if (!internal::_check_dims(dims))
		throw Exception("ptranspose", Exception::Type::DIMS_INVALID);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("ptranspose", Exception::Type::MATRIX_NOT_SQUARE);

// check that dims match the dimension of A
	if (!internal::_check_dims_match_mat(dims, rA))
		throw Exception("ptranspose", Exception::Type::DIMS_MISMATCH_MATRIX);

	if (subsys.size() == dims.size())
		return rA.transpose();
	if (subsys.size() == 0)
		return rA;
// check that subsys are valid
	if (!internal::_check_subsys_match_dims(subsys, dims))
		throw Exception("ptranspose", Exception::Type::SUBSYS_MISMATCH_DIMS);

	std::size_t D = static_cast<std::size_t>(rA.rows());
	std::size_t numdims = dims.size();
	std::size_t numsubsys = subsys.size();
	std::size_t cdims[ct::maxn];
	std::size_t midxcol[ct::maxn];
	std::size_t csubsys[ct::maxn];

// copy dims in cdims and subsys in csubsys
	for (std::size_t i = 0; i < numdims; i++)
		cdims[i] = dims[i];
	for (std::size_t i = 0; i < numsubsys; i++)
		csubsys[i] = subsys[i];

	types::DynMat<typename Derived::Scalar> result(D, D);

	auto worker = [&](std::size_t i, std::size_t j)
	{
		// use static allocation for speed!
			std::size_t midxcoltmp[ct::maxn];
			std::size_t midxrow[ct::maxn];

			for (std::size_t k = 0; k < numdims; k++)
			midxcoltmp[k] = midxcol[k];

			/* compute the row multi-index */
			internal::_n2multiidx(i, numdims, cdims, midxrow);

			for (std::size_t k = 0; k < numsubsys; k++)
			std::swap(midxcoltmp[csubsys[k]], midxrow[csubsys[k]]);

			/* writes the result */
			result(i, j)=rA(internal::_multiidx2n(midxrow, numdims, cdims),
					internal::_multiidx2n(midxcoltmp, numdims, cdims));

		};

	for (std::size_t j = 0; j < D; j++)
	{
		// compute the column multi-index
		internal::_n2multiidx(j, numdims, cdims, midxcol);
#pragma omp parallel for
		for (std::size_t i = 0; i < D; i++)
			worker(i, j);
	}

	return result;
}

/**
 * @brief Commutator
 *
 *  Commutator \f$ [A,B] = AB - BA \f$\n
 *  Both @a A and @a B must be Eigen expressions over the same scalar field
 */
/**
 *
 * @param A Eigen expression
 * @param B Eigen expression
 * @return Commutator \f$AB -BA\f$, as a dynamic matrix
 * over the same scalar field
 */
template<typename Derived1, typename Derived2>
types::DynMat<typename Derived1::Scalar> comm(
		const Eigen::MatrixBase<Derived1> &A,
		const Eigen::MatrixBase<Derived2> &B)
{
	const types::DynMat<typename Derived1::Scalar> & rA = A;
	const types::DynMat<typename Derived2::Scalar> & rB = B;

// EXCEPTION CHECKS

	// check types
	if (!std::is_same<typename Derived1::Scalar, typename Derived2::Scalar>::value)
		throw Exception("comm", Exception::Type::TYPE_MISMATCH);

// check zero-size
	if (!internal::_check_nonzero_size(rA)
			|| !internal::_check_nonzero_size(rB))
		throw Exception("comm", Exception::Type::ZERO_SIZE);

// check square matrices
	if (!internal::_check_square_mat(rA) || !internal::_check_square_mat(rB))
		throw Exception("comm", Exception::Type::MATRIX_NOT_SQUARE);

// check equal dimensions
	if (rA.rows() != rB.rows())
		throw Exception("comm", Exception::Type::DIMS_NOT_EQUAL);

	return rA * rB - rB * rA;
}

/**
 * @brief Anti-commutator
 *
 *  Anti-commutator \f$ \{A,B\} = AB + BA \f$\n
 *  Both @a A and @a B must be Eigen expressions over the same scalar field
 */
/**
 *
 * @param A Eigen expression
 * @param B Eigen expression
 * @return Anti-commutator \f$AB +BA\f$, as a dynamic matrix
 * over the same scalar field
 */
template<typename Derived1, typename Derived2>
types::DynMat<typename Derived1::Scalar> anticomm(
		const Eigen::MatrixBase<Derived1> &A,
		const Eigen::MatrixBase<Derived2> &B)
{
	const types::DynMat<typename Derived1::Scalar>& rA = A;
	const types::DynMat<typename Derived2::Scalar>& rB = B;

// EXCEPTION CHECKS

	// check types
	if (!std::is_same<typename Derived1::Scalar, typename Derived2::Scalar>::value)
		throw Exception("anticomm", Exception::Type::TYPE_MISMATCH);

// check zero-size
	if (!internal::_check_nonzero_size(rA)
			|| !internal::_check_nonzero_size(rB))
		throw Exception("anticomm", Exception::Type::ZERO_SIZE);

// check square matrices
	if (!internal::_check_square_mat(rA) || !internal::_check_square_mat(rB))
		throw Exception("anticomm", Exception::Type::MATRIX_NOT_SQUARE);

// check equal dimensions
	if (rA.rows() != rB.rows())
		throw Exception("anticomm", Exception::Type::DIMS_NOT_EQUAL);

	return rA * rB + rB * rA;
}

/**
 * @brief Projector
 *
 *  Normalized projector onto state vector
 */
/**
 *
 * @param V Eigen expression
 * @return Projector onto the state vector @a V, or the matrix @a Zero
 * if @a V has norm zero (i.e. smaller than @a qpp::ct::eps),
 * as a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> prj(const Eigen::MatrixBase<Derived>& V)
{
	const types::DynMat<typename Derived::Scalar> & rV = V;

// check zero-size
	if (!internal::_check_nonzero_size(rV))
		throw Exception("prj", Exception::Type::ZERO_SIZE);

// check column vector
	if (!internal::_check_col_vector(rV))
		throw Exception("prj", Exception::Type::MATRIX_NOT_CVECTOR);

	double normV = norm(rV);
	if (normV > ct::eps)
		return rV * adjoint(rV) / (normV * normV);
	else
		return types::DynMat<typename Derived::Scalar>::Zero(rV.rows(),
				rV.rows());

}

/**
 * @brief Expand out
 *
 *  Expand out @a A as a matrix in a multi-partite system\n
 *  Faster than using @a qpp::kron(I, I, ..., I, A, I, ..., I)
 */
/**
 *
 * @param A Eigen expression
 * @param pos Position
 * @param dims Dimensions of the multi-partite system
 * @return Tensor product
 * \f$ I\otimes\cdots\otimes I\otimes A \otimes I \otimes\cdots\otimes I\f$,
 * with @a A on position @a pos, as a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> expandout(
		const Eigen::MatrixBase<Derived>& A, std::size_t pos,
		const std::vector<std::size_t>& dims)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("expandout", Exception::Type::ZERO_SIZE);

// check that dims is a valid dimension vector
	if (!internal::_check_dims(dims))
		throw Exception("expandout", Exception::Type::DIMS_INVALID);

// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("expandout", Exception::Type::MATRIX_NOT_SQUARE);

// check that position is valid
	if (pos > dims.size() - 1)
		throw Exception("expandout", Exception::Type::OUT_OF_RANGE);

// check that dims[pos] match the dimension of A
	if (static_cast<std::size_t>(rA.cols()) != dims[pos])
		throw Exception("expandout", Exception::Type::DIMS_MISMATCH_MATRIX);

	auto multiply = [](std::size_t x, std::size_t y)->std::size_t
	{	return x*y;};

	std::size_t D = std::accumulate(std::begin(dims), std::end(dims), 1u,
			multiply);
	types::DynMat<typename Derived::Scalar> result = types::DynMat<
			typename Derived::Scalar>::Identity(D, D);

	std::size_t Cdims[ct::maxn];
	std::size_t midx_row[ct::maxn];
	std::size_t midx_col[ct::maxn];

	for (std::size_t k = 0; k < dims.size(); k++)
	{
		midx_row[k] = midx_col[k] = 0;
		Cdims[k] = dims[k];
	}

// run over the main diagonal multi-indexes
	for (std::size_t i = 0; i < D; i++)
	{
		// get row multi_index
		internal::_n2multiidx(i, dims.size(), Cdims, midx_row);
		// get column multi_index (same as row)
		internal::_n2multiidx(i, dims.size(), Cdims, midx_col);
		// run over the gate's row multi-index
		for (std::size_t a = 0; a < static_cast<std::size_t>(rA.cols()); a++)
		{
			// construct the total row multi-index
			midx_row[pos] = a;

			// run over the gate's column multi-index
			for (std::size_t b = 0; b < static_cast<std::size_t>(rA.cols());
					b++)
			{
				// construct the total column multi-index
				midx_col[pos] = b;

				// finally write the values
				result(internal::_multiidx2n(midx_row, dims.size(), Cdims),
						internal::_multiidx2n(midx_col, dims.size(), Cdims)) =
						rA(a, b);
			}
		}
	}

	return result;
}

/**
 * @brief Gram-Schmidt orthogonalization (std::vector overload)
 *
 */
/**
 *
 * @param Vs std::vector of Eigen expressions as column vectors
 * @return Gram-Schmidt vectors of @a Vs as columns of a dynamic matrix
 * over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> grams(const std::vector<Derived>& Vs)
{
	// check empty list
	if (!internal::_check_nonzero_size(Vs))
		throw Exception("grams", Exception::Type::ZERO_SIZE);

	for (auto it : Vs)
		if (!internal::_check_nonzero_size(it))
			throw Exception("grams", Exception::Type::ZERO_SIZE);

	// check that Vs[0] is a column vector
	if (!internal::_check_col_vector(Vs[0]))
		throw Exception("grams", Exception::Type::MATRIX_NOT_CVECTOR);

	// now check that all the rest match the size of the first vector
	for (auto it : Vs)
		if (it.rows() != Vs[0].rows() || it.cols() != 1)
			throw Exception("grams", Exception::Type::DIMS_NOT_EQUAL);

	types::DynMat<typename Derived::Scalar> cut = types::DynMat<
			typename Derived::Scalar>::Identity(Vs[0].rows(), Vs[0].rows());

	types::DynMat<typename Derived::Scalar> vi = types::DynMat<
			typename Derived::Scalar>::Zero(Vs[0].rows(), 1);

	std::vector<types::DynMat<typename Derived::Scalar>> outvecs;
	// find the first non-zero vector in the list
	std::size_t pos = 0;
	for (pos = 0; pos < Vs.size(); pos++)
	{
		if (norm(Vs[pos]) > ct::eps) // add it as the first element
		{
			outvecs.push_back(Vs[pos]);
			break;
		}
	}

	// start the process
	for (std::size_t i = pos + 1; i < Vs.size(); i++)
	{
		cut -= prj(outvecs[i - 1 - pos]);
		vi = cut * Vs[i];
		outvecs.push_back(vi);
	}

	types::DynMat<typename Derived::Scalar> result(Vs[0].rows(),
			outvecs.size());

	std::size_t cnt = 0;
	for (auto it : outvecs)
	{
		double normV = norm(it);
		if (normV > ct::eps) // we add only the non-zero vectors
		{
			result.col(cnt) = it / normV;
			cnt++;
		}
	}
	return result.block(0, 0, Vs[0].rows(), cnt);
}

// deduce the template parameters from initializer_list
/**
 * @brief Gram-Schmidt orthogonalization (std::initializer_list overload)
 *
 */
/**
 *
 * @param Vs std::initializer_list of Eigen expressions as column vectors
 * @return Gram-Schmidt vectors of @a Vs as columns of a dynamic matrix
 * over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> grams(
		const std::initializer_list<Derived>& Vs)
{
	return grams(std::vector<Derived>(Vs));
}

/**
 * @brief Gram-Schmidt orthogonalization (Eigen expression (matrix) overload)
 *
 */
/**
 *
 * @param A Eigen expression, the input vectors are the columns of @a A
 * @return Gram-Schmidt vectors of the columns of @a A,
 * as columns of a dynamic matrix over the same scalar field
 */
template<typename Derived>
types::DynMat<typename Derived::Scalar> grams(
		const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	if (!internal::_check_nonzero_size(rA))
		throw Exception("grams", Exception::Type::ZERO_SIZE);

	std::vector<types::DynMat<typename Derived::Scalar>> input;

	for (std::size_t i = 0; i < static_cast<std::size_t>(rA.cols()); i++)
		input.push_back(
				static_cast<types::DynMat<typename Derived::Scalar> >(rA.col(i)));

	return grams<types::DynMat<typename Derived::Scalar>>(input);
}

/**
 * @brief Non-negative integer index to multi-index
 *
 * Uses standard lexicographical order, i.e. 00...0, 00...1 etc.
 */
/**
 *
 * @param n Non-negative integer index
 * @param dims Dimensions of the multi-partite system
 * @return Multi-index of the same size as @a dims
 */
std::vector<std::size_t> n2multiidx(std::size_t n,
		const std::vector<std::size_t>& dims)
{
	if (!internal::_check_dims(dims))
		throw Exception("n2multiidx", Exception::Type::DIMS_INVALID);

	auto multiply = [](const std::size_t x, const std::size_t y)->std::size_t
	{	return x*y;};

	if (n >= std::accumulate(std::begin(dims), std::end(dims), 1u, multiply))
		throw Exception("n2multiidx", Exception::Type::OUT_OF_RANGE);

	std::vector<std::size_t> result(dims.size());
	std::size_t _n = n;
	for (std::size_t i = 0; i < dims.size(); i++)
	{
		result[dims.size() - i - 1] = _n
				% static_cast<int>(dims[dims.size() - i - 1]);
		_n = _n / static_cast<int>(dims[dims.size() - i - 1]);
	}

	return result;
}

/**
 * @brief Multi-index to non-negative integer index
 *
 * Uses standard lexicographical order, i.e. 00...0, 00...1 etc.
 */
/**
 *
 * @param midx Multi-index
 * @param dims Dimensions of the multi-partite system
 * @return Non-negative integer index
 */
std::size_t multiidx2n(const std::vector<std::size_t>& midx,
		const std::vector<std::size_t>& dims)
{
	if (!internal::_check_dims(dims))
		throw Exception("multiidx2n", Exception::Type::DIMS_INVALID);

	for (std::size_t i = 0; i < dims.size(); i++)
		if (midx[i] >= dims[i])
			throw Exception("multiidx2n", Exception::Type::OUT_OF_RANGE);

	std::vector<std::size_t> part_prod(dims.size());

	part_prod[dims.size() - 1] = 1;
	for (std::size_t j = 1; j < dims.size(); j++)
		part_prod[dims.size() - j - 1] = part_prod[dims.size() - j]
				* dims[dims.size() - j];

	std::size_t result = 0;
	for (std::size_t i = 0; i < dims.size(); i++)
		result += midx[i] * part_prod[i];

	return result;
}

/**
 * @brief Multi-partite qubit ket
 *
 * Constructs the multi-partite qubit ket \f$|\mathrm{mask}\rangle\f$,
 * where @a mask is a std::vector of 0's and 1's
 */
/**
 *
 * @param mask std::vector of 0's and 1's
 * @return Multi-partite qubit state vector, as a dynamic column vector
 * over the complex field
 */
types::ket mket(const std::vector<std::size_t>& mask)
{
	std::size_t n = mask.size();
	std::size_t D = static_cast<std::size_t>(std::pow(2, n));
// check zero size
	if (n == 0)
		throw Exception("mket", Exception::Type::ZERO_SIZE);
// check mask is a valid binary vector
	for (auto it : mask)
		if (it > 1)
			throw Exception("mket", Exception::Type::NOT_QUBIT_SUBSYS);
	std::vector<std::size_t> dims(n, 2);
	types::ket result = types::ket::Zero(D);
	std::size_t pos = multiidx2n(mask, dims);
	result(pos) = 1;
	return result;
}

/**
 * @brief Multi-partite qudit ket (different dimensions overload)
 *
 * Constructs the multi-partite qudit ket \f$|\mathrm{mask}\rangle\f$,
 * where @a mask is a std::vector of non-negative integers\n
 * Each element in @a mask has to be smaller than the corresponding element
 * in @a dims
 */
/**
 *
 * @param mask std::vector of non-negative integers
 * @return Multi-partite qudit state vector, as a dynamic column vector
 * over the complex field
 */
types::ket mket(const std::vector<std::size_t>& mask,
		const std::vector<std::size_t>& dims)
{
	std::size_t n = mask.size();
	auto multiply = [](std::size_t x, std::size_t y)->std::size_t
	{	return x*y;};

	std::size_t D = std::accumulate(std::begin(dims), std::end(dims), 1u,
			multiply);

// check zero size
	if (n == 0)
		throw Exception("mket", Exception::Type::ZERO_SIZE);
// check valid dims
	if (!internal::_check_dims(dims))
		throw Exception("mket", Exception::Type::DIMS_INVALID);
// check mask and dims have the same size
	if (mask.size() != dims.size())
		throw Exception("mket", Exception::Type::SUBSYS_MISMATCH_DIMS);
// check mask is a valid vector
	for (std::size_t i = 0; i < n; i++)
		if (mask[i] >= dims[i])
			throw Exception("mket", Exception::Type::SUBSYS_MISMATCH_DIMS);

	types::ket result = types::ket::Zero(D);
	std::size_t pos = multiidx2n(mask, dims);
	result(pos) = 1;
	return result;
}

/**
 * @brief Multi-partite qudit ket (same dimensions overload)
 *
 * Constructs the multi-partite qudit ket \f$|\mathrm{mask}\rangle\f$
 * in a multi-partite system, all subsystem having equal dimension @a d\n
 * @a mask is a std::vector of non-negative integers, and
 * each element in @a mask has to be strictly smaller than @a d
 */
/**
 *
 * @param mask std::vector of non-negative integers
 * @param d Subsystems' dimension
 * @return Multi-partite qudit state vector, as a dynamic column vector
 * over the complex field
 */
types::ket mket(const std::vector<std::size_t>& mask, std::size_t d)
{
	std::size_t n = mask.size();
	std::size_t D = static_cast<std::size_t>(std::pow(d, n));

// check zero size
	if (n == 0)
		throw Exception("mket", Exception::Type::ZERO_SIZE);
// check valid dims
	if (d == 0)
		throw Exception("mket", Exception::Type::DIMS_INVALID);
// check mask is a valid vector
	for (std::size_t i = 0; i < n; i++)
		if (mask[i] >= d)
			throw Exception("mket", Exception::Type::SUBSYS_MISMATCH_DIMS);

	types::ket result = types::ket::Zero(D);
	std::vector<std::size_t> dims(n, d);
	std::size_t pos = multiidx2n(mask, dims);
	result(pos) = 1;
	return result;
}

/**
 * @brief Inverse permutation
 *
 *
 */
/**
 *
 * @param perm Permutation
 * @return Inverse of the permutation @a perm
 */
std::vector<std::size_t> invperm(const std::vector<std::size_t>& perm)
{
	if (!internal::_check_perm(perm))
		throw Exception("invperm", Exception::Type::PERM_INVALID);

	// construct the inverse
	std::vector<std::size_t> result(perm.size());
	for (std::size_t i = 0; i < perm.size(); i++)
		result[perm[i]] = i;

	return result;
}

/**
 * @brief Compose permutations
 *
 *
 */
/**
 *
 * @param perm Permutation
 * @param sigma Permutation
 * @return Composition of the permutations @a perm \f$\circ\f$ @a sigma
 *  = perm(sigma)
 */
std::vector<std::size_t> compperm(const std::vector<std::size_t>& perm,
		const std::vector<std::size_t>& sigma)
{
	if (!internal::_check_perm(perm))
		throw Exception("compperm", Exception::Type::PERM_INVALID);
	if (!internal::_check_perm(sigma))
		throw Exception("compperm", Exception::Type::PERM_INVALID);
	if (perm.size() != sigma.size())
		throw Exception("compperm", Exception::Type::PERM_INVALID);

	// construct the composition perm(sigma)
	std::vector<std::size_t> result(perm.size());
	for (std::size_t i = 0; i < perm.size(); i++)
		result[i] = perm[sigma[i]];

	return result;
}

} /* namespace qpp */

#endif /* FUNCTIONS_H_ */
