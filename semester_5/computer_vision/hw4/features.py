import numpy as np
import scipy
import scipy.linalg


class PCA(object):
    """Class implementing Principal component analysis (PCA).

    Steps to perform PCA on a matrix of features X:
        1. Fit the training data using method `fit` (either with eigen decomposition of SVD)
        2. Project X into a lower dimensional space using method `transform`
        3. Optionally reconstruct the original X (as best as possible) using method `reconstruct`
    """

    def __init__(self):
        self.W_pca = None
        self.mean = None

    def fit(self, X, method='svd'):
        """Fit the training data X using the chosen method.

        Will store the projection matrix in self.W_pca and the mean of the data in self.mean

        Args:
            X: numpy array of shape (N, D). Each of the N rows represent a data point.
               Each data point contains D features.
            method: Method to solve PCA. Must be one of 'svd' or 'eigen'.
        """
        _, D = X.shape
        self.mean = None   # empirical mean, has shape (D,)
        X_centered = None  # zero-centered data

        # 1. Compute the mean and store it in self.mean
        self.mean = np.mean(X, axis=0)
        
        # 2. Apply either method to `X_centered`      
        X_centered = X - self.mean
        
        if method == 'svd':
            self.W_pca = self._svd(X_centered)[0]
        elif method == 'eigen_decomp':
            self.W_pca = self._eigen_decomp(X_centered)[0]

        # Make sure that X_centered has mean zero
        assert np.allclose(X_centered.mean(), 0.0)

        # Make sure that self.mean is set and has the right shape
        assert self.mean is not None and self.mean.shape == (D,)

        # Make sure that self.W_pca is set and has the right shape
        assert self.W_pca is not None and self.W_pca.shape == (D, D)

        # Each column of `self.W_pca` should have norm 1 (each one is an eigenvector)
        for i in range(D):
            assert np.allclose(np.linalg.norm(self.W_pca[:, i]), 1.0)

    def _eigen_decomp(self, X):
        """Performs eigendecompostion of feature covariance matrix.

        Args:
            X: Zero-centered data array, each ROW containing a data point.
               Numpy array of shape (N, D).

        Returns:
            e_vecs: Eigenvectors of covariance matrix of X. Eigenvectors are
                    sorted in descending order of corresponding eigenvalues. Each
                    column contains an eigenvector. Numpy array of shape (D, D).
            e_vals: Eigenvalues of covariance matrix of X. Eigenvalues are
                    sorted in descending order. Numpy array of shape (D,).
        """
        N, D = X.shape
        e_vecs = None
        e_vals = None
        # Steps:
        #     1. compute the covariance matrix of X, of shape (D, D)
        X_cov = np.cov(X.T)
                
        #     2. compute the eigenvalues and eigenvectors of the covariance matrix
        e_vals, e_vecs = np.linalg.eig(X_cov)
        
        #     3. Sort both of them in decreasing order (ex: 1.0 > 0.5 > 0.0 > -0.2 > -1.2)        
        idx = np.argsort(e_vals)[::-1]
        e_vals = e_vals[idx]
        e_vecs = e_vecs[:, idx]

        # Check the output shapes
        assert e_vals.shape == (D,)
        assert e_vecs.shape == (D, D)

        return e_vecs, e_vals

    def _svd(self, X):
        """Performs Singular Value Decomposition (SVD) of X.

        Args:
            X: Zero-centered data array, each ROW containing a data point.
                Numpy array of shape (N, D).
        Returns:
            vecs: right singular vectors. Numpy array of shape (D, D)
            vals: singular values. Numpy array of shape (K,) where K = min(N, D)
        """
        vecs = None  # shape (D, D)
        N, D = X.shape
        vals = None  # shape (K,)
        
        # Here, compute the SVD of X
        # Make sure to return vecs as the matrix of vectors where each column is a singular vector
        # Perform Singular Value Decomposition
        __, vals, vecs = np.linalg.svd(X)
        vecs = vecs.T

        assert vecs.shape == (D, D)
        K = min(N, D)
        assert vals.shape == (K,)

        return vecs, vals

    def transform(self, X, n_components):
        """Center and project X onto a lower dimensional space using self.W_pca.

        Args:
            X: numpy array of shape (N, D). Each row is an example with D features.
            n_components: number of principal components..

        Returns:
            X_proj: numpy array of shape (N, n_components).
        """
        N, _ = X.shape
        X_proj = None
        
        # We need to modify X in two steps:
        #     1. first substract the mean stored during `fit`
        tmp = X - self.mean
        
        #     2. then project onto a subspace of dimension `n_components` using `self.W_pca`
        X_proj = np.dot(tmp, self.W_pca[:, :n_components])

        assert X_proj.shape == (N, n_components), "X_proj doesn't have the right shape"

        return X_proj

    def reconstruct(self, X_proj):
        """Do the exact opposite of method `transform`: try to reconstruct the original features.

        Given the X_proj of shape (N, n_components) obtained from the output of `transform`,
        we try to reconstruct the original X.

        Args:
            X_proj: numpy array of shape (N, n_components). Each row is an example with D features.

        Returns:
            X: numpy array of shape (N, D).
        """
        N, n_components = X_proj.shape
        X = None

        # Steps:
        #     1. project back onto the original space of dimension D
        
        orig = np.dot(X_proj, self.W_pca[:, :n_components].T) 
        #     2. add the mean that we substracted in `transform`
        X = orig + self.mean 

        return X


class LDA(object):
    """Class implementing Principal component analysis (PCA).

    Steps to perform PCA on a matrix of features X:
        1. Fit the training data using method `fit` (either with eigen decomposition of SVD)
        2. Project X into a lower dimensional space using method `transform`
        3. Optionally reconstruct the original X (as best as possible) using method `reconstruct`
    """

    def __init__(self):
        self.W_lda = None

    def fit(self, X, y):
        """Fit the training data `X` using the labels `y`.

        Will store the projection matrix in `self.W_lda`.

        Args:
            X: numpy array of shape (N, D). Each of the N rows represent a data point.
               Each data point contains D features.
            y: numpy array of shape (N,) containing labels of examples in X
        """
        N, D = X.shape

        scatter_between = self._between_class_scatter(X, y)
        scatter_within = self._within_class_scatter(X, y)

        e_vecs = None

        # Solve generalized eigenvalue problem for matrices `scatter_between` and `scatter_within`
        # Use `scipy.linalg.eig` instead of numpy's eigenvalue solver.
        # Don't forget to sort the values and vectors in descending order.
        
        e_vals, e_vecs = scipy.linalg.eig(scatter_between, scatter_within)
        e_vecs = e_vecs[:, np.argsort(-e_vals)]
        
        self.W_lda = e_vecs

        # Check that the shape of `self.W_lda` is correct
        assert self.W_lda.shape == (D, D)

        # Each column of `self.W_lda` should have norm 1 (each one is an eigenvector)
        for i in range(D):
            assert np.allclose(np.linalg.norm(self.W_lda[:, i]), 1.0)

    def _within_class_scatter(self, X, y):
        """Compute the covariance matrix of each class, and sum over the classes.

        For every label i, we have:
            - X_i: matrix of examples with labels i
            - S_i: covariance matrix of X_i (per class covariance matrix for class i)
        The formula for covariance matrix is: X_centered^T X_centered
            where X_centered is the matrix X with mean 0 for each feature.

        Our result `scatter_within` is the sum of all the `S_i`

        Args:
            X: numpy array of shape (N, D) containing N examples with D features each
            y: numpy array of shape (N,), labels of examples in X

        Returns:
            scatter_within: numpy array of shape (D, D), sum of covariance matrices of each label
        """
        _, D = X.shape
        assert X.shape[0] == y.shape[0]
        scatter_within = np.zeros((D, D))

        for i in np.unique(y):
            # Get the covariance matrix for class i, and add it to scatter_within
            
            X_i = X[y == i] # matrix of examples with labels i
            X_i_mean = np.mean(X_i, axis=0)
            X_centered = X_i - X_i_mean
            S_i = X_centered.T.dot(X_centered) # covariance matrix of X_i
            scatter_within += S_i
            
        return scatter_within

    def _between_class_scatter(self, X, y):
        """Compute the covariance matrix as if each class is at its mean.

        For every label i, we have:
            - X_i: matrix of examples with labels i
            - mu_i: mean of X_i.

        Args:
            X: numpy array of shape (N, D) containing N examples with D features each
            y: numpy array of shape (N,), labels of examples in X

        Returns:
            scatter_between: numpy array of shape (D, D)
        """
        _, D = X.shape
        assert X.shape[0] == y.shape[0]
        scatter_between = np.zeros((D, D))

        mu = X.mean(axis=0)
        for i in np.unique(y):
            
            X_i = X[y == i] # matrix of examples with labels i
            N_eg = X_i.shape[0]
            mu_i = np.mean(X_i, axis=0) #mean of X_i
            scatter_between += N_eg * (mu_i - mu).T.dot(mu_i - mu)

        return scatter_between

    def transform(self, X, n_components):
        """Project X onto a lower dimensional space using self.W_pca.

        Args:
            X: numpy array of shape (N, D). Each row is an example with D features.
            n_components: number of principal components..

        Returns:
            X_proj: numpy array of shape (N, n_components).
        """
        N, _ = X.shape
        X_proj = None
        
        # project onto a subspace of dimension `n_components` using `self.W_lda`
        X_proj = X.dot(self.W_lda[:, :n_components])

        assert X_proj.shape == (N, n_components), "X_proj doesn't have the right shape"

        return X_proj
