import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Scanner;

public class HuffmanCoding {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        String s = input.nextLine();
        HashMap<Character, Integer> count = countChar(s);

        HuffmanTree<Character> tree = new HuffmanTree<>(count);
        System.out.println(tree.getRootTotalBits());
    }

    public static HashMap<Character, Integer> countChar(String s) {
        if (s == null) {
            throw new NullPointerException();
        }

        HashMap<Character, Integer> count = new HashMap<>();

        for (char c : s.toCharArray()){
            if (!count.containsKey(c)) {
                count.put(c, 1);
            }
            else {
                count.put(c, count.get(c) + 1);
            }
        }

        return count;
    }
}

class HuffmanTree<E> {
    public static class HuffmanNode<E>
            implements Comparable<HuffmanNode<E>>{
        private final E data;

        // Sum of all the child leaves' weight
        // Use int as weight type
        private final int leafWeight;

        // The total number of bits to encode
        // all the child leaves' characters in the string
        // if this node is the root node.
        private final int totalBits;

        private final HuffmanNode<E> leftChild;
        private final HuffmanNode<E> rightChild;

        // Create a leaf of Huffman Tree
        public HuffmanNode(E data, int weight) {
            this.data = data;
            this.totalBits = 0;
            this.leafWeight = weight;
            this.leftChild = null;
            this.rightChild = null;
        }

        // Combine two HuffmanNode with a new root node
        public HuffmanNode(HuffmanNode<E> leftChild
                , HuffmanNode<E> rightChild) {
            if (leftChild == null || rightChild == null) {
                throw new NullPointerException(
                    "Non-leaf Huffman Tree node must have two children");
            }

            this.data = null;
            this.leftChild = leftChild;
            this.rightChild = rightChild;

            // Each child leaves' character
            // gets one more bit to encode.
            this.totalBits
                    = leftChild.totalBits + rightChild.totalBits
                    + leftChild.leafWeight + rightChild.leafWeight;

            this.leafWeight = leftChild.leafWeight
                            + rightChild.leafWeight;
        }

        public boolean isLeaf() {
            return leftChild == null && rightChild == null;
        }

        public E getData() {
            return data;
        }

        public int getTotalBits() {
            return totalBits;
        }

        public int getLeafWeight() {
            return leafWeight;
        }

        public HuffmanNode<E> getLeftChild() {
            return leftChild;
        }

        public HuffmanNode<E> getRightChild() {
            return rightChild;
        }

        @Override
        public int compareTo(HuffmanNode<E> o) {
            if (o == null) {
                throw new NullPointerException();
            }
            return this.leafWeight - o.leafWeight;
        }
    }

    private HuffmanNode<E> root = null;

    public HuffmanTree() {
    }

    public HuffmanTree(Map<E, Integer> weights) {
        this();
        buildHuffman(weights);
    }

    public void buildHuffman(Map<E, Integer> weights) {
        if (weights == null) {
            throw new NullPointerException();
        }

        PriorityQueue<HuffmanNode<E>> nodes
                    = new PriorityQueue<>();

        weights.forEach((k, v)
                -> nodes.add(new HuffmanNode<>(k, v)));

        while (nodes.size() >= 2) {
            nodes.add(new HuffmanNode<>(
                    nodes.poll(), nodes.poll()));
        }

        root = nodes.peek();
    }

    public int getRootLeafWeight() {
        return root.getLeafWeight();
    }

    public int getRootTotalBits() {
        return root.getTotalBits();
    }
}
