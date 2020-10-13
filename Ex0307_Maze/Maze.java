import java.util.Stack;

public class Maze {
    private final int xLen, yLen;

    // Probability of an open path
    private final double openProb;

    // The map of maze
    private int[][] mazeMap;

    // Record the points that have walked through
    private int[][] pass;

    // The routine using coordinate
    private Stack<Integer[]> routine = null;

    // The allowed directions
    private final int[][] directions = { {1,0}, {0,1}, {-1,0}, {0,-1} };

    // Symbols for showing the map
    private final static char[] mapSymbols = {'o', 'x', '*'};

    public Maze(int xLen, int yLen, double openProb) {
        this.xLen = xLen;
        this.yLen = yLen;
        this.openProb = openProb;
        initial();
    }

    public int randomBlock() {
        return Math.random() > openProb ? 1 : 0;
    }

    public void initial() {
        mazeMap = new int[xLen][yLen];
        pass = new int[xLen][yLen];

        for (int i = 0; i < xLen; i++) {
            for (int j = 0; j < yLen; j++) {
                mazeMap[i][j] = randomBlock();
            }
        }
        mazeMap[0][0] = 0;
        mazeMap[xLen-1][yLen-1] = 0;
    }

    public static void showMaze(int[][] mazeMap) {
        if (mazeMap == null) {
            throw new NullPointerException();
        }
        for (int[] i: mazeMap) {
            for (int j: i) {
                System.out.print(mapSymbols[j]);
                System.out.print(" ");
            }
            System.out.println();
        }
    }

    public void showMaze() {
        System.out.println("Showing the maze:");
        showMaze(mazeMap);
    }

    // Check the accessibility of next step
    private boolean canStep(int x, int y) {
        if (x < 0 || x >= xLen
                || y < 0 || y >= yLen) {
            return false;
        }

        return mazeMap[x][y] == 0 && pass[x][y] == 0;
    }

    public boolean getRoutine() {
        int x = 0, y = 0;
        int i = 0;
        routine = new Stack<>();

        // The direction of last step
        Stack<Integer> stepDirect = new Stack<>();

        routine.push(new Integer[]{ x,y });
        pass[x][y] = 1;

        // When routine is empty, there is no solution
        while (!routine.empty()) {
            // Try all the directions
            while (i < directions.length) {
                // If one direction is available, then take a step
                if (canStep(x + directions[i][0],
                        y + directions[i][1])) {
                    break;
                }
                i++;
            }

            // One direction is available
            if (i < directions.length) {
                // Take a step
                x += directions[i][0];
                y += directions[i][1];

                // This point has past
                pass[x][y] = 1;

                // Update the routine
                routine.push(new Integer[]{ x,y });

                // Record last step
                stepDirect.push(i);

                // Check if reach the exit
                if (x == xLen - 1 && y == yLen - 1) {
                    return true;
                }

                // Reset the direction and continue
                i = 0;
            }

            // No direction is available, move back a step
            else {
                // Move one step behind
                routine.pop();

                // If routine is empty, then there is no solution
                if (routine.empty()) {
                    return false;
                }

                // Retrieve last point
                pass[x][y] = 0;
                x = routine.peek()[0];
                y = routine.peek()[1];

                // Retrieve last step and continue to try other directions
                i = stepDirect.pop() + 1;
            }
        }
        return false;
    }

    // Show the result of routine
    public void showRoutine() {
        if (routine == null) {
            throw new NullPointerException(
                    "Must call method getRoutine() first");
        }
        for (Integer[] r: routine) {
            System.out.println("(" + (r[0] + 1)
                    + ", " + (r[1] + 1) + ")");
        }
    }

    // Show routine in map
    public void showMapRoutine() {
        if (routine == null) {
            throw new NullPointerException(
                    "Must call method getRoutine() first");
        }
        int[][] mazeMapCopy = new int[xLen][yLen];
        for (int i = 0; i < xLen; i++) {
            mazeMapCopy[i] = mazeMap[i].clone();
        }

        for (Integer[] r: routine) {
            mazeMapCopy[r[0]][r[1]] = 2;
        }

        System.out.println("Showing the routine in map:");
        showMaze(mazeMapCopy);
    }
}

class TestMaze {
    public static void main(String[] args) {
        final int m = 8, n = 7;
        final double prob = 0.7;
        Maze maze = new Maze(m, n, prob);
        maze.showMaze();

        if(maze.getRoutine()) {
            System.out.println("There is a solution :)");
            maze.showRoutine();
            maze.showMapRoutine();
        }
        else {
            System.out.println("There is no solution :(");
        }
    }
}
