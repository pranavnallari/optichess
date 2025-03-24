# Optichess

Optichess is an advanced chess engine written in C. It is designed to be both efficient and straightforward, featuring modern search techniques and evaluation strategies to provide strong play and competitive performance.

## Features

- **Alpha Beta Search:**  
  Implements an optimized alpha-beta pruning algorithm to efficiently evaluate the game tree and discard branches that won’t affect the final decision.

- **Iterative Deepening:**  
  Gradually increases search depth, allowing early move selection and improved time management. This technique helps in finding good moves quickly while enabling deeper analysis when time permits.

- **Quiescence Search:**  
  Extends the search at volatile positions to avoid the horizon effect. This ensures that evaluations are not skewed by unstable positions with many captures or tactical sequences.

- **Transposition Table:**  
  Uses a transposition table to store and retrieve previously evaluated positions, reducing redundant calculations and speeding up the search process.

- **Always Replace:**  
  Implements an "always replace" strategy in the transposition table to simplify management and ensure the latest evaluation is used.

- **Polyglot Opening Books:**  
  Supports Polyglot opening books to leverage a vast repository of established opening moves, ensuring a strong start by referencing pre-computed lines.

- **MVV/LVA Move Ordering:**  
  Uses the Most Valuable Victim/Least Valuable Attacker heuristic to prioritize moves, enhancing search efficiency by considering the most promising moves first.

- **Basic Evaluation:**  
  Incorporates a fundamental evaluation function that assesses board positions based on material balance and positional factors, guiding the engine towards optimal decisions.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC)
- Make (optional, if a Makefile is provided)
- Polyglot opening book files (optional for enhanced opening play)

### Compilation

To compile Optichess, simply run:

```bash
make run
```

and to run the program :
```bash
./optichess
```

## Usage
Optichess supports standard UCI commands. To integrate with a chess GUI:

Launch the GUI.

Add Optichess as a UCI engine.

Configure the engine settings as desired, such as time controls and search parameters.

Enjoy a challenging game of chess!

