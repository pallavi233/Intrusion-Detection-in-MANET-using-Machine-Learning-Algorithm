# Intrusion-Detection-in-MANET-using-Machine-Learning-Algorithm

# Intrusion and Selfish Node Attack Simulation (NS-2)

## Project Overview
This project demonstrates network attack simulations using **NS-2 (Network Simulator-2)**.  
It is an academic simulation project designed to study how different types of malicious
or non-cooperative nodes affect overall decentralize network performance.

The repository contains **two different attack models** implemented for comparison:
- Selfish Node Attack
- Intrusion Attack


## Project Structure

intrusion_attack/
├── selfish_attack/
│   ├── main.tcl
│   ├── project.tcl
│   ├── trafficr
│   ├── perl_script.pl
│   └── thr.awk
│
├── intrusion_attack/
│   ├── main.tcl
│   ├── project.tcl
│   ├── trafficr
│   ├── perl_script.pl
│   └── thr.awk
│
├── README.md
└── .gitignore

---

## Attack Models Description

### 1. Selfish Node Attack
In this model, a node behaves selfishly by refusing to forward packets for other nodes
while still sending its own data.

Effects on the network:
- Reduced throughput
- Increased packet loss
- Degradation in overall network performance

This model is commonly used in ad-hoc and wireless sensor network studies.

---

### 2. Intrusion Attack
In this model, a malicious node actively disrupts the network by dropping or manipulating packets.

Effects on the network:
- Increased delay
- Reduced packet delivery ratio
- Network instability

This model helps in understanding intrusion behavior and its impact on routing performance.

---

## Technologies Used
- NS-2 (Network Simulator-2)
- TCL scripting language
- AWK and Perl for result analysis
- Ubuntu Linux (recommended)

---

## How to Run the Project (Beginner Friendly)

### Prerequisites
- Ubuntu Linux
- NS-2 and NAM installed

Install required tools:
sudo apt update
sudo apt install ns2 nam

Check installation:
ns

---

### Run Selfish Node Attack
cd Documents/intrusion_attack/selfish_attack
ns main.tcl
nam out.nam

---

### Run Intrusion Attack
cd Documents/intrusion_attack/intrusion_attack
ns main.tcl
nam out.nam

An animation window will open showing node communication and attack behavior.

---

## Output Files
After running the simulation, the following files are generated automatically:
- out.tr  → Trace file containing network events
- out.nam → Animation file for visual simulation

Optional performance analysis:
awk -f thr.awk out.tr

---

## Security Notice
All cryptographic key files (such as .pem files) are intentionally excluded from this
repository for security reasons. This project is for academic and simulation purposes only.

---

## Academic Use
This project can be used for:
- Final-year engineering projects
- Network security demonstrations
- Cybersecurity learning portfolios
- Simulation-based research studies

---

## Short Project Explanation
This project simulates selfish and intrusion attacks in a network using NS-2 and analyzes
their impact on decentralize network performance metrics such as throughput, delay, and packet loss.

---

## License
This project is intended for educational and learning purposes only.
