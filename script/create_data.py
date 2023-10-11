import subprocess

# Run 'sudo apt update' and capture the output
map_name = "assets/random-32-32-10.map"
agent = "40"
heuristic = "conflict"
command = "build/main -v 1 -m "+map_name+" -N "+agent+" -h "+heuristic
print(command)
try:
    result = subprocess.check_output(command, shell=True, stderr=subprocess.STDOUT, universal_newlines=True)
    # 'universal_newlines=True' converts the output to text
except subprocess.CalledProcessError as e:
    result = e.output  # Capture the error message if 'sudo apt update' fails

# Print the output
print("Checking")
print(result.split('\n'))
