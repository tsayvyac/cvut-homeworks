package cz.cvut.fel.pjv;

import java.util.Locale;
import java.util.Scanner;

public class Lab01 {

   public void homework(String[] args) {
      Scanner scan = new Scanner(System.in);
      scan.useLocale(Locale.US);
      String oper;
      int flDot;
      double first, second, result;
      System.out.println("Vyber operaci (1-soucet, 2-rozdil, 3-soucin, 4-podil):");
      oper = scan.next();
      if (oper.equals("1")) {
         System.out.println("Zadej scitanec: ");
         first = scan.nextDouble();
         System.out.println("Zadej scitanec: ");
         second = scan.nextDouble();
         System.out.println("Zadej pocet desetinnych mist: ");
         flDot = scan.nextInt();
         if (flDot < 0) {
            System.out.println("Chyba - musi byt zadane kladne cislo!");
            return;
         }
         result = first + second;
         System.out.println(String.format(Locale.US, "%."+flDot+"f", first) + " + " + String.format(Locale.US,"%."+flDot+"f", second) + " = " + String.format(Locale.US, "%."+flDot+"f", result));
      } else if (oper.equals("2")) {
         System.out.println("Zadej mensenec: ");
         first = scan.nextDouble();
         System.out.println("Zadej mensitel: ");
         second = scan.nextDouble();
         System.out.println("Zadej pocet desetinnych mist: ");
         flDot = scan.nextInt();
         if (flDot < 0) {
            System.out.println("Chyba - musi byt zadane kladne cislo!");
            return;
         }
         result = first - second;
         System.out.println(String.format(Locale.US, "%."+flDot+"f", first) + " - " + String.format(Locale.US, "%."+flDot+"f", second) + " = " + String.format(Locale.US, "%."+flDot+"f", result));
      } else if (oper.equals("3")) {
         System.out.println("Zadej cinitel: ");
         first = scan.nextDouble();
         System.out.println("Zadej cinitel: ");
         second = scan.nextDouble();
         System.out.println("Zadej pocet desetinnych mist: ");
         flDot = scan.nextInt();
         if (flDot < 0) {
            System.out.println("Chyba - musi byt zadane kladne cislo!");
            return;
         }
         result = first * second;
         System.out.println(String.format(Locale.US, "%."+flDot+"f", first) + " * " + String.format(Locale.US, "%."+flDot+"f", second) + " = " + String.format(Locale.US, "%."+flDot+"f", result));
      } else if (oper.equals("4")) {
         System.out.println("Zadej delenec: ");
         first = scan.nextDouble();
         System.out.println("Zadej delitel: ");
         second = scan.nextDouble();
         if (second == 0) {
            System.out.println("Pokus o deleni nulou!");
            return;
         }
         System.out.println("Zadej pocet desetinnych mist: ");
         flDot = scan.nextInt();
         if (flDot < 0) {
            System.out.println("Chyba - musi byt zadane kladne cislo!");
            return;
         }
         result = first / second;
         System.out.println(String.format(Locale.US, "%."+flDot+"f", first) + " / " + String.format(Locale.US, "%."+flDot+"f", second) + " = " + String.format(Locale.US, "%."+flDot+"f", result));
      } else {
         System.out.println("Chybna volba!");
      }
   }
}