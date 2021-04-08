maze1 = [[0, 0, 0, 0, 0, 0, 0, 0],
         [0, 0, 0, 0, 1, 1, 0, 0],
         [1, 1, 0, 0, 0, 0, 1, 0],
         [0, 0, 0, 0, 1, 0, 0, 0],
         [0, 0, 1, 1, 0, 0, 1, 0],
         [0, 1, 0, 0, 0, 0, 1, 0],
         [0, 0, 0, 0, 1, 1, 0, 1],
         [0, 0, 1, 0, 0, 0, 0, 0]]

maze2 = [[0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1],
         [0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1],
         [0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1],
         [0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1],
         [0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1],
         [1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1],
         [1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0],
         [0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0],
         [0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0],
         [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0],
         [0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0],
         [0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1],
         [0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0],
         [0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0],
         [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0],
         [0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0],]

moves = [(-1, 0), (0, 1), (1, 0), (0, -1)]

"""
This function recursively solves a 2D maze of ones and zeros.

Inputs:
    arr_2d, a 2D array of zeros and ones resembling a maze. Examples above.
    pos, a tuple of ints with a row and column current/starting position.
    visited, a list of positions described above of where the function has visited.

Output:
    An int of the fewest amount of steps to get from the current position to the
    bottom left corner of the maze.
"""
def solve_maze(arr_2d, pos=(0, 0), visited=[]):

    if pos == (len(arr_2d) - 1, len(arr_2d[0]) - 1):
        return 0

    possible_moves = check_surroundings(arr_2d, pos, visited)

    min_dist = -1
    for i in range(4):
        if possible_moves[i] == 1:
            continue  #           ///           position tuple             ///
        dist = solve_maze(arr_2d, (pos[0] + moves[i][0], pos[1] + moves[i][1]), visited + [pos])
        if dist == -1:
            continue
        if min_dist == -1 or dist < min_dist:
            min_dist = dist

    if min_dist == -1:
        return -1
    return min_dist + 1





"""
This function takes in a 2d maze and a position tuple (row, col), and returns a
list of four ints saying if the positions to the left, right, up, and down are
ones or zeros.

Input:
    arr_2d, a 2D array of zeros and ones resembling a maze.
    pos, a tuple of ints with a row and column current/starting position.
    visited, a list of positions described above of where the function has visited.

Output:
    An array of length 4 of ones and zeros representing the state of the maze in
    the cardinal directions from the input position (in the form [up, right, down, left]).
"""
def check_surroundings(arr_2d, pos, visited):
    output = [0, 0, 0, 0]

    # up
    if pos[0] == 0:
        output[0] = 1
    elif visited.count((pos[0] - 1, pos[1])) > 0:
        output[0] = 1
    else:
        output[0] = arr_2d[pos[0] - 1][pos[1]]

    # right
    if pos[1] == len(arr_2d[0]) - 1:
        output[1] = 1
    elif visited.count((pos[0], pos[1] + 1)) > 0:
        output[1] = 1
    else:
        output[1] = arr_2d[pos[0]][pos[1] + 1]

    # down
    if pos[0] == len(arr_2d) - 1:
        output[2] = 1
    elif visited.count((pos[0] + 1, pos[1])) > 0:
        output[2] = 1
    else:
        output[2] = arr_2d[pos[0] + 1][pos[1]]

    # left
    if pos[1] == 0:
        output[3] = 1
    elif visited.count((pos[0], pos[1] - 1)) > 0:
        output[3] = 1
    else:
        output[3] = arr_2d[pos[0]][pos[1] - 1]

    return output

print(solve_maze(maze1))