import subprocess
import time
import csv

# Define constants with unique-letter strings up to length 10
words_by_length = {
    3: "abc",
    4: "abcd",
    5: "abcde",
    6: "abcdef",
    7: "abcdefg",
    8: "abcdefgh",
    9: "abcdefghi",
    10: "abcdefghij"
}

num_runs = 30  # Number of times to run each test
cipher_file = "ciphertext.txt"  # Updated to match the actual output filename
dictionary_file = "american-english"  # Updated to the correct dictionary filename
output_csv = "serial_timings_benchmark_results.csv"  # Updated output CSV filename

# Function to create encrypted file for a given input string
def encrypt_string(input_string):
    subprocess.run(["./encrypt", input_string], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

# Function to benchmark the decryption
def benchmark_decrypt():
    start_time = time.perf_counter()
    result = subprocess.run(
        ["./decrypt_serial", cipher_file, dictionary_file],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    end_time = time.perf_counter()
    return end_time - start_time

# Main benchmarking
results = []
for length, word in words_by_length.items():
    print(f"Running tests for length {length}...")
    for trial in range(1, num_runs + 1):
        encrypt_string(word)  # Create the cipher file for this word
        runtime = benchmark_decrypt()  # Measure runtime for decryption
        results.append({"Length": length, "Trial": trial, "Runtime": runtime})

# Save results to CSV
with open(output_csv, mode='w', newline='') as csv_file:
    fieldnames = ["Length", "Trial", "Runtime"]
    writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerows(results)

print("Benchmarking complete. Results saved to serial_timings_benchmark_results.csv.")
