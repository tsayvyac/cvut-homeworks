package cz.cvut.fel.pjv;


import java.util.ArrayList;

public class Test {
    public void start(String[] args) {
        homework();
    }
    public void homework() {
        TextIO io = new TextIO();
        double sum = 0, sd = 0, mean;
        int count = 0, line = 0;
        ArrayList<Double> array = new ArrayList<Double>();
        while (io.stdin.hasNextLine()) {
            line++;
            String input = io.stdin.nextLine();
            if (TextIO.isInteger(input) || TextIO.isFloat(input) || TextIO.isDouble(input)) {
                array.add(Double.parseDouble(input));
                sum += Double.parseDouble(input);
                count++;
                if (count == 10) {
                    mean = sum / count;
                    for (double num : array) {
                        sd += Math.pow(num - mean, 2);
                    }
                    System.out.printf("%2d %.3f %.3f", count, mean, Math.sqrt(sd / count));
                    System.out.println();
                    count = 0;
                    array.clear();
                } else {
                    System.out.println("A number has not been parsed from line " + line);
                }
            }
        }
        mean = sum / count;
        for (double num : array) {
            sd += Math.pow(num - mean, 2);
        }
        System.out.println("End of input detected!");
        System.out.printf("%2d %.3f %.3f", count, mean, Math.sqrt(sd / count));
    }
}