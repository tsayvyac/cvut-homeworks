package cz.cvut.fel.pjv;


import java.util.ArrayList;

public class Lab02 {
   public void start(String[] args) {
      homework();
   }

   public void homework() {
      TextIO io = new TextIO();
      Lab02 methods = new Lab02();
      double mean;
      int line = 0;
      String input;
      ArrayList<Double> array = new ArrayList<Double>();
      do {
         input = io.getLine();
         line++;
         if (TextIO.isDouble(input) || TextIO.isFloat(input) || TextIO.isInteger(input)) {
            array.add(Double.parseDouble(input));
            if (array.size() == 10) {
               mean = methods.sumInArray(array) / array.size();
               System.out.printf("%2d %.3f %.3f\n", array.size(), mean, methods.sd(array, mean));
               array.clear();
            }
         } else {
            if (input.equals("")) {
               break;
            }
            System.out.println("A number has not been parsed from line " + line);
         }
      } while (!input.equals(""));
      if (array.size() > 1) {
         mean = sumInArray(array) / array.size();
         System.out.println("End of input detected!");
         System.out.printf("%2d %.3f %.3f\n", array.size(), mean, methods.sd(array, mean));
      } else {
         System.out.print("End of input detected!\n");
      }
   }

   public double sd(ArrayList<Double> arr, double mean) {
      double sd = 0;
      for (double num : arr) {
         sd += Math.pow(num - mean, 2);
      }
      return Math.sqrt(sd / arr.size());
   }

   public double sumInArray(ArrayList<Double> arr) {
      double sum = 0;
      for (double num : arr) {
         sum += num;
      }
      return sum;
   }
}