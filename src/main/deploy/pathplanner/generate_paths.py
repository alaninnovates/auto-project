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

generated_paths_dir = "generated/paths"

# find every possible permutation of two links
permutations = []
for link1 in links:
    for link2 in links:
        if link1 != link2:
            permutations.append((link1, link2))

if not os.path.exists(generated_paths_dir):
    os.makedirs(generated_paths_dir)

for i, (link1, link2) in enumerate(permutations):
    path = base_json.copy()
    path["waypoints"][0]["anchor"] = links[link1]["anchor"]
    path["waypoints"][0]["linkedName"] = link1
    path["waypoints"][0]["nextControl"] = links[link2]["anchor"]
    path["waypoints"][1]["anchor"] = links[link2]["anchor"]
    path["waypoints"][1]["linkedName"] = link2
    path["waypoints"][1]["prevControl"] = links[link1]["anchor"]
    path["idealStartingState"]["rotation"] = links[link1]["rotation"]
    path["goalEndState"]["rotation"] = links[link2]["rotation"]

    with open(f"{generated_paths_dir}/{link1}_{link2}.path", "w") as f:
        json.dump(path, f, indent=4)
