import java.util.LinkedList;

public class MyHashTable<K extends Integer, V> {
    public static class Node<K, V> {
        public K key;
        public V value;

        public Node(K key, V value) {
            this.key = key;
            this.value = value;
        }
    }

    private final int tableLength;
    private int numElement;
    private LinkedList<Node<K, V>>[] lists;

    public MyHashTable() {
        this(7);
    }

    @SuppressWarnings("unchecked")
    public MyHashTable(int tableLength) {
        this.numElement = 0;
        this.tableLength = nextPrime(tableLength);
        lists = new LinkedList[this.tableLength];
        for (int i = 0; i < this.tableLength; i++) {
            lists[i] = new LinkedList<>();
        }
    }

    public int hashFunc(K key) {
        if (key == null) {
            throw new NullPointerException();
        }
        return key.intValue() % tableLength;
    }

    public static boolean isPrime(int n) {
        if (n < 2) {
            return false;
        }

        for (int i = 2; i < n / 2; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    public static int nextPrime(int n) {
        if (n <= 2) {
            return 2;
        }

        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    public int getNumElement() {
        return numElement;
    }

    public int getTableLength() {
        return tableLength;
    }

    public void put(K key, V value) {
        if (key == null) {
            throw new NullPointerException();
        }

        int m = hashFunc(key);

        lists[m].add(new Node<>(key, value));
        numElement++;
    }

    public void put(Node<K, V> node) {
        if (node == null) {
            throw new NullPointerException();
        }
        put(node.key, node.value);
    }

    public void put(Node<K, V>[] array) {
        if (array == null) {
            throw new NullPointerException();
        }
        for (Node<K, V> i: array) {
            put(i);
        }
    }

    public V findKey(K key) {
        int m = hashFunc(key);

        for (Node<K, V> node: lists[m]) {
            if (node.key.equals(key)) {
                return node.value;
            }
        }

        System.out.println("Cannot find the key");
        return null;
    }

    public void deleteKey(K key) {
        int m = hashFunc(key);
        int formerSize = lists[m].size();

        lists[m].removeIf(e -> e.key.equals(key));

        numElement -= formerSize - lists[m].size();
    }

    public void printTable() {
        for (int i = 0; i < tableLength; i++) {
            System.out.print(i + ": ");

            for (Node<K, V> node: lists[i]) {
                System.out.print(node.key + " ");
            }
            System.out.println();
        }
    }

    public void printInfo() {
        System.out.println("Length of hashtable: " + getTableLength());
        System.out.println("Number of elements:" + getNumElement());

        int sum = 0;
        for (LinkedList<Node<K, V>> list: lists) {
            sum += list.size() * (list.size() + 1) / 2;
        }
        double successfulASL = (double) sum
                / (double) getNumElement();

        System.out.println("Successful ASL: " + successfulASL);
    }
}

class TestMyHashTable {
    public static void main(String[] args) {
        MyHashTable<Integer, String> table = new MyHashTable<>(11);

        table.put(1, "One");
        table.put(3, "Three");
        table.put(5, "Five");
        table.put(2, "Two");
        table.put(8, "Eight");
        table.put(10, "Ten");
        table.put(25, "Twenty-five");
        table.put(31, "Thirty-one");

        table.printTable();
        System.out.println();
        table.printInfo();
        System.out.println();

        System.out.println("Value of key 8: " + table.findKey(8));
    }
}
