
public class ReverseLinkedList {
    public static void main(String[] args) {
        MyLinkedList<Integer> list = new MyLinkedList<>(
                new Integer[]{1,9,3,5,4,2,7,4,5});

        System.out.println("List before reversion:");
        list.show();

        list.reverse();

        System.out.println("List after reversion:");
        list.show();
    }
}

class MyLinkedList<E> {
    node<E> head = new node<>();

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

        protected void setNext(node<E> next) {
            this.next = next;
        }
    }

    public MyLinkedList() { }

    public MyLinkedList(E[] inputArray) {
        buildList(inputArray);
    }

    public boolean isEmpty() {
        return head.isLast();
    }

    public void makeEmpty() {
        head.setNext(null);
    }

    public void show() {
        node<E> p = head.getNext();

        while(p != null) {
            System.out.print(p.getData() + ", ");
            p = p.getNext();
        }
        System.out.println();
    }

    public void insert(E x, node<E> p) {
        node<E> tmpNode = new node<>(x, p.next);
        p.setNext(tmpNode);
    }

    public void buildList(final E[] inputArray) {
        makeEmpty();
        node<E> last = head;
        for (E e: inputArray) {
            insert(e, last);
            last = last.next;
        }
    }

    public void reverse() {
        if (isEmpty() || head.getNext().isLast()) {
            System.out.println("Do not need to reverse the list.");
            return;
        }

        node<E> current, nextNode;
        current = head.getNext().getNext();
        head.getNext().setNext(null);

        while (current != null) {
            nextNode = current.getNext();
            current.setNext(head.getNext());
            head.setNext(current);
            current = nextNode;
        }
    }

}
