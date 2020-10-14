import java.util.Stack;

public class TreeNodeDist {
    public static void main(String[] args) {
        TreeNode<Integer> node1 = new TreeNode<>(1);
        TreeNode<Integer> node2 = node1.insert(2, 0);
        TreeNode<Integer> node3 = node1.insert(3, 1);
        TreeNode<Integer> node4 = node2.insert(4, 0);
        TreeNode<Integer> node5 = node2.insert(5, 1);
        TreeNode<Integer> node6 = node3.insert(6, 0);

        System.out.println("Distance between node4 and node6: "
                + node4.getDistance(node6));
        System.out.println("Distance between node4 and node5: "
                + node4.getDistance(node5));
        System.out.println("Distance between node4 and node2: "
                + node4.getDistance(node2));
    }
}

class TreeNode<E> {
    public E data;
    public TreeNode<E> left = null;
    public TreeNode<E> right = null;
    public TreeNode<E> parent = null;

    public TreeNode(E data) {
        this.data = data;
    }

    // Insert a node under a TreeNode
    // Direction=0 means insert into left
    // Direction=1 means insert into right
    public TreeNode<E> insert(E x, int direction) {
        TreeNode<E> newNode = new TreeNode<>(x);
        newNode.parent = this;

        if (direction == 0) {
            this.left = newNode;
        }
        else {
            this.right = newNode;
        }

        return newNode;
    }

    private Stack<TreeNode<E>> getAncestors() {
        Stack<TreeNode<E>> ancestors = new Stack<>();

        for (TreeNode<E> i = this; i != null; i = i.parent) {
            ancestors.push(i);
        }
        return ancestors;
    }

    public int getDistance(TreeNode<E> b) {
        if (b == null) {
            throw new NullPointerException();
        }

        Stack<TreeNode<E>> aAncestors = getAncestors();
        Stack<TreeNode<E>> bAncestors = b.getAncestors();

        while (aAncestors.size() > 0 && bAncestors.size() > 0
                && aAncestors.peek() == bAncestors.peek()) {
            aAncestors.pop();
            bAncestors.pop();
        }

        return aAncestors.size() + bAncestors.size();
    }
}
