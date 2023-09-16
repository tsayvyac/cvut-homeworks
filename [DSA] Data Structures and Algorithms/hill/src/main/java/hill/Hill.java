package hill;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Hill {
    static class Pair {
        int row;
        int col;

        public Pair(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }

    static class Quintet {
        int length;
        int slope;
        int sum;
        int maxSlope;
        Pair prev;

        public Quintet(int length, int slope, int sum, int maxSlope, Pair pair) {
            this.length = length;
            this.slope = slope;
            this.sum = sum;
            this.maxSlope = maxSlope;
            this.prev = pair;
        }
    }

    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static int[][] matrix;
    static Quintet[][] topMemo;
    static Quintet[][] bottomMemo;
    static boolean firstLine = true;
    static int highest = 0;
    static final int[] dRow = {0, 1, 0, -1};
    static final int[] dCol = {1, 0, -1, 0};
    static Queue<Pair> queue = new LinkedList<>();
    static int[] path;

    static void errorMessage() {
        System.err.println("Error: Chybny vstup!");
        System.exit(1);
    }

    static void initMatrixSize(String line) {
        String[] splitLine = line.split("\\s+");
        if (splitLine.length != 2) errorMessage();
        int rows = Integer.parseInt(splitLine[0]);
        int cols = Integer.parseInt(splitLine[1]);
        matrix = new int[rows][cols];
        topMemo = new Quintet[rows][cols];
        bottomMemo = new Quintet[rows][cols];
        firstLine = false;
    }

    static void parse() throws IOException {
        String line;
        int row = 0;
        int v;
        while ((line = br.readLine()) != null) {
            if (firstLine) {
                initMatrixSize(line);
                continue;
            }
            String[] splitLine = line.split("\\s+");
            if (splitLine.length != matrix[0].length ||
                    row + 1 > matrix.length) errorMessage();
            for (int i = 0; i < splitLine.length; i++) {
                v = Integer.parseInt(splitLine[i]);
                highest = Math.max(v, highest);
                matrix[row][i] = v;
            }
            row++;
        }
    }

    static boolean isValid(int row, int col) {
        return row >= 0 && col >= 0 && row < matrix.length && col < matrix[0].length;
    }

    private static void direction(Quintet[][] m, int row, int col, int i) {
        int nRow = row + dRow[i];
        int nCol = col + dCol[i];
        if (isValid(nRow, nCol) && matrix[nRow][nCol] > matrix[row][col]) {
            int slope = matrix[nRow][nCol] - matrix[row][col];
            int sum = m[row][col].sum + slope;
            int maxSlope = Math.max(m[row][col].maxSlope, slope);
            int length = m[row][col].length + 1;
            if (m[nRow][nCol] != null) {
                if (m[nRow][nCol].sum < sum || (m[nRow][nCol].sum == sum && (m[nRow][nCol].maxSlope < maxSlope)))
                    m[nRow][nCol] = new Quintet(length, slope, sum, maxSlope, new Pair(row, col));
            } else {
                queue.add(new Pair(nRow, nCol));
                m[nRow][nCol] = new Quintet(length, slope, sum, maxSlope, new Pair(row, col));
            }
        }
    }

    static void topLift() {
        Pair initial = new Pair(0, 0);
        queue.add(initial);
        topMemo[0][0] = new Quintet(0, 0, 0, 0, initial);
        while (!queue.isEmpty()) {
            Pair front = queue.remove();
            for (int i = 0; i < 2; i++)
                direction(topMemo, front.row, front.col, i);
        }
    }

    static void downLift() {
        int endRow = matrix.length - 1;
        int endCol = matrix[0].length - 1;
        if (bottomMemo[endRow][endCol] != null) return;
        queue.add(new Pair(endRow, endCol));
        bottomMemo[endRow][endCol] = new Quintet(0, 0, 0, 0, new Pair(0, 0));
        while (!queue.isEmpty()) {
            Pair front = queue.remove();
            for (int i = 3; i >= 2; i--)
                direction(bottomMemo, front.row, front.col, i);
        }
    }

    static void toTopLeft(int[] path, Pair p) {
        path[topMemo[p.row][p.col].length] = matrix[p.row][p.col];
        if (topMemo[p.row][p.col].prev.row == 0 && topMemo[p.row][p.col].prev.col == 0) return;
        toTopLeft(path, topMemo[p.row][p.col].prev);
    }

    static void toRightBottom(int[] path, Pair p) {
        if (bottomMemo[p.row][p.col] == null) return;
        path[path.length - bottomMemo[p.row][p.col].length - 1] = matrix[p.row][p.col];
        if (bottomMemo[p.row][p.col].prev.row == 0 && bottomMemo[p.row][p.col].prev.col == 0) return;
        toRightBottom(path, bottomMemo[p.row][p.col].prev);
    }

    static void construct(int[] path, Pair max) {
        toTopLeft(path, max);
        toRightBottom(path, bottomMemo[max.row][max.col].prev);
        printPath(path);
    }

    static Pair comparePeaks(List<Pair> inter) {
        int topMax = 0;
        int topMaxSlope = 0;
        int bottomMax = 0;
        int bottomMaxSlope = 0;
        Pair tm = new Pair(0, 0);
        Pair bm = new Pair(0, 0);
        for (Pair p : inter) {
            if (matrix[p.row][p.col] > topMax ||
                    (matrix[p.row][p.col] == topMax && topMemo[p.row][p.col].slope > topMaxSlope)) {
                topMax = matrix[p.row][p.col];
                topMaxSlope = topMemo[p.row][p.col].slope;
                tm = new Pair(p.row, p.col);
            }
            if (matrix[p.row][p.col] > bottomMax ||
                    (matrix[p.row][p.col] == bottomMax && bottomMemo[p.row][p.col].slope > bottomMaxSlope)) {
                bottomMax = matrix[p.row][p.col];
                bottomMaxSlope = bottomMemo[p.row][p.col].slope;
                bm = new Pair(p.row, p.col);
            }
        }
        Pair max = topMax > bottomMax ? tm : bm;
        int length = topMemo[max.row][max.col].length + bottomMemo[max.row][max.col].length + 1;
        path = new int[length];
        path[0] = matrix[0][0];
        path[length - 1] = matrix[matrix.length - 1][matrix[0].length - 1];
        return max;
    }

    static void buildPath() {
        List<Pair> intersection = new ArrayList<>();
        for (int row = 0; row < matrix.length; row++) {
            for (int col = 0; col < matrix[0].length; col++) {
                if (topMemo[row][col] != null && bottomMemo[row][col] != null)
                    intersection.add(new Pair(row, col));
            }
        }
        Pair max = comparePeaks(intersection);
        construct(path, max);
    }

    static void lift() {
        topLift();
        downLift();
        buildPath();
    }

    static void piste() {
        System.out.println("Piste");
    }

    static void printPath(int[] path) {
        System.out.println(path.length);
        for (int i = 0; i < path.length; i++) {
            if (i != path.length - 1)
                System.out.print(path[i] + " ");
            else
                System.out.println(path[i]);
        }
    }

    public static void main(String[] args) throws IOException {
        parse();
        if (args.length != 0) {
            if (Objects.equals(args[0], "lift"))
                lift();
            else if (Objects.equals(args[0], "piste"))
                piste();
        } else {
            lift();
            piste();
        }
    }
}