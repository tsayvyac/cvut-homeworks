package cz.cvut.fel.pjv;

public class NodeImpl implements Node{
    int value;
    Node right, left;

    public NodeImpl(int value) {
        this.value = value;
        this.right = null;
        this.left = null;
    }

    @Override
    public Node getLeft() {
        return this.left;
    }

    @Override
    public int getValue() {
        return this.value;
    }

    @Override
    public Node getRight() {
        return this.right;
    }

}
