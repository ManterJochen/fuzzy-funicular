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

## Architekturprinzip

Die Engine wird als Schichtenmodell gebaut. Jede Schicht darf nur von einer
darunterliegenden Schicht abhängen:

```text
Python / RL / externe Anwendungen
              |
              v
Interface und Serialization
              |
              v
Simulation und Environment
              |
       +------+------+
       |             |
       v             v
   Control       Sensors
       |
       v
Physics und Constraints
              |
              v
Robot Model, Kinematics, Dynamics
              |
              v
Math Core
```

Rendering liest einen Snapshot aus der Simulation. Es verändert niemals direkt
den Simulationszustand.

## Abhängigkeitsregeln

```text
math       -> kennt nur math
robot      -> kennt math
physics    -> kennt robot und math
control    -> kennt robot, math und benötigte Physikdaten
simulation -> verbindet robot, physics, control und sensors
rendering  -> liest Render-Snapshots und Transform-Daten
interface  -> benutzt die stabile Simulation-API
python     -> benutzt interface
rl         -> benutzt die Python-Umgebung
```

Verboten sind insbesondere:

- Physikberechnungen im Renderer
- doppelte Zustandsmodelle in Python und C++
- direkte Manipulation interner C++-Daten aus Python
- RL-Algorithmen im Simulationskern
- Abhängigkeiten von `math` auf Robotik, Physik oder Python

## Verantwortlichkeiten

| Paket | Aufgabe | Ergebnis |
| --- | --- | --- |
| `math` | Vektoren, Matrizen, Rotation, Geometrie und Solver | mathematisch zuverlässige Grundtypen |
| `robot` | Links, Gelenke, Zustand, Kinematik und Dynamik | beschreibbarer und berechenbarer Roboter |
| `physics` | Kräfte, Constraints, Kontakte und Integration | zeitliche Zustandsentwicklung |
| `control` | Ziele in Positionen, Geschwindigkeiten oder Kräfte übersetzen | Controller- und Trajektorienausgaben |
| `simulation` | alle Systeme in fester Reihenfolge ausführen | reproduzierbarer Simulationszustand |
| `sensors` | Zustand in Messwerte umwandeln | Observation-Daten |
| `rendering` | Zustand visualisieren | Render-Snapshot oder Bild |
| `interface` | stabile C++- und Python-Schnittstelle | externe Nutzung der Engine |
| `rl` | Action, Observation, Reward und Termination | trainierbare Umgebung |

## Datenfluss eines Simulationsschritts

```text
1. Action oder Controllerziel einlesen
2. Action durch Limits und Actuator-Modell führen
3. Gelenkkräfte und externe Kräfte berechnen
4. Constraints und Kontakte lösen
5. Robot state integrieren
6. Link- und Frame-Transforms aktualisieren
7. Sensoren aus dem neuen Zustand berechnen
8. Observation und Reward erzeugen
9. Render-Snapshot veröffentlichen
10. Zustand an C++- oder Python-Aufrufer zurückgeben
```

Die Simulation ist die einzige Instanz, die den maßgeblichen Zustand besitzt.
Rendering, Sensoren und Python erhalten daraus abgeleitete Daten.

## Implementierungsphasen

### Phase 0: Fundament

```text
[ ] CMake
[ ] Compilerwarnungen
[ ] CTest
[ ] Smoke-Test
```

### Phase 1: Math Core

```text
[ ] Scalar und Toleranzen
[ ] Vector und Matrix
[ ] lineare Gleichungssysteme
[ ] Rotation und Quaternion
[ ] Transform, Pose und Frame
[ ] Geometry und Spatial Math
```

### Phase 2: Robotik

```text
[ ] RobotModel
[ ] Links und Gelenke
[ ] RobotState
[ ] Forward Kinematics
[ ] Jacobian
[ ] Inverse Kinematics
[ ] Roboterdynamik
```

### Phase 3: Physik und Control

```text
[ ] World
[ ] Gravitation
[ ] Integration
[ ] Constraints und Kollision
[ ] PID und Actuators
[ ] Trajektorien
```

### Phase 4: Simulation

```text
[ ] Simulator
[ ] fester Timestep
[ ] Reset
[ ] Environment
[ ] Sensoren
```

### Phase 5: Sichtbarkeit und externe Nutzung

```text
[ ] Render-Snapshot
[ ] Renderer
[ ] C++-API
[ ] Python-Bindings
[ ] Python-Environment
```

### Phase 6: Reinforcement Learning

```text
[ ] Observation Space
[ ] Action Space
[ ] Reward
[ ] Termination
[ ] Random Agent
[ ] Training und Evaluation
```

## Architekturtests

Jede Schicht benötigt Unit-Tests für ihr eigenes Verhalten und mindestens einen
Integrationstest an jeder wichtigen Paketgrenze.

```text
[ ] Math: Algebra, Toleranzen und Rundtrip-Konvertierungen
[ ] Robot: bekannte Forward-Kinematics-Lösungen
[ ] Kinematics: analytischer gegen numerischen Jacobian
[ ] Dynamics: Gravitation, Energie und Momentum
[ ] Physics: Integration, Limits und Kollision
[ ] Control: PID-Konvergenz und Actuator-Sättigung
[ ] Simulation: deterministisches Reset und fester Timestep
[ ] Interface: gültige finite Python-Werte
[ ] RL: korrekte Observation, Reward und Termination
```

## Bezug zum Projektplan

Der konkrete Dateiplan und der aktuelle Fortschritt stehen in
[README.md](README.md). Diese Datei beschreibt die Struktur und Regeln; die
README beschreibt die Reihenfolge, Verantwortlichkeit und Definition of Done
für jede einzelne Datei beziehungsweise jedes Paket.