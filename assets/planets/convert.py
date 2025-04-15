import os

folder = os.path.dirname(__file__)
out_headers = []
planets_array = []

for filename in sorted(os.listdir(folder)):
    if filename.startswith("planet") and filename.endswith(".png"):
        name = filename.replace(".", "_")
        varname = name
        in_path = os.path.join(folder, filename)
        out_path = os.path.join(folder, f"{name}.h")
        out_headers.append(f'#include "{name}.h"')
        planets_array.append((varname, f"{varname}_len"))

        with open(in_path, "rb") as f:
            data = f.read()
        header = f"unsigned char {varname}[] = {{\n"
        header += ', '.join(f"0x{b:02x}" for b in data)
        header += f"\n}};\nunsigned int {varname}_len = {len(data)};\n"

        with open(out_path, "w") as out:
            out.write(header)

# Create planets.h
with open(os.path.join(folder, "planets.h"), "w") as f:
    f.write("#ifndef PLANETS_H\n#define PLANETS_H\n\n")
    for h in out_headers:
        f.write(h + "\n")
    f.write("\nstatic unsigned char* planet_imgs[] = {\n")
    f.write(",\n".join(p[0] for p in planets_array) + "\n};\n")
    f.write("static unsigned int planet_img_lens[] = {\n")
    f.write(",\n".join(p[1] for p in planets_array) + "\n};\n")
    f.write("\n#endif\n")

print("✅ All planet PNGs converted and planets.h generated.")
