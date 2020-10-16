import java.util.Arrays;
import java.util.Stack;

public class BreakingCircle {
    public static void main(String[] args) {
        MyGraph<Integer> graph = new MyGraph<>(5);
        graph.setArcWeight(0, 1, 1);
        graph.setArcWeight(0, 2, 2);
        graph.setArcWeight(0, 3, 3);
        graph.setArcWeight(1, 2, 3);
        graph.setArcWeight(1, 4, 1);
        graph.setArcWeight(2, 3, 2);
        graph.setArcWeight(2, 4, 2);
        graph.setArcWeight(3, 4, 1);

        System.out.println("Origin:");
        graph.showAdjMatrix();

        graph.buildMinSpan();

        System.out.println();
        System.out.println("Minimum Spanning Tree:");
        graph.showAdjMatrix();
    }
}

// Graph with adjacent matrix
class MyGraph<E> {
    // Number of vertexes, set when construct
    private final int vexNum;

    // Number of arcs
    private int arcNum;

    // The graph is directed or not
    private final boolean directed;

    // Data for all vertexes
    private final E[] vertexes;

    // Use int as WeightType
    // Weight of arcs
    private final int[][] arcs;

    // The constant to represent no arc
    public final static int INF = Integer.MAX_VALUE;

    // Default to construct an undirected graph
    public MyGraph(int vexNum) {
        this(vexNum, false);
    }

    @SuppressWarnings("unchecked")
    public MyGraph(int vexNum, boolean directed) {
        this.vexNum = vexNum;
        this.arcNum = 0;
        this.vertexes = (E[])new Object[vexNum];
        this.arcs = new int[vexNum][vexNum];
        this.directed = directed;

        for (int i = 0; i < vexNum; i++) {
            Arrays.fill(arcs[i], INF);
            arcs[i][i] = 0;
        }
    }

    public int getVertexNum() {
        return vexNum;
    }

    public int getArcNum() {
        return arcNum;
    }

    public boolean isDirected() {
        return directed;
    }

    // Check if the index is legal
    public void checkIndex(int m) {
        if (m >= vexNum || m < 0) {
            throw new IndexOutOfBoundsException(
                    "Vertex index out of range.");
        }
    }

    // Check if the indices of arc is legal
    public void checkArcIndex(int m, int n) {
        checkIndex(m);
        checkIndex(n);
        if (m == n) {
            throw new IllegalArgumentException(
                    "The arc cannot connect between the same vertex.");
        }
    }

    // Set the data of vertex, return the current value
    public E setVertex(int index, E data) {
        checkIndex(index);

        E current = vertexes[index];
        vertexes[index] = data;
        return current;
    }

    // Get the data of vertex
    public E getVertex(int index) {
        checkIndex(index);
        return vertexes[index];
    }

    // Get weight of arc from m to n
    public int getArcWeight(int m, int n) {
        checkArcIndex(m, n);
        return arcs[m][n];
    }

    // Set the weight of arc from m to n, return the current value
    public int setArcWeight(int m, int n, int weight) {
        checkArcIndex(m, n);

        if (arcs[m][n] == INF) {
            arcNum++;
        }

        int current = arcs[m][n];

        arcs[m][n] = weight;

        // For undirected graph
        if (!isDirected()) {
            arcs[n][m] = weight;
        }

        return current;
    }

    // Remove arc from m to n
    public int removeArc(int m, int n) {
        checkArcIndex(m, n);

        if (arcs[m][n] != INF) {
            arcNum--;
        }

        int current = arcs[m][n];

        arcs[m][n] = INF;

        // For undirected graph
        if (!isDirected()) {
            arcs[n][m] = INF;
        }

        return current;
    }

    // Show the adjacent matrix
    public void showAdjMatrix() {
        for (int[] i : arcs){
            for (int j : i){
                if (j == INF) {
                    System.out.print("INF");
                }
                else {
                    System.out.print(j);
                }
                System.out.print("\t");
            }
            System.out.println();
        }
    }

    // DFS for breaking the cycle
    private int breakDFS(int k, int former
            , boolean[] visited, Stack<Integer> path) {
        // Set the current point as visited and record it into path
        visited[k] = true;
        path.push(k);

        for (int i = 0; i < getVertexNum(); i++) {
            // The arc between current vertex and former vertex
            // cannot form a circle
            if (i == k || i == former) {
                continue;
            }

            // Check all the connected vertex
            if (getArcWeight(k, i) != INF) {
                // If one of the connected vertex has been visited,
                // then there is a cycle
                // return the start vertex of the cycle
                if (visited[i]) {
                    path.push(i);
                    return i;
                }

                // If the connected vertex has not been visited,
                // then continue the DFS
                else {
                    int rslt = breakDFS(i, k, visited, path);

                    // If the deeper DFS finds a cycle,
                    // then continue to return the result
                    if (rslt != -1) {
                        return rslt;
                    }
                }
            }
        }

        // When all the connected vertex cannot find a cycle,
        // return -1 as fail to find a cycle
        return -1;
    }

    // Break a cycle (only apply to undirected graph)
    // The method will remove arcs from the original graph
    private boolean breakCycle() {
        if (isDirected()) {
            throw new IllegalArgumentException(
                    "Method only apply to undirected graph.");
        }

        // There will not be cycles if vexNum<=2
        if (getVertexNum() <= 2) {
            return false;
        }

        // Record the visited vertexes and the path of cycle
        boolean[] visited = new boolean[getVertexNum()];

        Stack<Integer> path = new Stack<>();

        // Try all the start vertex
        for (int i = 0; i < getVertexNum(); i++) {
            // Skip the visited vertex which cannot find a cycle
            if (!visited[i]) {
                // Start the DFS (-1 means no former vertex)
                int rslt = breakDFS(i, -1, visited, path);

                // If a cycle is found, then process the cycle
                if (rslt != -1) {
                    // Check the path and find the maximum weight
                    int former = path.pop();
                    int current, m = -1, n = -1;
                    int maxWeight = 0;
                    while (!path.empty()) {
                        current = path.pop();
                        if (getArcWeight(current, former) > maxWeight) {
                            maxWeight = getArcWeight(current, former);

                            // Record the vertexes of maximum weight arc
                            m = current;
                            n = former;
                        }

                        // Reach the start point of the cycle
                        if (current == rslt) {
                            break;
                        }

                        former = current;
                    }

                    // Delete the arc with maximum weight
                    removeArc(m, n);

                    // Find a cycle
                    return true;
                }
            }
        }

        // No cycle found
        return false;
    }

    // Build the minimum spanning tree on the original graph
    public void buildMinSpan() {
        if (isDirected()) {
            throw new IllegalArgumentException(
                    "Method only apply to undirected graph.");
        }
        while (breakCycle()) {
            continue;
        }
    }
}
