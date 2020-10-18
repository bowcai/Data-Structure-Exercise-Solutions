public class MergeSort {
    public static void main(String[] args) {
        MyLinkedListWithSort<Integer> list
                = new MyLinkedListWithSort<>(
                        new Integer[]{ 32,59,21,12,45,89,63
                                ,34,26,7,6,18,24,45 });

        System.out.println("Original list:");
        list.show();

        list.mergeSort();

        System.out.println("After sorting:");
        list.show();
    }
}

class MyLinkedList<E> {
    public static class Node<E> {
        public final E data;
        public Node<E> next;

        public Node(E data) {
            this(data, null);
        }

        public Node(E data, Node<E> next) {
            this.data = data;
            this.next = next;
        }

        public boolean isLast() {
            return next == null;
        }
    }

    private final Node<E> head = new Node<>(null);

    public MyLinkedList() {}

    public MyLinkedList(E[] array) {
        this();
        insertToTail(array);
    }

    public Node<E> getHead() {
        return head;
    }

    public Node<E> getFirst() {
        return getHead().next;
    }

    public boolean isEmpty() {
        return getHead().isLast();
    }

    // Insert a node after position p
    public void insert(E data, Node<E> position) {
        if (position == null) {
            throw new NullPointerException();
        }
        position.next = new Node<>(data, position.next);
    }

    public Node<E> getTail() {
        Node<E> node = getHead();
        while (!node.isLast()) {
            node = node.next;
        }
        return node;
    }

    public void insertToTail(E[] array) {
        if (array == null) {
            throw new NullPointerException();
        }

        Node<E> last = getTail();
        for (E data: array) {
            insert(data, last);
            last = last.next;
        }
    }

    public int getLength() {
        int length = 0;
        Node<E> node = getHead();
        while (!node.isLast()) {
            length++;
            node = node.next;
        }
        return length;
    }

    public void show() {
        Node<E> node = getHead();
        while (!node.isLast()) {
            node = node.next;
            System.out.print(node.data + ", ");
        }
        System.out.println();
    }
}

class MyLinkedListWithSort<E extends Comparable<E>>
        extends MyLinkedList<E> {
    public MyLinkedListWithSort() {
        super();
    }

    public MyLinkedListWithSort(E[] array) {
        super(array);
    }

    public void mergeSort() {
        int k = 1;
        int length = getLength();

        // Auxiliary array to store the address of each element
        // The index begin from 1
        @SuppressWarnings("unchecked")
        Node<E>[] nodes = (Node<E>[])new Node[length + 1];

        Node<E> node = getFirst();
        getHead().next = null;
        Node<E> temp = node;
        while (node != null) {
            nodes[k] = node;
            k++;

            temp = node.next;
            node.next = null;
            node = temp;
        }

        k = 1;
        while (k < length) {
            mergePass(nodes, k, length);
            k *= 2;
        }

        getHead().next = nodes[1];
    }

    private void mergePass(Node<E>[] nodes, int k, int length) {
        int i;
        for (i = 1; i <= length - 2 * k + 1; i += 2 * k) {
            merge(nodes, i, i + k);
        }
        if (i < length - k + 1) {
            merge(nodes, i, i + k);
        }
    }

    private void merge(Node<E>[] nodes, int begin1, int begin2) {
        Node<E> former = null;
        Node<E> p1, p2;
        Node<E> p;

        p1 = nodes[begin1];
        p2 = nodes[begin2];

        if (p1.data.compareTo(p2.data) <= 0) {
            p = former = p1;
            p1 = p1.next;
        }
        else {
            p = former = p2;
            p2 = p2.next;
        }

        while (p1 != null && p2 != null) {
            if (p1.data.compareTo(p2.data) <= 0) {
                former.next = p1;
                former = p1;
                p1 = p1.next;
            }
            else {
                former.next = p2;
                former = p2;
                p2 = p2.next;
            }
        }

        while (p1 != null) {
            former.next = p1;
            former = p1;
            p1 = p1.next;
        }
        while (p2 != null) {
            former.next = p2;
            former = p2;
            p2 = p2.next;
        }

        // Update nodes
        int i = begin1;
        while (p != null) {
            nodes[i] = p;
            p = p.next;
            i++;
        }
    }
}
