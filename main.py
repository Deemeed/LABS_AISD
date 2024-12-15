import pandas as pd
import matplotlib.pyplot as plt

file_path = "C:/Users/user/labsaisd/lab3/results/sorting_results.csv"
data = pd.read_csv(file_path, sep=',', engine='python')

sizes = data['Size']

plt.figure(figsize=(10, 6))
plt.plot(sizes, data['BubbleSort_Copies_Random'], label='BubbleSort (Random)', marker='o')
plt.plot(sizes, data['CombSort_Copies_Random'], label='CombSort (Random)', marker='o')
plt.plot(sizes, data['HeapSort_Copies_Random'], label='HeapSort (Random)', marker='o')
plt.title('Number of Copies for Random Arrays')
plt.xlabel('Array Size')
plt.ylabel('Number of Copies')
plt.yscale('log')
plt.legend()
plt.grid(True, which="both", linestyle='--', linewidth=0.5)
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(sizes, data['BubbleSort_Copies_Sorted'], label='BubbleSort (Sorted)', marker='o')
plt.plot(sizes, data['CombSort_Copies_Sorted'], label='CombSort (Sorted)', marker='o')
plt.plot(sizes, data['HeapSort_Copies_Sorted'], label='HeapSort (Sorted)', marker='o')
plt.title('Number of Copies for Sorted Arrays')
plt.xlabel('Array Size')
plt.ylabel('Number of Copies')
plt.yscale('log')
plt.legend()
plt.grid(True, which="both", linestyle='--', linewidth=0.5)
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(sizes, data['BubbleSort_Copies_Reverse'], label='BubbleSort (Reverse)', marker='o')
plt.plot(sizes, data['CombSort_Copies_Reverse'], label='CombSort (Reverse)', marker='o')
plt.plot(sizes, data['HeapSort_Copies_Reverse'], label='HeapSort (Reverse)', marker='o')
plt.title('Number of Copies for Reverse Sorted Arrays')
plt.xlabel('Array Size')
plt.ylabel('Number of Copies')
plt.yscale('log')
plt.legend()
plt.grid(True, which="both", linestyle='--', linewidth=0.5)
plt.show()
