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
        public Arc firstArc;

        public Vertex(E data, Arc firstArc) {
            this.data = data;
            this.firstArc = firstArc;
        }

        public Vertex(E data) {
            this(data, null);
        }
    }

    protected ArrayList<Vertex<E>> vertices = new ArrayList<>();
    private int vexNum = 0;
    private int arcNum = 0;

    public AdjList() {
    }

    public AdjList(E[] array) {
        this();
        if (array == null) {
            throw new NullPointerException();
        }
        for (E e: array) {
            addVertex(e);
        }
    }

    public void addVertex(E x) {
        vertices.add(new Vertex<>(x));
        vexNum++;
    }

    public void addArc(int i, int j) {
        if (i >= vexNum || j >= vexNum) {
            throw new IllegalArgumentException(
                    "Vertex index out of range.");
        }

        Arc temp = vertices.get(i).firstArc;

        while (temp != null) {
            if (temp.adjVex == j) {
                System.err.println("The arc has already been added.");
                return;
            }
            temp = temp.next;
        }

        vertices.get(i).firstArc
                = new Arc(j, vertices.get(i).firstArc);
        vertices.get(j).firstArc
                = new Arc(i, vertices.get(j).firstArc);

        arcNum++;
    }

    // k is the begin vertex
    public void bfsPrint(int k) {
        if (k >= vexNum) {
            throw new IllegalArgumentException(
                    "Vertex index out of range.");
        }

        boolean[] visited = new boolean[vexNum];

        Queue<Integer> queue = new LinkedList<>();
        queue.offer(k);
        visited[k] = true;

        while (!queue.isEmpty()) {
            int current = queue.remove();

            System.out.print(vertices.get(current).data + " ");

            Arc temp = vertices.get(current).firstArc;
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
