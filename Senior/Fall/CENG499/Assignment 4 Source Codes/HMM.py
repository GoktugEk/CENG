import numpy as np


class HMM:
    def __init__(self, A, B, Pi):
        self.A = A
        self.B = B
        self.Pi = Pi

    def alpha(self, O: list):
        """
        Perform the forward algorithm for a hidden Markov model.

        Parameters:
            - O: a list of the observed states

        Returns:
            - a_vals: 2D array of the forward probabilities
        """
        states = len(self.A)

        a_vals = []

        vals = []
        for i in range(len(self.A)):
            vals.append(self.Pi[i] * self.B[i][O[0]])

        a_vals.append(vals)

        del vals

        for i in range(1, len(O)):
            b_vals = []
            for j in range(states):
                b_val = 0
                for k in range(states):
                    b_val += a_vals[i - 1][k] * self.A[k][j]

                b_vals.append(b_val * self.B[j][O[i]])

            a_vals.append([x for x in b_vals])

        return a_vals

    def alpha_with_max(self, O: list):
        """
        Perform the forward algorithm for a hidden Markov model with max.

        Parameters:
            - O: a list of the observed states

        Returns:
            - a_vals: 2D array of the forward probabilities
        """
        states = len(self.A)

        a_vals = []

        vals = []
        for i in range(len(self.A)):
            vals.append(self.Pi[i] * self.B[i][O[0]])

        a_vals.append(vals)

        del vals

        for i in range(1, len(O)):
            b_vals = []
            for j in range(states):
                b_val = 0
                for k in range(states):

                    if b_val < a_vals[i - 1][k] * self.A[k][j]:
                        b_val = a_vals[i - 1][k] * self.A[k][j]

                b_vals.append(b_val * self.B[j][O[i]])

            a_vals.append([x for x in b_vals])

        return a_vals

    def forward_log(self, O: list):
        """
        :param O: is the sequence (an array of) discrete (integer) observations, i.e. [0, 2,1 ,3, 4]
        :return: ln P(O|λ) score for the given observation, ln: natural logarithm
        """

        return np.log(np.sum(self.alpha(O)[-1]))

    def viterbi_log(self, O: list):
        """
        :param O: is an array of discrete (integer) observations, i.e. [0, 2,1 ,3, 4]
        :return: the tuple (Q*, ln P(Q*|O,λ)), Q* is the most probable state sequence for the given O
        """
        res = [None, None]

        a_vals = np.array(self.alpha(O), dtype=np.float32)
        a_vals_with_max = np.array(self.alpha_with_max(O), dtype=np.float32)

        res[0] = np.log(np.max(a_vals_with_max[-1, :]))  # Probability
        res[1] = [np.argmax(x) for x in a_vals]  # Sequence

        return tuple(res)
