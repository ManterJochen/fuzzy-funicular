# fuzzy-funicular

Eine selbst entwickelte 6DoF-Roboterarm-Simulationsengine in C++ mit Python- und RL-Schnittstelle für Pick-and-Place-Aufgaben.

Dieses Dokument ist gleichzeitig:

- Architekturplan
- Datei-Spezifikation
- Fortschrittsliste
- Definition of Done für jedes Paket

## Statuslegende

- `[x]` vorhanden und grundsätzlich implementiert
- `[~]` vorhanden, aber unvollständig oder muss stabilisiert werden
- `[!]` vorhanden, enthält aktuell einen Fehler oder eine wichtige technische Schuld
- `[ ]` noch zu erstellen

## Aktueller Stand

### Bereits vorhanden

Die aktuelle Codebasis besteht ausschließlich aus einer begonnenen Math-Schicht:

```text
src/math/scalar/
src/math/vector/
src/math/matrix/
```

Es existieren derzeit noch nicht:

```text
CMakeLists.txt
tests/
include/
src/core/
src/robot/
src/physics/
src/control/
src/simulation/
src/sensors/
src/rendering/
src/interface/
src/rl/
python/
configs/
assets/
examples/
apps/
```

### Wichtige Entscheidungen vor dem Weiterbau

1. Die bestehende Ordnerstruktur verwendet `vector` und `matrix`, nicht `vectors` und `matrices`. Diese README verwendet deshalb die tatsächlich vorhandenen Singularformen.
2. `src/math/vector/Vector.h` enthält zusätzlich einen Template-Vektor und ist aktuell untracked. Er überschneidet sich mit `VectorN.h`. Es muss genau eine öffentliche Vektorarchitektur geben.
3. Header bleiben zunächst in `src/`, bis CMake und die Tests stehen. Danach können öffentliche Header nach `include/` verschoben werden.
4. Die Implementierung wird in Abhängigkeitsreihenfolge gebaut: Scalar -> Vector/Matrix -> Robot -> Physics -> Simulation -> Python -> RL.

## Zielarchitektur

```text
Math
  +-- Scalar, Vector, Matrix, Linear Algebra
  +-- Rotation, Transform, Geometry, Spatial Math
    |
Robot Model
  +-- Links, Joints, State, Kinematics, Dynamics
    |
Physics and Control
  +-- Forces, Constraints, Collision, Controllers, Trajectories
    |
Simulation
  +-- World, Stepping, Reset, Environment
    |
Sensors, Rendering, Interface
    |
Python Environment and Reinforcement Learning
```

Abhängigkeitsregel:

```text
math kennt nur math
robot kennt math
physics kennt robot und math
simulation verbindet robot, physics und control
rendering und interface lesen Simulationsergebnisse
rl benutzt die Python-Umgebung
```

## Vollständige Projektarchitektur

Dies ist der geplante Zielbaum des Projekts. Die Ordner werden erst angelegt,
wenn die jeweilige Schicht in der Bauanleitung benötigt wird.

```text
fuzzy-funicular/
|
|- CMakeLists.txt
|- README.md
|- Architecture.md                 # separates Architekturdiagramm
|
|- src/
|  |
|  |- core/                         # Anwendung, Zeit, Konfiguration, Logging
|  |  |- application/
|  |  |- config/
|  |  |- logging/
|  |  `- timing/
|  |
|  |- math/                         # unabhängiger mathematischer Kern
|  |  |- scalar/
|  |  |- vector/
|  |  |- matrix/
|  |  |- linear_algebra/
|  |  |- rotation/
|  |  |- transform/
|  |  |- geometry/
|  |  |- spatial/
|  |  `- numerical/
|  |
|  |- robot/                        # Roboterbeschreibung und Robotikformeln
|  |  |- model/
|  |  |- joints/
|  |  |- links/
|  |  |- state/
|  |  |- kinematics/
|  |  `- dynamics/
|  |
|  |- physics/                      # Welt, Kräfte, Constraints, Kollision
|  |  |- world/
|  |  |- integration/
|  |  |- forces/
|  |  |- constraints/
|  |  `- collision/
|  |
|  |- control/                      # Aktuatoren, Controller, Trajektorien
|  |  |- controllers/
|  |  |- actuators/
|  |  `- trajectory/
|  |
|  |- simulation/                   # zentraler Simulationsablauf
|  |  |- simulator/
|  |  |- environment/
|  |  |- reset/
|  |  `- stepping/
|  |
|  |- sensors/                      # Messungen aus dem Simulationszustand
|  |  |- joints/
|  |  |- imu/
|  |  |- force/
|  |  `- camera/
|  |
|  |- rendering/                    # Darstellung, ohne Simulationslogik
|  |  |- renderer/
|  |  |- camera/
|  |  |- mesh/
|  |  |- shaders/
|  |  `- scene/
|  |
|  |- interface/                    # externe API und Datenübertragung
|  |  |- api/
|  |  |- python/
|  |  |- serialization/
|  |  `- ipc/
|  |
|  `- rl/                           # RL-spezifische C++-Abstraktionen
|     |- environment/
|     |- observation/
|     |- action/
|     |- reward/
|     |- termination/
|     `- wrappers/
|
|- include/                         # öffentliche Header nach Stabilisierung
|  |- core/
|  |- math/
|  |- robot/
|  |- physics/
|  |- control/
|  |- simulation/
|  |- sensors/
|  |- rendering/
|  |- interface/
|  `- rl/
|
|- python/
|  |- simulator/                    # Python-Umgebung und Gym-kompatible API
|  |  |- __init__.py
|  |  |- environment.py
|  |  |- spaces.py
|  |  |- wrapper.py
|  |  `- vector_env.py
|  |
|  |- rl/                            # Agenten, Policies und Algorithmen
|  |  |- agents/
|  |  |- policies/
|  |  |- algorithms/
|  |  |- callbacks/
|  |  `- evaluation/
|  |
|  |- training/                      # Training und Auswertung
|  |  |- configs/
|  |  |- train.py
|  |  |- evaluate.py
|  |  `- visualize.py
|  `- examples/
|
|- tests/                            # Unit-, Integrations- und End-to-End-Tests
|  |- math/
|  |- robot/
|  |- physics/
|  |- control/
|  |- simulation/
|  |- interface/
|  `- rl/
|
|- assets/                           # Meshes, Roboter- und Umgebungsdaten
|  |- robots/
|  |- environments/
|  |- textures/
|  `- shaders/
|
|- configs/                          # versionierte Laufzeitkonfigurationen
|  |- robots/
|  |- environments/
|  |- simulation/
|  `- rl/
|
|- examples/                         # kleine, nachvollziehbare Nutzungsbeispiele
|  |- cpp/
|  |  |- basic_robot/
|  |  |- kinematics/
|  |  |- dynamics/
|  |  `- simulation/
|  `- python/
|     |- environment/
|     `- reinforcement_learning/
|
`- apps/                             # ausführbare Programme
   |- simulator/
   |- headless/
   `- benchmark/
```

### Verantwortungsgrenzen

| Schicht | Darf kennen | Darf nicht enthalten |
| --- | --- | --- |
| `math` | Scalar-, Vector-, Matrix- und Geometriecode | Roboter, Physik, Python, Rendering |
| `robot` | `math` | Renderer, Python, RL |
| `physics` | `math`, `robot` | Python-API und UI-Code |
| `control` | `math`, `robot`, benötigte Physikdaten | Rendering |
| `simulation` | Robot, Physics, Control, Sensors | konkrete RL-Algorithmen |
| `sensors` | Simulationszustand und Math | eigene Physikmodelle |
| `rendering` | Render-Snapshot, Transform, Geometry | Controller und Physikänderungen |
| `interface` | stabile Simulations-API | doppelte Simulationslogik |
| `python` | Interface/API | direkte Manipulation interner C++-Daten |
| `rl` | Python Environment | Low-Level-Matrix- und Physikcode |

### Laufzeit-Datenfluss

Ein Simulationsschritt läuft immer in dieser Richtung:

```text
Python action oder C++ command
  |
  v
Controller / Actuator
  |
  v
Robot state und gewünschte Kräfte
  |
  v
Physics: Kräfte -> Constraints -> Integration
  |
  v
Aktualisierte Gelenke, Links und Frames
  |
  +--> Sensors -> Observation
  |
  +--> Render snapshot -> Renderer
  |
  `--> Python: observation, reward, terminated, truncated, info
```

Die Simulationsengine besitzt die Wahrheit über den Zustand. Rendering,
Sensoren und Python erhalten daraus nur abgeleitete Daten. Dadurch kann die
Simulation headless, visualisiert oder über RL betrieben werden, ohne drei
verschiedene Zustandsmodelle zu pflegen.

### Paketabhängigkeiten

```text
scalar
  -> vector, matrix
  -> linear_algebra
  -> rotation, transform, geometry, spatial, numerical
  -> robot/model, robot/kinematics, robot/dynamics
  -> physics, control
  -> simulation
  -> sensors, rendering, interface
  -> python, rl
```

Pfeile zeigen ausschließlich erlaubte Abhängigkeiten. Eine Abhängigkeit in die
entgegengesetzte Richtung ist ein Architekturfehler.

# Bauplan

## 0. Build- und Testfundament

### Dateien

```text
[ ] CMakeLists.txt
[ ] cmake/CompilerWarnings.cmake
[ ] tests/CMakeLists.txt
[ ] tests/smoke_test.cpp
```

### Verantwortung

- `CMakeLists.txt`: C++20-Projekt, Bibliotheken, Tests und Targets definieren.
- `CompilerWarnings.cmake`: einheitliche Compiler-Warnungen aktivieren.
- `tests/CMakeLists.txt`: Testframework und CTest registrieren.
- `tests/smoke_test.cpp`: beweist, dass Build und Testausführung funktionieren.

### Definition of Done

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

Alle drei Befehle müssen erfolgreich sein, bevor weitere Pakete wachsen.

## 1. Scalar

### Dateien

```text
[x] src/math/scalar/Constants.h
[x] src/math/scalar/Angle.h
[x] src/math/scalar/Angle.cpp
[x] src/math/scalar/Tolerance.h
[x] src/math/scalar/Tolerance.cpp
[x] src/math/scalar/Scalar.h
[ ] tests/math/scalar/Angle.test.cpp
[ ] tests/math/scalar/Tolerance.test.cpp
[ ] src/math/scalar/Scalar.cpp, falls später benötigt
```

### Verantwortung pro Datei

- `Scalar.h`: zentraler numerischer Typ, idealerweise `using Scalar = double`.
- `Constants.h`: PI, Winkelumrechnungen, Gravitation und Standardtoleranzen.
- `Angle.*`: Winkel in Radiant mit Grad-Konvertierung und Trigonometrie.
- `Tolerance.*`: absolute und relative Approximation, `approximatelyZero`.

### Noch nötig

```text
[x] NaN- und Infinity-Prüfungen
[x] approximatelyZero
[x] einheitliche Verwendung von Constants::PI in Angle
[ ] Tests für Grad, Radiant und Grenzwerte
```

## 2. Vector

### Vorhandene Dateien

```text
[x] src/math/vector/Vector2.h
[x] src/math/vector/Vector2.cpp
[x] src/math/vector/Vector3.h
[x] src/math/vector/Vector3.cpp
[x] src/math/vector/Vector4.h
[x] src/math/vector/Vector4.cpp
[x] src/math/vector/Vector6.h
[x] src/math/vector/Vector6.cpp
[x] src/math/vector/VectorN.h
[x] src/math/vector/VectorN.cpp
[x] src/math/vector/Vector.h
```

### Verantwortung

- `Vector.h`: generischer statischer `Vector<N>`. Entscheiden, ob er `VectorN` ersetzt.
- `Vector2`: 2D-Punkte und kleine mathematische Tests.
- `Vector3`: 3D-Robotikvektor mit Cross Product, Projektion und Reflexion.
- `Vector4`: homogene Koordinaten und Quaternion-Komponenten.
- `Vector6`: Gelenkvektoren, Twists und Wrenches.
- `VectorN`: dynamische Dimensionen für lineare Algebra.

### Noch nötig

```text
[x] eine Vector-Architektur auswählen
[x] length, squaredLength, normalized und distance vollständig implementieren
[x] Nullvektor-Normalisierung definiert behandeln
[x] Divisionen und Dimensionen einheitlich prüfen
[x] operator*(scalar) auch als freie Funktion ermöglichen
[ ] Vector-Unit-Tests schreiben
```

## 3. Matrix und lineare Algebra

### Vorhandene Dateien

```text
[x] src/math/matrix/Matrix2.h
[x] src/math/matrix/Matrix2.cpp
[x] src/math/matrix/Matrix3.h
[x] src/math/matrix/Matrix3.cpp
[x] src/math/matrix/Matrix4.h
[x] src/math/matrix/Matrix4.cpp
[ ] src/math/matrix/Matrix6.h
[ ] src/math/matrix/Matrix6.cpp
[x] src/math/matrix/MatrixN.h
[x] src/math/matrix/MatrixN.cpp
```

### Verantwortung

- `MatrixN`: dynamische Matrizen, Zugriff, Addition, Multiplikation, Transponierung.
- `Matrix2`: 2x2-Spezialisierung und kleine Tests.
- `Matrix3`: Rotationen und Trägheitstensoren.
- `Matrix4`: homogene Transformationen.
- `Matrix6`: Spatial Math und Jacobians.

### Aktuelle Probleme

```text
[x] doppelte Matrix4-Konstruktor-Definition entfernen
[x] fehlende beziehungsweise inkonsistente Matrix4-Initializer-Implementierung prüfen
[x] Inversion mit Partial Pivoting versehen
[x] exakte Identity- und Symmetrievergleiche durch Toleranzen ersetzen
[x] rekursive Determinante durch pivotierende Elimination ersetzen
```

### Noch zu erstellen

```text
[ ] src/math/linear_algebra/Norms.h/.cpp
[ ] src/math/linear_algebra/LinearSystem.h/.cpp
[ ] src/math/linear_algebra/LU.h/.cpp
[ ] src/math/linear_algebra/QR.h/.cpp
[ ] src/math/linear_algebra/SVD.h/.cpp
[ ] src/math/linear_algebra/PseudoInverse.h/.cpp
[ ] tests/math/matrix/
[ ] tests/math/linear_algebra/
```

## 4. Rotation, Transform und Geometry

### Zu erstellen

```text
[ ] src/math/rotation/Quaternion.h/.cpp
[ ] src/math/rotation/RotationMatrix.h/.cpp
[ ] src/math/rotation/EulerAngles.h/.cpp
[ ] src/math/rotation/AxisAngle.h/.cpp
[ ] src/math/rotation/RotationVector.h/.cpp
[ ] src/math/rotation/Conversion.h/.cpp
[ ] src/math/transform/Transform.h/.cpp
[ ] src/math/transform/Pose.h/.cpp
[ ] src/math/transform/Frame.h/.cpp
[ ] src/math/geometry/Point.h/.cpp
[ ] src/math/geometry/Line.h/.cpp
[ ] src/math/geometry/Ray.h/.cpp
[ ] src/math/geometry/Segment.h/.cpp
[ ] src/math/geometry/Plane.h/.cpp
[ ] src/math/geometry/Sphere.h/.cpp
[ ] src/math/geometry/Box.h/.cpp
[ ] src/math/geometry/Capsule.h/.cpp
```

### Verantwortung

- Rotation: gültige 3D-Orientierungen und Konvertierungen.
- Transform: Rotation plus Translation und deren Verkettung.
- Pose: Position plus Orientierung.
- Frame: benannte Koordinatensysteme mit Parent-Beziehung.
- Geometry: Abstände, Projektionen, Schnitt- und Kollisionsabfragen.

### Definition of Done

```text
[ ] Punkt und Vektor unterscheiden sich korrekt bei Transformationen
[ ] Transform * inverse(Transform) ergibt Identität
[ ] Euler-Konvention ist dokumentiert
[ ] Quaternion-SLERP funktioniert
[ ] Frame-Ketten liefern reproduzierbare Weltkoordinaten
```

## 5. Spatial Math

```text
[ ] src/math/spatial/SpatialVector.h/.cpp
[ ] src/math/spatial/Twist.h/.cpp
[ ] src/math/spatial/Wrench.h/.cpp
[ ] src/math/spatial/SpatialTransform.h/.cpp
[ ] src/math/spatial/SpatialInertia.h/.cpp
[ ] tests/math/spatial/
```

- `Twist`: lineare und angulare Geschwindigkeit.
- `Wrench`: Kraft und Drehmoment.
- `SpatialTransform`: Wechsel zwischen Koordinatensystemen.
- `SpatialInertia`: Masse, Schwerpunkt und Trägheit.

## 6. Robot Model

```text
[ ] src/robot/model/RobotModel.h/.cpp
[ ] src/robot/links/Link.h/.cpp
[ ] src/robot/joints/Joint.h/.cpp
[ ] src/robot/state/RobotState.h/.cpp
[ ] src/robot/model/RobotDescription.h/.cpp
[ ] configs/robots/robot6.yaml
[ ] tests/robot/model/
```

- `Link`: Masse, Schwerpunkt, Trägheit und Geometrie.
- `Joint`: Gelenktyp, Achse, Grenzen und Ursprungstransformation.
- `RobotModel`: statische Link-Joint-Struktur.
- `RobotState`: `q`, `qDot`, `qDDot` und Gelenkmomente.
- `RobotDescription`: Laden und Validieren einer Roboterkonfiguration.

## 7. Kinematics

```text
[ ] src/robot/kinematics/ForwardKinematics.h/.cpp
[ ] src/robot/kinematics/Jacobian.h/.cpp
[ ] src/robot/kinematics/InverseKinematics.h/.cpp
[ ] src/robot/kinematics/JointVector.h/.cpp
[ ] src/robot/kinematics/CartesianVector.h/.cpp
[ ] tests/robot/kinematics/
```

Reihenfolge:

1. Forward Kinematics
2. numerischer Jacobian als Referenz
3. analytischer Jacobian
4. Rang- und Singularitätsprüfung
5. gedämpfte Pseudoinverse
6. Gelenkgrenzen und IK-Abbruchbedingungen

## 8. Dynamics

```text
[ ] src/robot/dynamics/MassMatrix.h/.cpp
[ ] src/robot/dynamics/InertiaTensor.h/.cpp
[ ] src/robot/dynamics/Gravity.h/.cpp
[ ] src/robot/dynamics/Momentum.h/.cpp
[ ] src/robot/dynamics/Energy.h/.cpp
[ ] tests/robot/dynamics/
```

Zuerst implementieren:

```text
[ ] Gravitation
[ ] kinetische Energie
[ ] potentielle Energie
[ ] Massematrix
[ ] externe Kräfte und Drehmomente
```

Danach:

```text
[ ] Coriolis- und Zentrifugalkräfte
[ ] vollständige Roboterdynamik
```

## 9. Physics

```text
[ ] src/physics/world/World.h/.cpp
[ ] src/physics/forces/Gravity.h/.cpp
[ ] src/physics/forces/ExternalForce.h/.cpp
[ ] src/physics/integration/SemiImplicitEuler.h/.cpp
[ ] src/physics/integration/RungeKutta4.h/.cpp
[ ] src/physics/constraints/JointLimits.h/.cpp
[ ] src/physics/collision/CollisionWorld.h/.cpp
[ ] src/physics/collision/Contact.h/.cpp
[ ] tests/physics/
```

Erster funktionierender Physik-Slice:

```text
Robot + Gravity + Torque + SemiImplicitEuler + Joint Limits
```

## 10. Control

```text
[ ] src/control/actuators/Actuator.h/.cpp
[ ] src/control/actuators/TorqueActuator.h/.cpp
[ ] src/control/controllers/PIDController.h/.cpp
[ ] src/control/controllers/JointPositionController.h/.cpp
[ ] src/control/trajectory/ScalarTrajectory.h/.cpp
[ ] src/control/trajectory/JointTrajectory.h/.cpp
[ ] tests/control/
```

Der erste Controller ist ein Gelenkpositions-PID. Danach folgen Gravitätskompensation, Trajektorien und Cartesian Control.

## 11. Simulation

```text
[ ] src/simulation/simulator/Simulator.h/.cpp
[ ] src/simulation/environment/Environment.h/.cpp
[ ] src/simulation/stepping/SimulationClock.h/.cpp
[ ] src/simulation/reset/ResetPolicy.h/.cpp
[ ] tests/simulation/
```

Ein Simulationsschritt muss diese Reihenfolge besitzen:

```text
Action lesen
Controller ausführen
Kräfte berechnen
Constraints lösen
Zustand integrieren
Frames aktualisieren
Sensoren aktualisieren
Observation erzeugen
```

Der Physik-Timestep bleibt fest, beispielsweise `0.001` Sekunden.

## 12. Sensors

```text
[ ] src/sensors/joints/JointSensor.h/.cpp
[ ] src/sensors/imu/ImuSensor.h/.cpp
[ ] src/sensors/force/ForceTorqueSensor.h/.cpp
[ ] src/sensors/camera/CameraModel.h/.cpp
[ ] tests/sensors/
```

Jeder Sensor braucht:

```text
frame
sampling rate
measurement output
optional noise model
```

## 13. Rendering

```text
[ ] src/rendering/renderer/Renderer.h/.cpp
[ ] src/rendering/camera/RenderCamera.h/.cpp
[ ] src/rendering/mesh/Mesh.h/.cpp
[ ] src/rendering/scene/Scene.h/.cpp
[ ] src/rendering/shaders/
[ ] tests/rendering/
```

Rendering liest einen Snapshot der Simulation. Es darf keine Physik oder Controllerlogik enthalten.

Erste Darstellung:

```text
[ ] Gelenke als Koordinatenachsen
[ ] Links als Boxen oder Kapseln
[ ] Bodenebene
[ ] Zielobjekt
```

## 14. Core

```text
[ ] src/core/application/Application.h/.cpp
[ ] src/core/config/Config.h/.cpp
[ ] src/core/logging/Logger.h/.cpp
[ ] src/core/timing/Clock.h/.cpp
[ ] tests/core/
```

Diese Dateien verwalten Anwendung, Konfiguration, Logs und Zeit. Sie enthalten keine Robotikformeln.

## 15. C++- und Python-Interface

```text
[ ] src/interface/api/SimulatorApi.h/.cpp
[ ] src/interface/serialization/StateSerializer.h/.cpp
[ ] src/interface/python/Bindings.cpp
[ ] python/simulator/__init__.py
[ ] python/simulator/environment.py
[ ] python/simulator/spaces.py
[ ] python/simulator/wrapper.py
[ ] tests/interface/
```

Die Python-API braucht mindestens:

```python
observation = env.reset()
observation, reward, terminated, truncated, info = env.step(action)
```

Python darf die Simulationslogik nicht duplizieren. Die Berechnung bleibt in C++.

## 16. RL

```text
[ ] python/rl/agents/
[ ] python/rl/policies/
[ ] python/rl/algorithms/
[ ] python/rl/callbacks/
[ ] python/rl/evaluation/
[ ] python/training/train.py
[ ] python/training/evaluate.py
[ ] python/training/visualize.py
[ ] tests/rl/
```

Erste Observation:

```text
joint positions
joint velocities
end-effector position
target position
distance to target
```

Erste Action:

```text
target joint positions
```

Erste Reward:

```text
distance penalty
action penalty
collision penalty
success reward
timeout penalty
```

## 17. Assets, Configs, Examples und Apps

```text
[ ] assets/robots/
[ ] assets/environments/
[ ] assets/textures/
[ ] assets/shaders/
[ ] configs/environments/
[ ] configs/simulation/
[ ] configs/rl/
[ ] examples/cpp/basic_robot/
[ ] examples/cpp/kinematics/
[ ] examples/cpp/dynamics/
[ ] examples/cpp/simulation/
[ ] examples/python/environment/
[ ] examples/python/reinforcement_learning/
[ ] apps/simulator/
[ ] apps/headless/
[ ] apps/benchmark/
```

Diese Bereiche kommen erst, wenn die zugrunde liegende Engine testbar ist.

# Meilensteine

## M1: Math kompiliert und getestet

```text
[ ] CMake und CTest
[ ] Scalar
[ ] Vector
[ ] Matrix
[ ] lineare Gleichungssysteme
```

## M2: Raumrechnung funktioniert

```text
[ ] Quaternion
[ ] RotationMatrix
[ ] Transform
[ ] Pose
[ ] Frame
```

## M3: Ein Roboter kann seine Pose berechnen

```text
[ ] RobotModel
[ ] Link
[ ] Joint
[ ] RobotState
[ ] Forward Kinematics
```

## M4: Ein Roboter kann eine Zielpose erreichen

```text
[ ] Jacobian
[ ] Pseudoinverse
[ ] Inverse Kinematics
[ ] Gelenkgrenzen
```

## M5: Ein Roboter bewegt sich physikalisch

```text
[ ] Massenträgheit
[ ] Gravitation
[ ] Integration
[ ] Constraints
```

## M6: Ein Roboter folgt Trajektorien

```text
[ ] PID
[ ] Actuators
[ ] Trajectories
[ ] Torque limits
```

## M7: Umgebung und Kollision funktionieren

```text
[ ] World
[ ] Collision
[ ] Contact
[ ] Sensors
```

## M8: Python und RL funktionieren

```text
[ ] pybind11 API
[ ] reset/step
[ ] Observation
[ ] Action
[ ] Reward
[ ] Training
```

# Testregeln

Jede neue mathematische Funktion bekommt zuerst einen Unit-Test. Jede neue Paketgrenze bekommt zusätzlich einen Integrationstest.

Besonders wichtige Tests:

```text
[ ] Transform * inverse(Transform) ist Identität
[ ] Forward Kinematics stimmt für bekannte Gelenkwinkel
[ ] numerischer und analytischer Jacobian stimmen überein
[ ] Gelenkgrenzen werden niemals überschritten
[ ] Reset ist deterministisch
[ ] Simulation bleibt unter Gravitation stabil
[ ] Kollision wird erkannt
[ ] Python erhält gültige finite Werte
[ ] keine NaN- oder Infinity-Werte nach einem Simulationsschritt
```

# Übergabepunkt: Linear Algebra

Scalar, Vector und die Matrix-Basis sind fertiggestellt. `Matrix6` bleibt
bewusst offen. Der nächste eigene Bereich beginnt hier:

```text
1. linear_algebra/Norms.h/.cpp
2. linear_algebra/LinearSystem.h/.cpp
3. linear_algebra/LU.h/.cpp
4. linear_algebra/QR.h/.cpp
5. linear_algebra/SVD.h/.cpp
6. linear_algebra/PseudoInverse.h/.cpp
```

Dabei sollen die Basisoperationen in `VectorN` und `MatrixN` nicht dupliziert
werden. `linear_algebra` ergänzt Algorithmen wie Solver, Zerlegungen und
Pseudoinversen auf Basis der fertigen Scalar-, Vector- und Matrixklassen.