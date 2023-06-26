import numpy as np

from HMM import HMM

A = np.array([[0.4, 0.6], [0.7, 0.3]], dtype=np.float128)

B = np.array([[0.3, 0.4, 0.3], [0.1, 0.2, 0.7]], dtype=np.float128)

Pi = np.array([0.6, 0.4], dtype=np.float128)

hmm = HMM(A, B, Pi)

O1 = [2, 1, 0]
O2 = [0, 0, 2, 1, 0]
print(hmm.forward_log(O1))
print(hmm.forward_log(O2))
print(hmm.viterbi_log(O1))
print(hmm.viterbi_log(O2))
