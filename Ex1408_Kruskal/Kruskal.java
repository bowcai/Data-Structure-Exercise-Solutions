import java.util.LinkedList;
import java.util.Arrays;
import java.util.Comparator;

public class Kruskal {
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

        System.out.println("\nMinimum Spanning Tree:");
        graph.kruskal().showAdjMatrix();
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

    // Use int as WeightType
    // Weight of arcs
    private int[][] arcs;

    // The constant to represent no arc
    public final static int INF = Integer.MAX_VALUE;

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
        arcs = new int[vexNum][vexNum];

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

    public static class Arc {
        public int m;
        public int n;
        public int weight;

        public Arc(int m, int n, int weight) {
            this.m = m;
            this.n = n;
            this.weight = weight;
        }
    }

    public MyGraph<E> kruskal() {
        if (isDirected()) {
            throw new IllegalArgumentException(
                    "This method only applies to undirected graph");
        }
        MyGraph<E> minSpan = new MyGraph<>(getVertexNum());
        int edgeAccepted = 0;

        LinkedList<Arc> allEdges = new LinkedList<>();
        int[] conComponent = new int[getVertexNum()];
        for (int i = 0; i < conComponent.length; i++) {
            conComponent[i] = i;
        }

        for (int i = 0; i < getVertexNum(); i++) {
            for (int j = i + 1; j < getVertexNum(); j++) {
                if (getArcWeight(i, j) != INF) {
                    allEdges.add(new Arc(i, j, getArcWeight(i, j)));
                }
            }
        }

        allEdges.sort(Comparator.comparingInt(e -> e.weight));

        while (edgeAccepted < getVertexNum() - 1) {
            if (allEdges.isEmpty()) {
                throw new IllegalArgumentException(
                        "Number of edges are not enough");
            }

            Arc arc = allEdges.removeFirst();

            // Accept the edge
            if (conComponent[arc.m] != conComponent[arc.n]) {
                minSpan.setArcWeight(arc.m, arc.n, arc.weight);
                edgeAccepted++;

                for (int i = 0; i < getVertexNum(); i++) {
                    if (i == arc.n) {
                        continue;
                    }
                    if (conComponent[i] == conComponent[arc.n]) {
                        conComponent[i] = conComponent[arc.m];
                    }
                }
                conComponent[arc.n] = conComponent[arc.m];
            }
        }

        return minSpan;
    }
}
