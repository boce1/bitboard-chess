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
- **Principle variation search** - Improves the performance up to 10%

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

## References
1. This project is inspired by and follows the tutorial series from Maksim Korzh.

Youtube series: https://youtube.com/playlist?list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs&si=Sd3jy2bCRtksQ3oJ

Github repo of his engine: https://github.com/maksimKorzh/bbc.git

2. Principle Variation Search by Bruce Moreland : 
https://web.archive.org/web/20071030220825/http://www.brucemo.com/compchess/programming/pvs.htm#expand

3. Manimax and alpha-beta lecture - MIT OpenCourseWare : https://youtu.be/STjW3eH0Cik?si=kpKddQLv2FGQYds4

4. Minimax and alpha-beta pruning algortyhm - Sebastian Lague : https://www.youtube.com/watch?v=l-hh51ncgDI

5. Magic numbers and magic bitboard for move generation

TimosPal, repo: https://github.com/TimosPal/NNUE-Bitboard-Chess-Engine

Chess programming wiki : https://www.chessprogramming.org/Magic_Bitboards

## Running the engine
This engine works with UCI protocol and every GUI that supports UCI can start the bot. The most popular GUI for chess engines are:
- Arena
- Lucas Chess
- Tarrasch
- Cute Chess

### For windows
To play this engine just load ```bitboard_chess_release.exe```.
### For Unix based OS
Executable ```bitboard_chess_release.exe``` in the ```bin``` folder is only Windows compatable. For Unix systems the program needs to be compiled and then loaded in a GUI. Instructions are in [Build Instructions](#build-instructions) section.

# Bitboards
Bitboards (also called bitmaps) are unsigned 64-bit integers. They are used to represent the state of the board. This method offers great computational speed because bitboard can be manipulated with binary operation. Modern computers are 64-bit arhitectures wich allows ussability of 64 bit registers. Binary operations with 64bit registers are much faster than the standard 2d representation of the board.

# Board
Board is a structure that contains occupancy of all 12 pieces (pawn, rook, knight, bishop, queen. king for black and white), occupancies for white and black pieces and occupancy of all pieces of the board. The occupancies are represented as bitboards. Board also contains variables for wich side is to move, en passant sqaure and castling rights.

# Move generation
For move generation there's two move categories: pseudo moves and legal moves. A pseudo move is a move that is legal if we leave the fact that the move might make the king in check or let the king be checked. Legal move is a move that doesn't allow the king to be in check position. Algorithm first generates the pseudo moves then it filtrates them afterwards. All the attacks are pre-generated at startup. This way getting the pseudo moves is faster because theres no need to calculate them on the fly. Exception in this implementation are pawn pushes and king castles. They are being calculated on the fly.

In context of generating moves there's two types of pieces: 
- leaper pieces (pawns, king, knight)
- slider pieces (rook, bishop, queen)


 