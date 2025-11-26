import matplotlib.pyplot as plt
import numpy as np

def read_data(filename):
    """Reads data from a file and returns x and y values."""
    data = []
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip().split()
            if len(line) == 3:
                data.append([float(x) for x in line])
    x_values = [row[0] for row in data]
    y_values = [row[1] for row in data]
    return x_values, y_values

# Reading data from text files for ASS and BSS models
filenames_ASS = [f'C:\\Users\\User\\Dropbox\\Queiruga\\progs\\CRs_python\\data\\ASSN16{i}.dat' for i in range(1, 11)]
filenames_BSS = [f'C:\\Users\\User\\Dropbox\\Queiruga\\progs\\CRs_python\\data\\BSSN16{i}.dat' for i in range(1, 11)]

# Reading data from text files for ASS and BSS models
#filenames_ASS = [f'C:\\Users\\User\\Dropbox\\Queiruga\\progs\\CRs_python\\data\\ASSNplane16{i}.dat' for i in range(1, 11)]
#filenames_BSS = [f'C:\\Users\\User\\Dropbox\\Queiruga\\progs\\CRs_python\\data\\BSSNplane16{i}.dat' for i in range(1, 11)]

# List of colors and labels for the particles
colors = ['gray', 'green', 'blue', 'yellow', 'purple', 'orange', 'cyan', 'magenta', 'brown', 'pink']
labels = [f'Particle {i+1}' for i in range(10)]

# Create two subplots side by side
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))

# Plotting ASS model
for i, filename in enumerate(filenames_ASS):
    x_values, y_values = read_data(filename)
    ax1.scatter(x_values, y_values, color=colors[i], label=labels[i], s=0.5)

# Plot points at specific positions for ASS
ax1.scatter(0, 0, color='black', label='Galactic Center')
ax1.scatter(-8.5, 0, color='red', label='Earth')

# Plotting the circle for ASS
circle_ASS = plt.Circle((0, 0), radius=20, color='b', fill=False, linestyle='--', label='Circle (r=20)')
ax1.add_patch(circle_ASS)

# Setting labels and title for ASS
ax1.set_xlabel('X (kpc)')
ax1.set_ylabel('Y (kpc)')
ax1.set_title('ASS (Nitrogen - Energy:10^16 eV)')
ax1.grid(True)
ax1.set_aspect('equal', adjustable='box')

# Plotting BSS model
for i, filename in enumerate(filenames_BSS):
    x_values, y_values = read_data(filename)
    ax2.scatter(x_values, y_values, color=colors[i], label=labels[i], s=0.5)

# Plot points at specific positions for BSS
ax2.scatter(0, 0, color='k', label='Galactic Center')
ax2.scatter(-8.5, 0, color='r', label='Earth')

# Plotting the circle for BSS
circle_BSS = plt.Circle((0, 0), radius=20, color='b', fill=False, linestyle='--', label='Circle (r=20)')
ax2.add_patch(circle_BSS)

# Setting labels and title for BSS
ax2.set_xlabel('X (kpc)')
ax2.set_ylabel('Y (kpc)')
ax2.set_title('BSS (Nitrogen - Energy:10^16 eV)')
ax2.grid(True)
ax2.set_aspect('equal', adjustable='box')

#Saving the graph
output_path = 'N2D16.png' #Nomenclatura ((Inicial da partícula)(Tipo de gráfico)(Energia))
#output_path = 'N2D16plane.png' #Nomenclatura ((Inicial da partícula)(Tipo de gráfico)(Energia))
plt.savefig(output_path, bbox_inches='tight')

# Move the legend outside the plot area for both plots
ax1.legend(loc='center left', bbox_to_anchor=(1, 0.5))
ax2.legend(loc='center left', bbox_to_anchor=(1, 0.5))

# Adjust the layout
plt.tight_layout()

# Show the plots
plt.show()
