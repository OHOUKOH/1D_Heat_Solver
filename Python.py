import numpy as np
import os
import matplotlib.pyplot as plt
import subprocess

"""
        We perfom the same parameterization as describe in the project
"""
N = 110                  
tf = 0.5                  
diffusion_coefficient = 1.0               
x_min, x_max = 0.0, 1.0   
delta_t = 0.5 / 110            

"""
    Making available directory for configuration .ini , .dat and the results .dat files
"""
os.makedirs("Setup", exist_ok=True)
os.makedirs("Output", exist_ok=True)

#We sample N point using the interval [x_min, x_max]
x = np.linspace(x_min, x_max, N)

"""
    Initial condition U(0,.)= Sin(pi*x)
"""

U_0 = np.sin(np.pi * x)   
U_0.astype(np.float64).tofile("Setup/init.dat")

# We then open our problem.ini and write onto it using key pair value .
with open("Setup/problem.ini", "w") as f:
    f.write(f"x_min = {x_min}\n")
    f.write(f"x_max = {x_max}\n")
    f.write(f"delta_t = {delta_t:.16f}\n")
    f.write(f"diffusion_coefficient = {diffusion_coefficient}\n")

"""
    We call our c++ program executable
"""
print("Heat equation program lauching")
result = subprocess.run(["./Bin/heat_solver.exe"])  

if result.returncode != 0:
    print("C++ program failed.")
    exit(1)


output_files = sorted([
    f for f in os.listdir("Output")
    if f.startswith("output_") and f.endswith(".dat")
], key=lambda name: int(name.split("_")[1].split(".")[0]))

if not output_files:
    print("No output files found in Output/.")
    exit(1)

heat = []
for filename in output_files:
    path = os.path.join("Output", filename)
    U = np.fromfile(path, dtype=np.float64)
    heat.append(U)

 # shape: (timesteps, N)

heat = np.array(heat)
print(heat.shape)  

#We define the y axis which correspond to how we move in time
timesteps = heat.shape[0]
y= np.linspace(0, delta_t * timesteps, timesteps)


# === STEP 6: Plot heatmap ===
plt.figure(figsize=(10, 6))
plt.imshow(heat, aspect='auto', origin='lower', extent=[x_min, x_max, 0, y[-1]], cmap='hot')
plt.colorbar(label='Temperature')
plt.xlabel("x")
plt.ylabel("Time")
plt.title("Heat Equation: Temperature Evolution Over Time")
plt.tight_layout()
plt.show()
