import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class AdjListBFS {
    public static void main(String[] args) {
        AdjList<Integer> graph = new AdjList<>(
                new Integer[]{0, 1, 2, 3, 4, 5});

        graph.addArc(0, 4);
        graph.addArc(0, 3);
        graph.addArc(0, 1);
        graph.addArc(1, 5);
        graph.addArc(1, 4);
        graph.addArc(1, 2);
        graph.addArc(2, 5);
        graph.addArc(2, 4);
        graph.addArc(2, 3);
        graph.addArc(3, 4);
        graph.addArc(4, 5);

        graph.bfsPrint(5);
    }
}

// Graph with Adjacent List
class AdjList<E> {
    protected static class Arc {
        public int adjVex;
        public Arc next;

        public Arc(int adjVex, Arc next) {
            this.adjVex = adjVex;
            this.next = next;
        }
    }

    protected static class Vertex<E> {
        public E data;
        public Arc arcsHead;

        public Vertex(E data, Arc arcsHead) {
            this.data = data;
            this.arcsHead = arcsHead;
        }

        // Initialize the vertex with an head node
        public Vertex(E data) {
            this(data, new Arc(-1, null));
        }
    }

    protected ArrayList<Vertex<E>> vertexes;
    private int vexNum;
    private int arcNum;
    private final boolean directed;

    // Default to construct an empty undirected graph
    public AdjList() {
        this(false);
    }

    public AdjList(E[] array) {
        this(array, false);
    }

    public AdjList(boolean directed) {
        this(null, directed);
    }

    public AdjList(E[] array, boolean directed) {
        this.directed = directed;
        makeEmpty();
        addVertex(array);
    }

    public void makeEmpty() {
        vertexes = new ArrayList<>();
        vexNum = 0;
        arcNum = 0;
    }

    public boolean isDirected() {
        return directed;
    }

    public int getArcNum() {
        return arcNum;
    }

    public int getVexNum() {
        return vexNum;
    }

    public void checkIndex(int index) {
        if (index >= vexNum || index < 0) {
            throw new IndexOutOfBoundsException(
                    "Vertex index out of range.");
        }
    }

    public void checkArcIndex(int m, int n) {
        checkIndex(m);
        checkIndex(n);

        if (m == n) {
            throw new IllegalArgumentException(
                    "The arc cannot connect between the same vertex.");
        }
    }

    public void addVertex(E x) {
        vertexes.add(new Vertex<>(x));
        vexNum++;
    }

    public void addVertex(E[] array) {
        if (array == null) {
            return;
        }
        for (E e: array) {
            addVertex(e);
        }
    }

    public void addArc(int m, int n) {
        checkArcIndex(m, n);

        Arc temp = vertexes.get(m).arcsHead.next;

        while (temp != null) {
            if (temp.adjVex == n) {
                System.err.println("The arc has already been added.");
                return;
            }
            temp = temp.next;
        }

        vertexes.get(m).arcsHead.next
                = new Arc(n, vertexes.get(m).arcsHead.next);

        if (!isDirected()) {
            vertexes.get(n).arcsHead.next
                    = new Arc(m, vertexes.get(n).arcsHead.next);
        }

        arcNum++;
    }

    // Remove an arc from directed graph
    private void removeArcDirected(int m, int n) {
        checkArcIndex(m, n);

        Arc temp = vertexes.get(m).arcsHead;
        while (temp.next != null) {
            if (temp.next.adjVex == n) {
                Arc former = temp.next;
                temp.next = temp.next.next;
                former.next = null;

                // Add code here if you want
                // to do something with former arc

                return;
            }
        }

        System.err.println("The arc has not been added");
    }

    public void removeArc(int m, int n) {
        removeArcDirected(m, n);
        if (!isDirected()) {
            removeArcDirected(n, m);
        }
    }

    // k is the begin vertex
    public void bfsPrint(int k) {
        checkIndex(k);

        boolean[] visited = new boolean[vexNum];

        Queue<Integer> queue = new LinkedList<>();
        queue.offer(k);
        visited[k] = true;

        while (!queue.isEmpty()) {
            int current = queue.remove();

            System.out.print(vertexes.get(current).data + " ");

            Arc temp = vertexes.get(current).arcsHead.next;
            while (temp != null) {
                if (!visited[temp.adjVex]) {
                    queue.offer(temp.adjVex);
                    visited[temp.adjVex] = true;
                }
                temp = temp.next;
            }
        }
        System.out.println();
    }
}
