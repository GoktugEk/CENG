import numpy as np


class HMM:
    def __init__(self, A, B, Pi):
        self.A = A
        self.B = B
        self.Pi = Pi

    def forward_log(self, O: list):
        """
        :param O: is the sequence (an array of) discrete (integer) observations, i.e. [0, 2, 1 ,3, 4]
        :return: ln P(O|λ) score for the given observation, ln: natural logarithm
        """
        # Num of hidden states
        H = self.A.shape[0]
        # Num of observations
        T = len(O)
        # Initialize the alpha matrix
        alpha = np.zeros((H, T), dtype=np.float128)
        # Initialize the scaling vector
        c = np.zeros(T)
        # Compute the initial forward probabilities
        alpha[:, 0] = self.Pi * self.B[:, O[0]]
        # Scale the alpha to avoid underflow
        c[0] = 1 / alpha[:, 0].sum()

        alpha[:, 0] = c[0] * alpha[:, 0]
        # The forward algorithm
        for t in range(1, T):
            alpha[:, t] = alpha[:, t - 1].dot(self.A) * self.B[:, O[t]]
            # Scale the alpha to avoid underflow
            c[t] = 1 / alpha[:, t].sum()

            alpha[:, t] = c[t] * alpha[:, t]

        # Compute the final probability P(O|λ) as the sum of the last column of alpha,
        # multiplied by the product of the scaling factors
        P_O_lambda = -np.log(c).sum()

        return P_O_lambda

    def viterbi_log(self, O: list):
        """
            :param O: is an array of discrete (integer) observations, i.e. [0, 2,1 ,3, 4]
            :return: the tuple (Q*, ln P(Q*|O,λ)), Q* is the most probable state sequence for the given O
            """
        # Num of hidden states
        H = self.A.shape[0]
        # Num of observations
        T = len(O)
        # Initialize the delta and psi matrices
        delta = np.zeros((H, T), dtype=np.float128)

        psi = np.zeros((H, T), dtype=np.int32)
        # Compute the initial delta values
        delta[:, 0] = self.Pi * self.B[:, O[0]]
        # The Viterbi algorithm
        for t in range(1, T):

            for j in range(H):
                delta[j, t] = np.max(delta[:, t - 1] * self.A[:, j]) * self.B[j, O[t]]

                psi[j, t] = np.argmax(delta[:, t - 1] * self.A[:, j])

        Q_star = [np.argmax(delta[:, T - 1])]

        for t in range(T - 2, -1, -1):
            Q_star.insert(0, psi[Q_star[0], t + 1])

        print(delta)
        # Compute the final probability P(Q*|O,λ) as the maximum value of the last column of delta
        P_Q_star_O_lambda = np.log(np.max(delta[:, T - 1]))
        # Return the most probable state sequence and the final probability
        # Function description says Q_star first then the ln probability
        # but as I see at the pdf, example output looks like in this format
        return P_Q_star_O_lambda, Q_star
