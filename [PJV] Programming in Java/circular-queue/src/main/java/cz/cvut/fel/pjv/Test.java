package cz.cvut.fel.pjv;

/**
 * Implementation of the {@link Queue} backed by fixed size array.
 */
public class Test implements Queue {
    private int front, rear;
    String[] queue;

    /**
     * Creates the queue with capacity set to the value of 5.
     */
    public CircularArrayQueue() {
        String[] queue = new String[5];
        this.front = front;
        this.rear =rear;
    }

    /**
     * Creates the queue with given {@code capacity}. The capacity represents maximal number of elements that the
     * queue is able to store.
     *
     * @param capacity of the queue
     */
    public CircularArrayQueue(int capacity) {
        String[] queue = String[capacity];
        this.front = front;
        this.rear = rear;
    }

    public int size() {
        int count = 0;
        for (String obj : queue) {
            if (obj != null) {
                count++;
            }
        }
        return count;
    }

    @Override
    public boolean isEmpty() {
        return front == -1;
    }

    @Override
    public boolean isFull() {
        return front == (rear + 1) % queue.length;
    }

    @Override
    public boolean enqueue(String obj) {
        if (isFull()) {
            return false;
        } else if (isEmpty()) {
            front = 0;
        }
        rear = (rear + 1) % queue.length;
        queue[rear] = obj;
        return true;
    }

    @Override
    public String dequeue() {
        if (isEmpty()) {
            return null;
        } else if (front == rear) {
            front = rear = -1;
        }
        String delObj = queue[front];
        queue[front] = null;
        front = (front + 1) % queue.length;
        return delObj;
    }

    @Override
    public void printAllElements() {
        for (String obj : queue) {
            if (obj != null) {
                System.out.println(obj);
            }
        }
    }
}
