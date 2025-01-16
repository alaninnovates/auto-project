import json
import os


def parse_link_name(link_name):
    if "coralmark" in link_name:
        return "CoralMark" + link_name[-1].upper()
    return link_name[0].upper() + link_name[1:]


links = {}
path_files = os.listdir("paths")
for path_file in path_files:
    with open("paths/" + path_file) as f:
        path = json.load(f)
        way0 = path["waypoints"][0]
        links[parse_link_name(way0["linkedName"])] = {
            "anchor": way0["anchor"],
            "rotation": path["idealStartingState"]["rotation"],
        }
        way1 = path["waypoints"][1]
        links[parse_link_name(way1["linkedName"])] = {
            "anchor": way1["anchor"],
            "rotation": path["goalEndState"]["rotation"],
        }

# sort links
links = dict(sorted(links.items()))

generated_dir = "generated"

if not os.path.exists(generated_dir):
    os.makedirs(generated_dir)

with open(f"{generated_dir}/links.json", "w") as f:
    json.dump(links, f, indent=4)
