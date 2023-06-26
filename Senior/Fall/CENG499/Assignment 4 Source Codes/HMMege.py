import numpy as np


class HMM:
    def __init__(self, A, B, Pi):
        self.A = A
        self.B = B
        self.Pi = Pi

    def calculateAlpha(self, O: list):
        num_states = self.A.shape[0]
        seq_len = len(O)
        alpha = [[0 for _ in range(num_states)] for _ in range(seq_len)]

        for i in range(seq_len):
            for j in range(num_states):
                if i == 0:
                    alpha[i][j] = self.Pi[j] * self.B[j][O[i]]

                else:
                    for x in range(num_states):
                        alpha[i][j] += alpha[i - 1][x] * self.A[x][j] * self.B[j][O[i]]

        return alpha

    def forward_log(self, O: list):
        """
        :param O: is the sequence (an array of) discrete (integer) observations, i.e. [0, 2,1 ,3, 4]
        :return: ln P(O|λ) score for the given observation, ln: natural logarithm
        """

        alpha = self.calculateAlpha(O)

        return np.log(sum(alpha[len(O) - 1]))

    def viterbi_log(self, O: list):
        """
        :param O: is an array of discrete (integer) observations, i.e. [0, 2,1 ,3, 4]
        :return: the tuple (Q*, ln P(Q*|O,λ)), Q* is the most probable state sequence for the given O
        """
        seq_len = len(O)
        alpha = self.calculateAlpha(O)
        print(alpha)
        p = np.log(max(alpha[seq_len - 1]))

        sequence = []

        for i in range(seq_len):
            sequence.append(alpha[i].index(max(alpha[i])))

        return (p, sequence)
