import numpy as np
import os
import matplotlib.pyplot as plt
import subprocess

# === PARAMETERS ===
N = 110                   # Number of spatial points (excluding boundaries)
tf = 0.5                  # Final time
alpha = 1.0               # Diffusion coefficient
x_min, x_max = 0.0, 1.0   # Spatial domain
dt = 0.5 / 110            # Time step (example)

# === STEP 1: Generate initial condition ===
os.makedirs("Setup", exist_ok=True)
os.makedirs("Output", exist_ok=True)

x = np.linspace(x_min, x_max, N)
T0 = np.sin(np.pi * x)   # Example: sine wave initial condition
T0.astype(np.float64).tofile("Setup/init.dat")

# === STEP 2: Write problem.ini ===
with open("Setup/problem.ini", "w") as f:
    f.write(f"x_min = {x_min}\n")
    f.write(f"x_max = {x_max}\n")
    f.write(f"delta_t = {dt:.16f}\n")
    f.write(f"diffusion_coefficient = {alpha}\n")

# === STEP 3: Run the compiled C++ program ===
print("Running heat_solver.exe...")
result = subprocess.run(["./Bin/heat_solver.exe"])  # If using Linux/Mac, change to ./main
if result.returncode != 0:
    print("C++ program failed.")
    exit(1)

# === STEP 4: Read output files ===
output_files = sorted([
    f for f in os.listdir("Output")
    if f.startswith("output_") and f.endswith(".dat")
], key=lambda name: int(name.split("_")[1].split(".")[0]))

if not output_files:
    print("No output files found in Output/.")
    exit(1)

temperature_data = []
for filename in output_files:
    path = os.path.join("Output", filename)
    T = np.fromfile(path, dtype=np.float64)
    temperature_data.append(T)

temperature_data = np.array(temperature_data)  # shape: (timesteps, N)

# === STEP 5: Time and space axes ===
timesteps = temperature_data.shape[0]
time = np.linspace(0, dt * timesteps, timesteps)
x = np.linspace(x_min, x_max, N)

# === STEP 6: Plot heatmap ===
plt.figure(figsize=(10, 6))
extent = [x_min, x_max, 0, time[-1]]
plt.imshow(temperature_data, aspect='auto', origin='lower', extent=extent, cmap='hot')
plt.colorbar(label='Temperature')
plt.xlabel("x")
plt.ylabel("Time")
plt.title("Heat Equation: Temperature Evolution Over Time")
plt.tight_layout()
plt.show()
