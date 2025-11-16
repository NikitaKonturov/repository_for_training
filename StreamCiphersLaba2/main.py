import math

def probability(cl1, cl2, cl3, v):
 
    if cl1 < 0 or cl2 < 0 or cl3 < 0 or v < max(cl1, cl2, cl3):
        return 0.0
    
    numerator = (math.comb(v, v -cl1) * 
                math.comb(cl1, v - cl2) * 
                math.comb(cl1 + cl2 - v, v - cl3))
    
    denominator = 4 ** v 
    return numerator / denominator

import numpy as np

def iterative_probability(target_cl1, target_cl2, target_cl3, max_v):
    F = np.zeros((max_v+1, max_v+1, max_v+1, max_v+1), dtype=np.float64)
    
    F[0, 0, 0, 0] = 1.0

    for v in range(1, max_v+1):
        for cl1 in range(v+1):
            for cl2 in range(v+1):
                for cl3 in range(v+1):
                    total = 0.0
                    if cl1 >= 1 and cl2 >= 1 and cl3 >= 1:
                        total += 0.25 * F[cl1-1, cl2-1, cl3-1, v-1]
                    
                    if cl2 >= 1 and cl3 >= 1 and cl1 <= v-1:
                        total += 0.25 * F[cl1, cl2-1, cl3-1, v-1]
                    
                    if cl1 >= 1 and cl3 >= 1 and cl2 <= v-1:
                        total += 0.25 * F[cl1-1, cl2, cl3-1, v-1]
                    
                    if cl1 >= 1 and cl2 >= 1 and cl3 <= v-1:
                        total += 0.25 * F[cl1-1, cl2-1, cl3, v-1]
                    
                    F[cl1, cl2, cl3, v] = total
    
    return F[target_cl1, target_cl2, target_cl3, max_v]



print("############################(Probability from equal 16)############################")
print(f"Probability P(76, 76, 76, 101): {probability(76, 76, 76, 101) * 10000}")
print(f"Probability P(79, 79, 79, 105): {probability(79, 79, 79, 105) * 10000}")
print(f"Probability P(80, 80, 80, 105): {probability(80, 80, 80, 105) * 10000}")
print(f"Probability P(79, 80, 81, 106): {probability(79, 80, 81, 106) * 10000}")
print(f"Probability P(82, 82, 82, 109): {probability(82, 82, 82, 109) * 10000}")


print("############################(Probability from equal 15)############################")
print(f"Probability P(76, 76, 76, 101): {iterative_probability(76, 76, 76, 101) * 10000}")
print(f"Probability P(79, 79, 79, 105): {iterative_probability(79, 79, 79, 105) * 10000}")
print(f"Probability P(80, 80, 80, 105): {iterative_probability(80, 80, 80, 105) * 10000}")
print(f"Probability P(79, 80, 81, 106): {iterative_probability(79, 80, 81, 106) * 10000}")
print(f"Probability P(82, 82, 82, 109): {iterative_probability(82, 82, 82, 109) * 10000}")

