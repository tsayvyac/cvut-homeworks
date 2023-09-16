package cz.cvut.fel.pjv;

import java.util.ArrayList;

public class BruteForceAttacker extends Thief {

    @Override
    public void breakPassword(int sizeOfPassword) {
        char[] pass = new char[sizeOfPassword];
        if (sizeOfPassword == 0) {
            tryOpen(pass);
            return;
        }
        breaking(pass, 0, sizeOfPassword);
        }

    public void breaking(char[] temp, int index, int size) {
        for (int i = 0; i < getCharacters().length; i++) {
            temp[index] = getCharacters()[i];
            if (index < size - 1) {
                breaking(temp, index + 1, size);
            }
            if (tryOpen(temp)) {
                break;
            }
        }
    }
}