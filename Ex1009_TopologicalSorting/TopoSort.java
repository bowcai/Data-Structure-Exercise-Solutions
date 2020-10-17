import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class TopoSort {
    public static void main(String[] args) {
        AdjList<Integer> graph = new AdjList<>(
                new Integer[]{0,1,2,3,4,5,6}, true);

        graph.addArc(0, 1);
        graph.addArc(0, 2);
        graph.addArc(0, 3);
        graph.addArc(1, 3);
        graph.addArc(1, 4);
        graph.addArc(2, 5);
        graph.addArc(3, 2);
        graph.addArc(3, 5);
        graph.addArc(3, 6);
        graph.addArc(4, 3);
        graph.addArc(4, 6);
        graph.addArc(6, 5);

        int[] topoVertex = graph.topoSort();

        for (int i: topoVertex) {
            System.out.print(i + " ");
        }
        System.out.println();
    }
}


// Graph with Adjacent List
class AdjList<E> {
    protected static class Arc {
        private final int adjVex;
        private Arc next;

        public Arc(int adjVex, Arc next) {
            this.adjVex = adjVex;
            this.next = next;
        }
    }

    protected static class Vertex<E> {
        public E data;
        public Arc arcsHead;

        // For topological sorting of directed graph
        public int outDegree = 0;
        public int inDegree = 0;

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

    protected Vertex<E> getVertex(int index) {
        return vertexes.get(index);
    }

    public void addArc(int m, int n) {
        checkArcIndex(m, n);

        Arc temp = getVertex(m).arcsHead.next;

        while (temp != null) {
            if (temp.adjVex == n) {
                System.err.println("The arc has already been added.");
                return;
            }
            temp = temp.next;
        }

        getVertex(m).arcsHead.next
                = new Arc(n, getVertex(m).arcsHead.next);

        getVertex(m).outDegree++;
        getVertex(n).inDegree++;

        if (!isDirected()) {
            getVertex(n).arcsHead.next
                    = new Arc(m, getVertex(n).arcsHead.next);
            getVertex(n).outDegree++;
            getVertex(m).inDegree++;
        }

        arcNum++;
    }

    // Remove an arc from directed graph
    private void removeArcDirected(int m, int n) {
        checkArcIndex(m, n);

        Arc temp = getVertex(m).arcsHead;
        while (temp.next != null) {
            if (temp.next.adjVex == n) {
                Arc former = temp.next;
                temp.next = temp.next.next;
                former.next = null;

                getVertex(m).outDegree--;
                getVertex(n).inDegree--;

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

    public int[] topoSort() {
        if (!isDirected()) {
            throw new IllegalArgumentException(
                    "Topological sort only applies to directed graph.");
        }
        int[] inDegreeCopy = new int[getVexNum()];

        for (int i = 0; i < getVexNum(); i++) {
            inDegreeCopy[i] = getVertex(i).inDegree;
        }

        Queue<Integer> vertexQueue = new LinkedList<>();
        int counter = 0;
        int[] topoVertexes = new int[getVexNum()];

        for (int i = 0; i < getVexNum(); i++) {
            if (inDegreeCopy[i] == 0) {
                vertexQueue.offer(i);
            }
        }

        while (!vertexQueue.isEmpty()) {
            int v = vertexQueue.remove();
            topoVertexes[counter] = v;
            counter++;

            Arc arc = getVertex(v).arcsHead.next;

            while (arc != null) {
                inDegreeCopy[arc.adjVex]--;
                if (inDegreeCopy[arc.adjVex] == 0) {
                    vertexQueue.offer(arc.adjVex);
                }

                arc = arc.next;
            }
        }

        if (counter != getVexNum()) {
            throw new IllegalArgumentException(
                    "Graph has a cycle.");
        }

        return topoVertexes;
    }
}
