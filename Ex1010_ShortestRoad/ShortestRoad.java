import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class ShortestRoad {
    public static void main(String[] args) {
        ArrayList<GraphWithCoordinate> graphs = new ArrayList<>();

        Scanner input = new Scanner(System.in);

        while (input.hasNextInt()) {
            int vexNum = input.nextInt();
            int arcNum = input.nextInt();

            GraphWithCoordinate graph
                    = new GraphWithCoordinate(vexNum, true);

            for (int i = 1; i <= vexNum; i++) {
                Coordinate c = new Coordinate(
                        input.nextDouble(), input.nextDouble());
                graph.setVertex(i, c);
            }

            for (int i = 1; i <= arcNum; i++) {
                int m = input.nextInt();
                int n = input.nextInt();
                graph.addArc(m, n);
            }

            graphs.add(graph);
        }

        System.out.println();
        System.out.println("Output:");

        for (GraphWithCoordinate g: graphs) {
            double roadLength = g.getShortestRoad(1);
            if (roadLength < 0) {
                System.out.println("NO");
            }
            else {
                System.out.printf("%.2f\n", roadLength);
            }
        }
    }
}

class Coordinate
{
    double x;
    double y;

    public Coordinate(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double euclidDistance(Coordinate c) {
        if (c == null) {
            throw new NullPointerException();
        }

        double deltaX = this.x - c.x;
        double deltaY = this.y - c.y;
        return Math.sqrt(deltaX * deltaX + deltaY * deltaY);
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
    private E[] vertexes;

    // Use double as WeightType
    // Weight of arcs
    private double[][] arcs;

    // The constant to represent no arc
    public final static double INF = Double.MAX_VALUE;

    // Default to construct an undirected graph
    public MyGraph(int vexNum) {
        this(vexNum, false);
    }

    public MyGraph(int vexNum, boolean directed) {
        this.vexNum = vexNum;
        this.arcNum = 0;
        this.directed = directed;

        makeEmpty();
    }

    @SuppressWarnings("unchecked")
    public void makeEmpty() {
        vertexes = (E[])new Object[vexNum];
        arcs = new double[vexNum][vexNum];

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

    // If the given does not start from 0
    private static int modifyIndex(int index) {
        return index - 1;
    }

    // Check if the index is legal
    protected void checkIndex(int m) {
        m = modifyIndex(m);
        if (m >= vexNum || m < 0) {
            throw new IndexOutOfBoundsException(
                    "Vertex index out of range.");
        }
    }

    // Check if the indices of arc is legal
    protected void checkArcIndex(int m, int n) {
        checkIndex(m);
        checkIndex(n);

        m = modifyIndex(m);
        n = modifyIndex(n);

        if (m == n) {
            throw new IllegalArgumentException(
                    "The arc cannot connect between the same vertex.");
        }
    }

    // Set the data of vertex, return the current value
    public E setVertex(int index, E data) {
        checkIndex(index);
        index = modifyIndex(index);

        E current = vertexes[index];
        vertexes[index] = data;
        return current;
    }

    // Get the data of vertex
    public E getVertex(int index) {
        checkIndex(index);
        index = modifyIndex(index);
        return vertexes[index];
    }

    // Get weight of arc from m to n
    public double getArcWeight(int m, int n) {
        checkArcIndex(m, n);
        m = modifyIndex(m);
        n = modifyIndex(n);
        return arcs[m][n];
    }

    // Set the weight of arc from m to n, return the current value
    public double setArcWeight(int m, int n, double weight) {
        checkArcIndex(m, n);
        m = modifyIndex(m);
        n = modifyIndex(n);

        if (arcs[m][n] == INF) {
            arcNum++;
        }

        double current = arcs[m][n];

        arcs[m][n] = weight;

        // For undirected graph
        if (!isDirected()) {
            arcs[n][m] = weight;
        }

        return current;
    }

    // Remove arc from m to n
    public double removeArc(int m, int n) {
        checkArcIndex(m, n);
        m = modifyIndex(m);
        n = modifyIndex(n);

        if (arcs[m][n] != INF) {
            arcNum--;
        }

        double current = arcs[m][n];

        arcs[m][n] = INF;

        // For undirected graph
        if (!isDirected()) {
            arcs[n][m] = INF;
        }

        return current;
    }

    // Show the adjacent matrix
    public void showAdjMatrix() {
        for (double[] i : arcs){
            for (double j : i){
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
}

class GraphWithCoordinate extends MyGraph<Coordinate> {
    public GraphWithCoordinate(int vexNum) {
        this(vexNum, false);
    }

    public GraphWithCoordinate(int vexNum, boolean directed) {
        super(vexNum, directed);
    }

    public double getDistance(int m, int n) {
        return getVertex(m).euclidDistance(getVertex(n));
    }

    public double addArc(int m, int n) {
        return super.setArcWeight(m, n, getDistance(m, n));
    }

    public double getShortestRoad(int indexStart) {
        checkIndex(indexStart);

        double roadLength = 0.0;
        boolean[] known = new boolean[getVertexNum()];

        known[indexStart - 1] = true;

        // Minimun distance to start point
        double[] minDist = new double[getVertexNum()];
        // Length of last step to this point
        // (Length of new road needed to be built)
        double[] lastDist = new double[getVertexNum()];

        for (int i = 1; i <= getVertexNum(); i++) {
            lastDist[i - 1] = minDist[i - 1]
                    = indexStart != i
                    ? getArcWeight(indexStart, i) : 0.0;
        }

        while (true) {
            int vertexShortest = -1;
            double weightShortest = INF;

            // Get the shortest unknown vertex
            for (int i = 1; i <= getVertexNum(); i++) {
                if (known[i - 1]) {
                    continue;
                }

                if (minDist[i - 1] < weightShortest) {
                    vertexShortest = i;
                    weightShortest = minDist[i - 1];
                }
            }

            // No unknown accessible vertex
            if (vertexShortest == -1) {
                for (boolean k : known) {
                    // Found vertex inaccessible
                    if (!k) {
                        return -1.0;
                    }
                }

                return roadLength;
            }

            known[vertexShortest - 1] = true;
            roadLength += lastDist[vertexShortest - 1];

            // Update minDist and lastDist
            for (int j = 1; j <= getVertexNum(); j++) {
                if (known[j - 1]) {
                    continue;
                }

                if (getArcWeight(vertexShortest, j) == INF) {
                    continue;
                }

                if (weightShortest + getArcWeight(vertexShortest, j)
                        < minDist[j - 1]) {
                    minDist[j - 1] = weightShortest
                            + getArcWeight(vertexShortest, j);
                    lastDist[j - 1] = getArcWeight(vertexShortest, j);
                }
            }
        }
    }
}
