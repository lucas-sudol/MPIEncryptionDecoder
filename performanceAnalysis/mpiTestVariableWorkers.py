import subprocess
import time
import statistics
import csv

# Define constants
test_string = "abcdefghij"  # Length 10 string
num_runs = 30  # Number of times to run each test
cipher_file = "ciphertext.txt"  # Cipher text file
dictionary_file = "american-english"  # Dictionary file
output_csv = "mpi_thread_benchmark_results.csv"  # Output CSV filename

# Function to create encrypted file for the test string
def encrypt_string(input_string):
    subprocess.run(["./encrypt", input_string], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

# Function to benchmark the decryption with a specified process count
def benchmark_decrypt(process_count):
    start_time = time.perf_counter()
    result = subprocess.run(
        ["mpiexec", "-n", str(process_count), "./decrypt", cipher_file, dictionary_file],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    end_time = time.perf_counter()
    return end_time - start_time

# Main benchmarking
results = []
for process_count in range(1, 7):  # Test from 1 to 6 threads
    print(f"Running MPI tests for process count {process_count}...")
    encrypt_string(test_string)  # Create the cipher file for the test string
    runtimes = []
    for _ in range(num_runs):
        runtime = benchmark_decrypt(process_count)  # Measure runtime for decryption
        runtimes.append(runtime)
    mean_runtime = statistics.mean(runtimes)
    median_runtime = statistics.median(runtimes)
    results.append({"Process Count": process_count, "Mean": mean_runtime, "Median": median_runtime})

# Save results to CSV
with open(output_csv, mode='w', newline='') as csv_file:
    fieldnames = ["Process Count", "Mean", "Median"]
    writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerows(results)

print("MPI benchmarking complete for varying process counts. Results saved to mpi_thread_benchmark_results.csv.")
