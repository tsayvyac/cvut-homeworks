package cz.cvut.fel.pjv;

public class TreeImpl implements Tree{
    NodeImpl root;

    public TreeImpl() {
        this.root = null;
    }

    @Override
    public void setTree(int[] values) {
        root = null;
        subtrees(values, 0, values.length - 1);
    }

    public NodeImpl subtrees(int[] values, int start, int end) {
        if (start > end) {
            return null;
        }
        int center = centerOfTree(start, end);
        NodeImpl node = new NodeImpl(values[center]);
        if (root == null) {
            root = node;
        }
        node.left = subtrees(values, start, center - 1);
        node.right = subtrees(values, center + 1, end);
        return node;
    }

    public int centerOfTree(int start, int end) {
        int centerIndex;
        if ((start + end) % 2 == 0) {
            centerIndex = (start + end) / 2;
        } else {
            centerIndex = (start + end + 1) / 2;
        }
        return centerIndex;
    }

    @Override
    public Node getRoot() {
        return root;
    }

    @Override
    public String toString() {
        return treeToSting(root, 2);
    }

    public String treeToSting(NodeImpl node, int count) {
        String stringTree = "";
        if (node == null) {
            return stringTree;
        }
        stringTree += String.format("%" + count + "s", "- ") + node.value + "\n";
        count++;
        stringTree += treeToSting((NodeImpl) node.left, count);
        stringTree += treeToSting((NodeImpl) node.right, count);
        return stringTree;
    }
}
