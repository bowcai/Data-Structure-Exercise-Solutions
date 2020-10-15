import java.util.Scanner;

public class BinaryTreeDepth {
    public static void main(String[] args) {
        int n;
        Scanner input = new Scanner(System.in);

        n = input.nextInt();

        TreeNode.Pair[] v = new TreeNode.Pair[n];

        for (int i = 0; i < n; i++) {
            v[i] = new TreeNode.Pair();
            v[i].first = input.nextInt();
            v[i].second = input.nextInt();
        }

        System.out.println();
        System.out.println("Output");

        System.out.println(TreeNode.treeDepth(v));
    }
}

class TreeNode {
    private final int id;
    private int depth = 1;
    private TreeNode leftChild = null;
    private TreeNode rightChild = null;

    public TreeNode(int id) {
        this.id = id;
    }

    public static class Pair {
        public int first;
        public int second;
    }

    public static int treeDepth(Pair[] v) {
        if (v == null) {
            throw new NullPointerException();
        }

        TreeNode[] nodes = new TreeNode[v.length];
        int maxDepth = 0;

        for (int i = 0; i < v.length; i++) {
            nodes[i] = new TreeNode(i + 1);
        }

        for (int i = 0; i < v.length; i++) {
            if (v[i].first > 0 && v[i].first <= v.length) {
                nodes[i].leftChild = nodes[v[i].first-1];
                nodes[v[i].first-1].depth = nodes[i].depth + 1;

                if (nodes[v[i].first-1].depth > maxDepth){
                    maxDepth = nodes[v[i].first-1].depth;
                }
            }

            if (v[i].second > 0 && v[i].second <= v.length) {
                nodes[i].rightChild = nodes[v[i].second-1];
                nodes[v[i].second-1].depth = nodes[i].depth + 1;

                if (nodes[v[i].second-1].depth > maxDepth){
                    maxDepth = nodes[v[i].second-1].depth;
                }
            }
        }

        return maxDepth;
    }

}
