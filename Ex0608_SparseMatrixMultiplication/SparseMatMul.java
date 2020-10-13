import java.util.ArrayList;
import java.util.Collections;
import java.util.Objects;

public class SparseMatMul {
    public static void main(String[] args) {
        SparseMatrix a = new SparseMatrix(3, 4);
        SparseVector b = new SparseVector(4);

        a.input(1, 1, 5);
        a.input(0, 2, 2);
        a.input(0, 0, 3);
        a.input(1, 3, 4);
        a.input(2, 2, 6);

        b.input(2, 6);
        b.input(0, 2);


        System.out.println("Matrix A:");
        a.show();
        System.out.println("Vector b:");
        b.show();

        System.out.println();
        System.out.println("The result c:");
        a.multiply(b).show();
    }
}

class SparseMatrix {
    public static class SPMNode<ENode>
            implements Comparable<SPMNode<ENode>> {
        public int i, j;
        public ENode value;

        public SPMNode(int i, int j, ENode value) {
            this.i = i;
            this.j = j;
            this.value = value;
        }

        // Rewrite equals to check nodes in the same place
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass())
                return false;
            SPMNode<?> spmNode = (SPMNode<?>) o;
            return i == spmNode.i &&
                    j == spmNode.j;
        }

        @Override
        public int hashCode() {
            return Objects.hash(i, j);
        }

        // For sorting the elements in matrix
        @Override
        public int compareTo(SPMNode<ENode> o) {
            if (o == null) {
                throw new NullPointerException();
            }
            if (i != o.i) {
                return i - o.i;
            }
            else {
                return j - o.j;
            }
        }
    }

    // mu, nu is the size of the matrix
    // tu is the number of non-zero elements
    public final int mu, nu;
    public final ArrayList<SPMNode<Integer>> data;

    public SparseMatrix(int mu, int nu) {
        this.mu = mu;
        this.nu = nu;
        data = new ArrayList<>();
    }

    // Get the number of non-zero elements
    public int getNonzeroLength() {
        return data.size();
    }

    public void input(SPMNode<Integer> node) {
        if (node == null || node.i >= mu && node.j >= nu) {
            throw new IllegalArgumentException(
                    "Input index out of range");
        }

        // Check if the nodes are in the same place
        // Use rewritten equals()
        int indexSame = data.indexOf(node);
        if (indexSame < 0) {
            data.add(node);
        }
        else {
            data.set(indexSame, node);
        }
    }

    public void input(int x, int y, Integer value) {
        input(new SPMNode<>(x, y, value));
    }

    public void show() {
        System.out.println("     i|     j|    data|");
        System.out.println("------|------|--------|");
        for (SPMNode<Integer> k: data) {
            System.out.printf("%6d|%6d|%8d|\n", k.i
                    , k.j, k.value);
        }
    }

    // Sort the data according to row and column indices
    public void sort() {
        Collections.sort(data);
    }

    // Will automatically sorts the matrix and vector
    public SparseVector multiply(SparseVector b) {
        if (b == null) {
            throw new NullPointerException();
        }
        if (nu != b.mu) {
            throw new IllegalArgumentException(
                    "The size of matrix and vector does not match");
        }

        sort();
        b.sort();

        SparseVector c = new SparseVector(mu);
        if (getNonzeroLength() == 0 || b.getNonzeroLength() == 0) {
            return c;
        }

        int ak = 0, bk = 0;
        SparseVector.SPVNode<Integer> ck =
                new SparseVector.SPVNode<>(0, 0);
        while (ak < getNonzeroLength()) {
            if (ck.i != data.get(ak).i) {
                if (ck.value != 0) {
                    c.input(ck);
                }
                ck = new SparseVector.SPVNode<>(data.get(ak).i, 0);
                bk = 0;
                continue;
            }
            if (bk == b.getNonzeroLength()
                || data.get(ak).j < b.data.get(bk).i) {
                ak++;
                continue;
            }
            if (data.get(ak).j > b.data.get(bk).i) {
                bk++;
                continue;
            }

            // ak.j == bk.i
            ck.value += data.get(ak).value * b.data.get(bk).value;
            ak++;
            bk++;
        }

        if (ck.value != 0) {
            c.input(ck);
        }

        return c;
    }
}

class SparseVector {
    public static class SPVNode<ENode>
            implements Comparable<SPVNode<ENode>>{
        public int i;
        public ENode value;

        public SPVNode(int i, ENode value) {
            this.i = i;
            this.value = value;
        }

        // Rewrite equals to check nodes in the same place
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass())
                return false;
            SPVNode<?> spvNode = (SPVNode<?>) o;
            return i == spvNode.i;
        }

        @Override
        public int hashCode() {
            return Objects.hash(i);
        }

        // For sorting the elements in vector
        @Override
        public int compareTo(SPVNode<ENode> o) {
            if (o == null) {
                throw new NullPointerException();
            }
            return i - o.i;
        }
    }

    // mu is the size of the vector
    // tu is the number of non-zero elements
    public final int mu;
    public final ArrayList<SPVNode<Integer>> data;

    public SparseVector(int mu) {
        this.mu = mu;
        data = new ArrayList<>();
    }

    // Get the number of non-zero elements
    public int getNonzeroLength() {
        return data.size();
    }

    public void input(SPVNode<Integer> node) {
        if (node == null) {
            throw new NullPointerException();
        }
        if (node.i >= mu) {
            throw new IllegalArgumentException(
                    "Input index out of range");
        }

        // Check if the nodes are in the same place
        // Use rewritten equals()
        int indexSame = data.indexOf(node);
        if (indexSame < 0) {
            data.add(node);
        }
        else {
            data.set(indexSame, node);
        }
    }

    public void input(int i, Integer value) {
        input(new SPVNode<>(i, value));
    }

    public void show() {
        System.out.println("     i|    data|");
        System.out.println("------|--------|");
        for (SPVNode<Integer> k: data) {
            System.out.printf("%6d|%8s|\n", k.i, k.value);
        }
    }

    // Sort the data according to row indices
    public void sort() {
        Collections.sort(data);
    }
}
