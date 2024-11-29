import subprocess

# Define words of length 3 to 10 for testing
test_words = ["cat", "code", "apple", "garden", "freedom", "computer", "attention", "impression"]
cipher_file = "ciphertext.txt"
dictionary_file = "american-english"  # Path to the dictionary file
serial_executable = "./decrypt_serial"
mpi_executable = "./decrypt"
num_processes = 4  # Number of processes for MPI

# Function to create encrypted file for a given input string
def encrypt_string(input_string):
    subprocess.run(["./encrypt", input_string], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

# Function to run the serial decryption and capture output after "Results"
def run_serial_decrypt():
    result = subprocess.run(
        [serial_executable, cipher_file, dictionary_file],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    output_lines = result.stdout.strip().splitlines()
    
    # Filter lines after "Results"
    results_start = False
    filtered_output = []
    for line in output_lines:
        if "Results" in line:
            results_start = True
            continue
        if results_start:
            filtered_output.append(line)
    
    return "\n".join(filtered_output)

# Function to run the MPI decryption, filter output to ignore "Rank" lines, and only keep lines after "Results"
def run_mpi_decrypt():
    result = subprocess.run(
        ["mpiexec", "-n", str(num_processes), mpi_executable, cipher_file, dictionary_file],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    output_lines = result.stdout.strip().splitlines()
    
    # Find the start of the "Results" section
    results_start = False
    filtered_output = []
    for line in output_lines:
        if "Results" in line:
            results_start = True
            continue
        if results_start and "Rank" not in line:
            filtered_output.append(line)
    
    return "\n".join(filtered_output)

# Main testing
print("Starting tests...")
for word in test_words:
    print(f"Testing word: {word}")
    
    # Encrypt the word to create the cipher text file
    encrypt_string(word)
    
    # Run the serial version and capture its filtered output
    serial_output = run_serial_decrypt()
    print(f"Serial Output (filtered):\n{serial_output}")
    
    # Run the MPI version and capture its filtered output
    mpi_output = run_mpi_decrypt()
    print(f"MPI Output (filtered):\n{mpi_output}")
    
    # Compare the outputs
    if serial_output == mpi_output:
        print(f"Test passed for word '{word}': Outputs match.\n")
    else:
        print(f"Test failed for word '{word}': Outputs do not match.\n")

print("Testing complete.")
