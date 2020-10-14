import java.util.*;

public class ExpressionTree {
    public static void main(String[] args) {
        int nVariable;
        Map<Character, Integer> variables = new HashMap<>();
        String infix;

        // Get input
        Scanner input = new Scanner(System.in);
        infix = input.nextLine();
        nVariable = input.nextInt();

        for (int i = 0; i < nVariable; i++) {
            variables.put(input.next().charAt(0), input.nextInt());
        }

        System.out.println();
        System.out.println("Output:");

        String postfix = toPostfix(infix);
        System.out.println(postfix);
        TreeNode<Character> T = postfixToTree(postfix);
        T.show();
        System.out.println(computePostfix(postfix, variables));
    }

    // Convert the infix expression into postfix expression
    public static String toPostfix(String S) {
        if (S == null) {
            throw new NullPointerException();
        }

        Stack<Character> oper = new Stack<>();
        StringBuilder postfix = new StringBuilder();
        for (char c : S.toCharArray()) {
            if ((c >= 'a' && c <= 'z')
                    || (c >= 'A' && c <= 'Z')) {
                postfix.append(c);
            }
            else if (c == '(') {
                oper.push(c);
            }
            else if (c == ')') {
                while (oper.size() > 0 && oper.peek() != '(') {
                    // Pop the operators and insert into postfix
                    postfix.append(oper.pop());
                }
                // Pop the '('
                oper.pop();
            }
            else if (c == '*' || c == '/') {
                while (oper.size() > 0 && oper.peek() != '('
                        && oper.peek() != '+' && oper.peek() != '-') {
                    postfix.append(oper.pop());
                }
                // Push c into stack
                oper.push(c);
            }
            else if (c == '+' || c == '-') {
                while (oper.size() > 0 && oper.peek() != '(') {
                    postfix.append(oper.pop());
                }
                oper.push(c);
            }
            else {
                throw new IllegalArgumentException(
                        "The infix expression is illegal.");
            }
        }

        while (!oper.isEmpty()) {
            if (oper.peek() != '(') {
                postfix.append(oper.peek());
            }
            oper.pop();
        }

        return postfix.toString();
    }

    public static int computePostfix(
            String postfix, Map<Character, Integer> values) {
        if (postfix == null || values == null) {
            throw new NullPointerException();
        }

        Stack<Integer> numbers = new Stack<>();

        for (char c: postfix.toCharArray()) {
            if ((c >= 'a' && c <= 'z')
                    || (c >= 'A' && c <= 'Z')) {
                Integer value = values.get(c);
                if (value == null) {
                    throw new IllegalArgumentException(
                            "The value of variable " + c
                            + " is not given");
                }
                numbers.push(value);
            }
            else if (c == '+' || c == '-'
                    || c == '*' || c == '/') {
                if (numbers.size() < 2) {
                    throw new IllegalArgumentException(
                            "The postfix expression is illegal.");
                }

                int a = numbers.pop();
                int b = numbers.pop();

                switch (c) {
                    case '+':
                        numbers.push(a + b);
                        break;
                    case '-':
                        numbers.push(a - b);
                        break;
                    case '*':
                        numbers.push(a * b);
                        break;
                    case '/':
                        numbers.push(a / b);
                        break;
                    default:
                        break;
                }
            }
            else {
                throw new IllegalArgumentException(
                        "The postfix expression is illegal.");
            }
        }

        if (numbers.size() != 1) {
            throw new IllegalArgumentException(
                    "The postfix expression is illegal.");
        }

        return numbers.peek();
    }

    public static TreeNode<Character> postfixToTree(String postfix) {
        if (postfix == null) {
            throw new NullPointerException();
        }
        Stack<TreeNode<Character>> nodes = new Stack<>();
        for (char c : postfix.toCharArray()) {
            if ((c >= 'a' && c <= 'z')
                    || (c >= 'A' && c <= 'Z')) {
                nodes.push(new TreeNode<>(c));
            }
            else if (c == '+' || c == '-'
                    || c == '*' || c == '/') {
                if (nodes.size() < 2) {
                    throw new IllegalArgumentException(
                            "The postfix expression is illegal");
                }

                TreeNode<Character> right = nodes.pop();
                TreeNode<Character> left = nodes.pop();

                nodes.push(new TreeNode<>(c, left, right));
            }
            else {
                throw new IllegalArgumentException(
                        "The postfix expression is illegal");
            }
        }

        if (nodes.size() != 1) {
            throw new IllegalArgumentException(
                    "The postfix expression is illegal");
        }

        return nodes.peek();
    }
}

class TreeNode<E> {
    E data;
    TreeNode<E> left = null;
    TreeNode<E> right = null;
    int height = 0;

    public TreeNode() {
        this.data = null;
    }

    public TreeNode(E data) {
        this();
        this.data = data;
    }

    // Combine tree with a new root
    public TreeNode(E data, TreeNode<E> left
            , TreeNode<E> right) {
        this(data);
        this.left = left;
        this.right = right;

        int leftHeight = left != null ? left.height : -1;
        int rightHeight = right != null ? right.height : -1;
        this.height = leftHeight > rightHeight
                ? leftHeight + 1 : rightHeight + 1;
    }

    private static class NodeDepth<E> {
        TreeNode<E> node;
        int layer;

        // The coordinate of node in output
        int coordinate;

        public NodeDepth(TreeNode<E> node
                , int layer, int coordinate) {
            this.node = node;
            this.layer = layer;
            this.coordinate = coordinate;
        }
    }

    public void show() {
        Queue<NodeDepth<E>> nodes = new LinkedList<>();
        ArrayList<String> outs = new ArrayList<>();

        // Get the sequence of nodes
        nodes.offer(new NodeDepth<>(this
                , height, (1 << height) - 1));

        StringBuilder s1 = new StringBuilder();
        StringBuilder s2 = new StringBuilder();
        int coord1 = 0;
        int coord2 = 0;
        int last_layer = height;

        while (nodes.size() > 0) {
            NodeDepth<E> current = nodes.remove();

            // Put last layer into output strings
            if (last_layer != current.layer) {
                outs.add(s1.toString());
                outs.add(s2.toString());
                s1 = new StringBuilder();
                s2 = new StringBuilder();
                coord1 = 0;
                coord2 = 0;
                last_layer = current.layer;
            }

            // Deal with current node
            for (int i = 0; i < current.coordinate - coord1; i++) {
                s1.append(" ");
            }
            s1.append(current.node.data.toString());
            coord1 = current.coordinate + 1;

            if (current.node.left != null){
                nodes.offer(new NodeDepth<>(
                    current.node.left, current.layer - 1
                    , current.coordinate - (1 << (current.layer - 1))
                ));

                for (int i = 0; i < current.coordinate - 1 - coord2; i++) {
                    s2.append(" ");
                }
                s2.append("/");
                coord2 = current.coordinate;
            }

            if (current.node.right != null){
                nodes.offer(new NodeDepth<>(
                    current.node.right, current.layer - 1
                    , current.coordinate + (1 << (current.layer - 1))
                ));

                for (int i = 0; i < current.coordinate + 1 - coord2; i++) {
                    s2.append(" ");
                }
                s2.append("\\");
                coord2 = current.coordinate + 2;
            }
        }

        outs.add(s1.toString());

        for (String s : outs){
            System.out.println(s);
        }
    }
}
