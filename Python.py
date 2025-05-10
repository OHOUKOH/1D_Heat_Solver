import numpy as np
import os
import matplotlib.pyplot as plt
import subprocess

"""
        This python script reads: x_min , x_max, delta_t, diffusion coefficient 
        from problem.ini directly.
"""


def read_problem_parameters(filename):
    params = {}
    
    with open(filename, "r") as file:
        for line in file:
            if "=" in line:
                key, value = line.strip().split("=")
                params[key.strip()] = np.float64(value.strip())

    return params["x_min"], params["x_max"], params["delta_t"], params["diffusion_coefficient"]


x_min, x_max, delta_t,diffusion_coefficient = read_problem_parameters("./Setup/problem.ini")


"""
    Initial condition U(0,x)= Sin(pi*x) , we use N sample of [x_min , x_max]
    to build the initial condition.
"""


N= 100
x = np.linspace(x_min, x_max, N)
U_0 = np.sin(np.pi * x)   
U_0.astype(np.float64).tofile("./Setup/init.dat")


"""
    We call our c++ program executable
"""


print("Heat equation program lauching")
result = subprocess.run(["./Bin/heat_solver.exe"])
 
# result must be 0 if the execution was successful.
if result.returncode != 0:
    print("C++ program failed.")
    exit(1)


#Once the output is ready we need to add them into a single array.
#First we sort ensure timestep consitency
#By taking step vlaue between _ and . dat.

output_files = sorted([
    f for f in os.listdir("./Output/")
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

"""
We define the y axis which correspond to how we move in time. And plot
the 2D heatmap.
"""

timesteps = heat.shape[0]
y= np.linspace(0, delta_t * timesteps, timesteps)

plt.figure(figsize=(10, 6))
plt.imshow(heat, aspect='auto', origin='lower', extent=[x_min, x_max, 0, y[-1]], cmap='hot')
plt.colorbar(label='Temperature')
plt.xlabel("x")
plt.ylabel("Time")
plt.title("Heat Equation: Temperature Evolution Over Time")
plt.tight_layout()
plt.show()






