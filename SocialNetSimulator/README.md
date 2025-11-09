#  COL106: SocialNet Simulator

This project is a command-line simulator for a social network's backend. It manages users, friendships, and posts using custom-built Graph and AVL Tree data structures.

## Project Structure

- `.hpp` (Headers) : `Post.hpp`, `User.hpp`, `AVLTree.hpp`, `SocialNet.hpp`, `utils.hpp`.
- `.cpp` (Impelementation) : `AVLTree.cpp`, `SocialNet.cpp`, `main.cpp`.
- `compile.sh` : The build script.
- `README.md` : This file.

## How to Compile and Run (from Terminal)

These instructions assume you are on a Linux or macOS environment with g++ and git installed.

### 1. Clone the Repository

First, clone the project from its Git repository to your local machine.
```
git clone <your-repo-url>
cd SocialNet-Simulator 
```
### 2. Make the Compile Script Executable

After cloning, you must give the shell script "execute" permissions.
```
chmod +x compile.sh
```
### 3. Compile the Project

Run the compile script. This will create an executable file named `SocialNet`.
```
./compile.sh
```

### 4. Running the Program

Run the compiled executable:
```
./SocialNet
```
The program will wait for you to enter commands from standard input.
### For running Random Testcases

Execute the below lines in the terminal
```
python3 socialnet_test.py
Get-Content input.txt | ./SocialNet.exe > output.txt
```
- Input generated is stored in `input.txt`.
- The output will be stored in/written to `output.txt`.
## Supported Commands

### Social Network Operations

- `ADD_USER <username>` : Adds a new user to the network (No friends and posts). Usernames are single words and are case-insensitive.

- `ADD_FRIEND <username1> <username2>` : Establishes a bidirectional friendship between two existing users.

- `LIST_FRIENDS <username>` : Prints an alphabetically sorted list of the specified user's friends, each on a new line.

- `DEGREES_OF_SEPARATION <username1> <username2>` : Calculates and prints the shortest path of friendships (e.g., "6 degrees of separation"). Prints -1 if no path exists.

- `SUGGEST_FRIENDS <username> <N>` : Recommends up to N new friends. Recommendations are "friends of a friend" and are ranked by mutual friend count (descending), then by username (alphabetical). If N is 0, output is nothing. If fewer than N candidates exist, all available candidates are listed.

### User Content Operations

- `ADD_POST <username> <post_content...>` : Adds a post for the specified user. The content is everything after the username. Post content is case-insensitive.

- `OUTPUT_POSTS <username> <N>` : Outputs the most recent N posts for the user, in reverse chronological order. If N is -1, it outputs all posts.

## Exiting

To stop the program, send an End-of-File (EOF) signal:

- On Linux/macOS: `Ctrl+D`

- On Windows: `Ctrl+Z then Enter`