# Bitboard Chess Engine

## Features

- **Bitboard Representation** – Fast move generation and board manipulation using 64-bit integers.  
- **Move Generation** – Legal and pseudo-legal moves for all pieces.  
- **Negamax Search** – Implements the negamax variant of minimax with alpha-beta pruning.  
- **Quiescence Search** – Extends leaf nodes to reduce the horizon effect.  
- **Move Ordering** – Includes killer moves, history heuristics, and principal variation (PV) search.  
- **Evaluation Function** – Basic material + positional evaluation (can be extended).  
- **UCI Protocol** – Communicates with GUIs like **Arena**, **CuteChess**, or **lichess-bot**.  
- **Perft Testing** – Verify correctness of move generation.  

## Build Instructions
### Requirements
- GCC compiller
- make tool for reading and executing the makefile

### Compile
Clone the repo
```bash
git clone https://github.com/boce1/bitboard-chess.git
cd bitboard-chess
```

To run the "release" version of the chess bot
```bash
make
./bin/bitboard_chess_release
```

For debug
```bash
make debug
./bin/bitboard_chess_debug
```

## Credits
1. This project is inspired by and follows the tutorial series from Maksim Korzh.

Youtube series: https://youtube.com/playlist?list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs&si=Sd3jy2bCRtksQ3oJ

Github repo of his engine: https://github.com/maksimKorzh/bbc.git

2. Principle Variation Search by Bruce Moreland : 
https://web.archive.org/web/20071030220825/http://www.brucemo.com/compchess/programming/pvs.htm#expand

3. Manimax and alpha-beta lecture - MIT OpenCourseWare : https://youtu.be/STjW3eH0Cik?si=kpKddQLv2FGQYds4

4. Minimax and alpha-beta pruning algortyhm - Sebastian Lague : https://www.youtube.com/watch?v=l-hh51ncgDI


## Running the engine
This engine works with UCI protocol and every GUI that supports UCI can start the bot. The most popular GUI for chess engines are:
- Arena
- Lucas Chess
- Tarrasch
- Cute Chess

