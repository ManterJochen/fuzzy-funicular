# fuzzy-funicular
6DoF Robot arm simulation. Created from scratch in c++ Use of RL via Python to do pick and place actions. All of it from scratch.

```text
robot-simulator/
│
├── CMakeLists.txt
├── README.md
│
├── src/
│   │
│   ├── core/
│   │   ├── application/
│   │   ├── config/
│   │   ├── logging/
│   │   └── timing/
│   │
│   ├── math/
│   │   ├── vectors/
│   │   ├── matrices/
│   │   ├── rotations/
│   │   ├── transforms/
│   │   ├── geometry/
│   │   └── numerical/
│   │
│   ├── robot/
│   │   ├── model/
│   │   ├── joints/
│   │   ├── links/
│   │   ├── dynamics/
│   │   ├── kinematics/
│   │   └── state/
│   │
│   ├── physics/
│   │   ├── world/
│   │   ├── integration/
│   │   ├── forces/
│   │   ├── constraints/
│   │   └── collision/
│   │
│   ├── control/
│   │   ├── controllers/
│   │   ├── actuators/
│   │   └── trajectory/
│   │
│   ├── simulation/
│   │   ├── simulator/
│   │   ├── environment/
│   │   ├── reset/
│   │   └── stepping/
│   │
│   ├── sensors/
│   │   ├── joints/
│   │   ├── imu/
│   │   ├── force/
│   │   └── camera/
│   │
│   ├── rendering/
│   │   ├── renderer/
│   │   ├── camera/
│   │   ├── mesh/
│   │   ├── shaders/
│   │   └── scene/
│   │
│   ├── interface/
│   │   ├── api/
│   │   ├── python/
│   │   ├── serialization/
│   │   └── ipc/
│   │
│   └── rl/
│       ├── environment/
│       ├── observation/
│       ├── action/
│       ├── reward/
│       ├── termination/
│       └── wrappers/
│
├── include/
│   ├── core/
│   ├── math/
│   ├── robot/
│   ├── physics/
│   ├── control/
│   ├── simulation/
│   ├── sensors/
│   ├── rendering/
│   ├── interface/
│   └── rl/
│
├── python/
│   │
│   ├── simulator/
│   │   ├── __init__.py
│   │   ├── environment.py
│   │   ├── spaces.py
│   │   ├── wrapper.py
│   │   └── vector_env.py
│   │
│   ├── rl/
│   │   ├── agents/
│   │   ├── policies/
│   │   ├── algorithms/
│   │   ├── callbacks/
│   │   └── evaluation/
│   │
│   ├── training/
│   │   ├── configs/
│   │   ├── train.py
│   │   ├── evaluate.py
│   │   └── visualize.py
│   │
│   └── examples/
│       ├── random_agent.py
│       ├── train_agent.py
│       └── evaluate_agent.py
│
├── tests/
│   ├── math/
│   ├── robot/
│   ├── physics/
│   ├── control/
│   ├── simulation/
│   ├── interface/
│   └── rl/
│
├── assets/
│   ├── robots/
│   ├── environments/
│   ├── textures/
│   └── shaders/
│
├── configs/
│   ├── robots/
│   ├── environments/
│   ├── simulation/
│   └── rl/
│
├── examples/
│   ├── cpp/
│   │   ├── basic_robot/
│   │   ├── kinematics/
│   │   ├── dynamics/
│   │   └── simulation/
│   │
│   └── python/
│       ├── environment/
│       └── reinforcement_learning/
│
└── apps/
    ├── simulator/
    ├── headless/
    └── benchmark/
```