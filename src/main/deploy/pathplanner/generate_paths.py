import json
import os

links = {}
with open("generated/links.json") as f:
    links = json.load(f)

base_json = json.loads(
    """
{
  "version": "2025.0",
  "waypoints": [
    {
      "anchor": {},
      "prevControl": null,
      "nextControl": {},
      "isLocked": false,
      "linkedName": ""
    },
    {
      "anchor": {},
      "prevControl": {},
      "nextControl": null,
      "isLocked": false,
      "linkedName": ""
    }
  ],
  "rotationTargets": [],
  "constraintZones": [],
  "pointTowardsZones": [],
  "eventMarkers": [],
  "globalConstraints": {
    "maxVelocity": 3.0,
    "maxAcceleration": 3.0,
    "maxAngularVelocity": 540.0,
    "maxAngularAcceleration": 720.0,
    "nominalVoltage": 12.0,
    "unlimited": false
  },
  "goalEndState": {
    "velocity": 0,
    "rotation": 0.0
  },
  "reversed": false,
  "folder": null,
  "idealStartingState": {
    "velocity": 0,
    "rotation": 0.0
  },
  "useDefaultConstraints": true
}
"""
)

generated_paths_dir = "paths"

# find every possible permutation of two links
permutations = []
for link1 in links:
    for link2 in links:
        if link1 != link2:
            permutations.append((link1, link2))

if not os.path.exists(generated_paths_dir):
    os.makedirs(generated_paths_dir)
else:
    for file in os.listdir(generated_paths_dir):
        os.remove(os.path.join(generated_paths_dir, file))


# find an anchor that is 20% of the distance from anchor1 to anchor2, and on the line between them
def get_twenty_percent_path(anchor1, anchor2):
    try:
        slope = (anchor2["y"] - anchor1["y"]) / (anchor2["x"] - anchor1["x"])
    except ZeroDivisionError:
        slope = 0
    y_int = anchor1["y"] - slope * anchor1["x"]
    dx = anchor2["x"] - anchor1["x"]
    new_x = 0.2 * dx + anchor1["x"]
    new_y = slope * new_x + y_int
    return {"x": new_x, "y": new_y}


for i, (link1, link2) in enumerate(permutations):
    path = base_json.copy()
    path["waypoints"][0]["anchor"] = links[link1]["anchor"].copy()
    path["waypoints"][0]["linkedName"] = link1
    path["waypoints"][0]["nextControl"] = get_twenty_percent_path(
        links[link1]["anchor"].copy(), links[link2]["anchor"].copy()
    ).copy()
    path["waypoints"][1]["anchor"] = links[link2]["anchor"].copy()
    path["waypoints"][1]["linkedName"] = link2
    path["waypoints"][1]["prevControl"] = get_twenty_percent_path(
        links[link2]["anchor"].copy(), links[link1]["anchor"].copy()
    ).copy()
    path["idealStartingState"]["rotation"] = links[link1]["rotation"]
    path["goalEndState"]["rotation"] = links[link2]["rotation"]

    with open(f"{generated_paths_dir}/{link1}_{link2}.path", "w") as f:
        json.dump(path, f, indent=4)
