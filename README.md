# tictactoeAI
This repository contains a C++ implementation of Tic Tac Toe, along with simple AI agents (a purely random player and an evolutionary-trained two-layer linear network). 
It demonstrates game logic, AI decision-making, evolutionary machine learning, and performance evaluation.

---

## Table of Contents

- [Overview](#overview)  
- [File Structure](#file-structure)  
- [Getting Started](#getting-started)  
- [Executables](#executables)  
- [Neural Network Architecture](#neural-network-architecture)  
- [Training Method](#training-method)  
- [Evaluation](#evaluation)  
- [Usage](#usage)

---

## Overview

The project is organized as a learning-focused lab. It progresses in stages:

1. **Base game logic** – defines the board, moves, win/tie conditions.
2. **Random agent** – baseline AI for testing and comparison.
3. **Linear “neural” agent** – two-layer linear network with no activation functions.
4. **Evolutionary training** – trains the network via self-play and mutation.
5. **Evaluation and interactive play** – test the trained AI against humans or random players.

---

## File Structure
.
├── tictactoe.h / tictactoe.cpp # Core game logic
├── weightsManager.h / weightsManager.cpp # Linear network operations and weight management
├── basegame_playable.cpp # Human vs human terminal game
├── random_player.cpp # Random AI plays alone
├── main.cpp # Training loop and post-training human vs AI play
├── play_v_AI.cpp # Standalone human vs trained or untrained AI
├── trained_v_random_auto.cpp # Automated benchmark of trained AI vs random player
├── trained_weights.txt # Example saved weights file
└── README.md

---

## Getting Started

1. Clone the repository:

```bash
git clone https://github.com/RealmWarden/tictactoeAI.git
cd tictactoeAI 
```
2. Compile the desired executable using a C++ compiler, e.g.:
```bash
g++ basegame_playable.cpp tictactoe.cpp -o basegame_playable
g++ random_player.cpp tictactoe.cpp -o random_player
g++ main.cpp tictactoe.cpp weightsManager.cpp -o main
g++ play_v_AI.cpp tictactoe.cpp weightsManager.cpp -o play_v_AI
g++ trained_v_random_auto.cpp tictactoe.cpp weightsManager.cpp -o trained_v_random_auto
```
3. Run the desired executable:
```bash
./basegame
./trainAI
./playAI
./evalAI
```

---

## Executables

# basegame_playable
- Pure human vs human Tic Tac Toe.
- Demonstrates the basic game loop, board rendering, and win/tie detection.
# random_player
- Random move AI plays by itself.
- Useful as a baseline for testing computer interface with game.
# main
- Evolves a two-layer linear network via self-play.
- Saves final weights to trained_weights.txt.
- Lets a human play against the trained AI in terminal.
# play_v_AI
- Loads weights from trained_weights.txt (or randomizes them).
- Human can play against trained or untrained AI.
- Demonstrates AI inference separate from training.
# trained_v_random_auto
- Runs automated simulations between trained AI and random AI.
- Tracks wins, losses, and ties over 1,000,000 iterations.
- Provides statistical validation of the trained AI’s performance.

---

## Neural Network Architecture
- Input layer: 10 units
    - 9 board positions encoded as x = 1, o = -1, empty = 0
    - 1 extra unit indicating whether AI goes first (1 if first, -1 if second)
- Hidden layer: 9 units (linear combination)
- Output layer: 9 units (one per board position)
- Decision: select highest value among valid moves (argmax), illegal moves filtered out
- No activation functions; purely linear.

---

## Training Method
The AI is trained via a simple evolutionary strategy:
    1. Start with a parent network with random weights.
    2. Generate a population of mutated children (controlled by creativity).
    3. Children play repeated games against the parent network.
    4. Each child is scored:
        - rewardForWin for a win
        - rewardForTie for a tie
        - rewardForLoss for a loss
    5. The best child becomes the new parent for the next generation.
    6. Repeat for numGenerations generations.
    7. Save the best network to trained_weights.txt.
Hyperparameters are configurable in main.cpp:
    - creativity – mutation magnitude
    - generationSize – number of children per generation
    - rewardForWin, rewardForTie, rewardForLoss – scoring system
    - gamesPerIndividual – number of games each child plays per generation
    - numGenerations – total generations

---

## Evaluation
- The trained AI can be benchmarked against a random player using trained_v_random_auto.
- Outputs total wins, losses, ties, and percentages.
- Demonstrates that the evolutionary strategy improves AI performance over random chance.

---

## Usage Example
# Train AI and play interactively
./trainAI
# Play against a trained AI or untrained AI
./playAI
# Run automated evaluation
./evalAI

---

## Notes
- Board positions are numbered 1–9, top-left to bottom-right:

1 2 3
4 5 6
7 8 9

- Random number generators are seeded with the current time for stochastic behavior.
- The network is intentionally minimal, demonstrating linear policy evolution without complex ML frameworks.
