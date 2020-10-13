
public class LinkedQueue<E> {
    node<E> tail;

    public static class node<E> {
        private E data = null;
        private node<E> next = null;

        public node() {}

        public node(E data) {
            setData(data);
        }

        public node(E data, node<E> next) {
            this(data);
            setNext(next);
        }

        public E getData() {
            return data;
        }

        public void setData(E data) {
            this.data = data;
        }

        public node<E> getNext() {
            return next;
        }

        public boolean isLast() {
            return getNext() == null;
        }

        public void setNext(node<E> next) {
            this.next = next;
        }
    }

    public LinkedQueue() {
        makeEmpty();
    }

    public LinkedQueue(E[] inputArray) {
        this();

        for (E e: inputArray) {
            enqueue(e);
        }
    }

    public boolean isEmpty() {
        return tail.getNext() == tail;
    }

    public void makeEmpty() {
        tail = new node<>();
        tail.setNext(tail);
    }

    public void enqueue(E x) {
        node<E> newNode = new node<>(x, tail.getNext());
        tail.setNext(newNode);
        tail = newNode;
    }

    public E dequeue() {
        if (isEmpty()) {
            throw new IndexOutOfBoundsException("No node to dequeue");
        }

        // The node going to dequeue is the next node of head
        node<E> dequeuingNode = tail.getNext().getNext();
        E x = dequeuingNode.getData();

        // Check if the dequeuing node is the last node
        if (dequeuingNode != tail) {
            tail.getNext().setNext(dequeuingNode.getNext());
        }
        else {
            tail = tail.getNext();
            tail.setNext(tail);
        }

        return x;
    }
}

class TestLinkedList {
    public static void main(String[] args) {
        LinkedQueue<Integer> myQueue = new LinkedQueue<>(
                new Integer[]{3,2,5,4,1,3,6}
        );

        while(!myQueue.isEmpty()) {
            System.out.println("Dequeuing: " + myQueue.dequeue());
        }
    }
}
