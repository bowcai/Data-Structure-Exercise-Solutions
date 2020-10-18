class TestAVLTree {
    public static void main(String[] args) {
        AVLTree<Integer> tree = new AVLTree<>();

        tree.insert(new Integer[]{1, 3, 5, 2, 6, 7, 4});

        System.out.println("find(5): " + tree.find(5).getData());
        System.out.println("findMin(): " + tree.findMin().getData());
        System.out.println("findMax(): " + tree.findMax().getData());
    }
}

public class AVLTree<E extends Comparable<E>> {

    public static class AVLNode<E extends Comparable<E>> {
        private final E data;
        private AVLNode<E> leftChild;
        private AVLNode<E> rightChild;
        private int height;

        public AVLNode(E data) {
            this(data, null, null);
        }

        public AVLNode(E data, AVLNode<E> leftChild
                , AVLNode<E> rightChild) {
            this.data = data;
            this.leftChild = leftChild;
            this.rightChild = rightChild;
            this.height = 0;
        }

        public E getData() {
            return data;
        }

        public static int getHeight(AVLNode<?> node) {
            return node == null ? -1: node.height;
        }

        private void setHeight() {
            this.height = Math.max(getHeight(leftChild)
                    , getHeight(rightChild)) + 1;
        }

        // "this" is k2
        private AVLNode<E> singleRotateWithLeft() {
            AVLNode<E> k1 = this.leftChild;
            this.leftChild = k1.rightChild;
            k1.rightChild = this;

            this.setHeight();
            k1.setHeight();

            return k1;
        }

        // "this" is k2
        private AVLNode<E> singleRotateWithRight() {
            AVLNode<E> k1 = this.rightChild;
            this.rightChild = k1.leftChild;
            k1.leftChild = this;

            this.setHeight();
            k1.setHeight();
            return k1;
        }

        // "this" is k3
        private AVLNode<E> doubleRotateWithLeft() {
            this.leftChild = this.leftChild.singleRotateWithRight();

            return this.singleRotateWithLeft();
        }

        // "this" is k3
        private AVLNode<E> doubleRotateWithRight() {
            this.rightChild = this.rightChild.singleRotateWithLeft();

            return this.singleRotateWithRight();
        }

        private static final int ALLOW_BALANCE = 1;

        private AVLNode<E> balance(AVLNode<E> node) {
            if (node == null) {
                return null;
            }

            if (getHeight(node.leftChild) - getHeight(node.rightChild)
                    > ALLOW_BALANCE) {
                if (getHeight(node.leftChild.leftChild)
                        >= getHeight(node.leftChild.rightChild)) {
                    node = node.singleRotateWithLeft();
                }
                else {
                    node = node.doubleRotateWithLeft();
                }
            }
            else if (getHeight(node.rightChild) - getHeight(node.leftChild)
                    > ALLOW_BALANCE) {
                if (getHeight(node.rightChild.rightChild)
                        >= getHeight(node.rightChild.leftChild)) {
                    node = node.singleRotateWithRight();
                }
                else {
                    node = node.doubleRotateWithRight();
                }
            }

            node.setHeight();
            return node;
        }

        public AVLNode<E> insert(E data, AVLNode<E> node) {
            if (node == null) {
                return new AVLNode<>(data);
            }

            int compareResult = data.compareTo(node.data);

            if (compareResult < 0) {
                node.leftChild = insert(data, node.leftChild);
            }
            else if (compareResult > 0) {
                node.rightChild = insert(data, node.rightChild);
            }
            else {
                // Duplicate, do nothing
            }

            return balance(node);
        }

        public AVLNode<E> find(E data) {
            if (data == null) {
                throw new NullPointerException();
            }

            AVLNode<E> node = this;
            while (node != null) {
                if (data.compareTo(node.data) < 0) {
                    node = node.leftChild;
                }
                else if (data.compareTo(node.data) > 0) {
                    node = node.rightChild;
                }
                else return node;
            }
            return null;
        }

        public AVLNode<E> findMin() {
            AVLNode<E> node = this;
            while (node.leftChild != null) {
                node = node.leftChild;
            }
            return node;
        }

        public AVLNode<E> findMax() {
            AVLNode<E> node = this;
            while (node.rightChild != null) {
                node = node.rightChild;
            }
            return node;
        }
    }

    private AVLNode<E> root = null;

    public AVLTree() {}

    public void insert(E data) {
        if (root == null) {
            root = new AVLNode<>(data);
        }
        else {
            root = root.insert(data, root);
        }
    }

    public void insert(E[] array) {
        if (array == null) {
            throw new NullPointerException();
        }
        for (E data: array) {
            insert(data);
        }
    }

    public boolean isEmpty() {
        return root == null;
    }

    private void checkEmpty() {
        if (isEmpty()) {
            throw new NullPointerException("The tree is empty.");
        }
    }

    public AVLNode<E> find(E data) {
        checkEmpty();
        return root.find(data);
    }

    public AVLNode<E> findMin() {
        checkEmpty();
        return root.findMin();
    }

    public AVLNode<E> findMax() {
        checkEmpty();
        return root.findMax();
    }
}
