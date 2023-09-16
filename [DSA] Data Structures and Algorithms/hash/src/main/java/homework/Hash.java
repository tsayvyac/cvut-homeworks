package homework;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;

public class Hash {
    static class Member {
        String name;
        String[] hashTable;
        int[] count;
        int content;
        Member(String name) {
            this.name = name;
            content = 0;
        }
    }
    Member[] members = {new Member("Mirek"), new Member("Jarka"), new Member("Jindra"),
            new Member("Rychlonozka"), new Member("Cervenacek")};

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static final String ERROR = "Error: Chybny vstup!";
    static final int SIZE_M = 5;
    int memberId = -1;
    boolean isFirst = true;
    boolean aF = false;
    boolean pF = false;
    boolean dF = false;
    boolean isResize = false;

    void setSize(Member m, int size) {
        m.hashTable = new String[size];
        m.count = new int[size];
    }

    void initSize(String line) {
        int initialized = 0;
        if (line.charAt(0) == '#' && line.charAt(1) == 'i') {
            String[] splitLine = line.split("\\s+");
            for (int i = 1; i < splitLine.length; i++) {
                setSize(members[initialized], Integer.parseInt(splitLine[i]));
                initialized++;
            }
        }
        for (int i = initialized; i < SIZE_M; i++) {
            setSize(members[i], 11);
        }
        isFirst = false;
    }

    void parse() throws IOException {
        String line;
        while ((line = br.readLine()) != null) {
            if (isFirst) initSize(line);
            if (line.charAt(0) == '#' && line.charAt(1) != 'i') {
                switch (line.charAt(1)) {
                    case 'a' -> {
                        aF = true;
                        pF = false; dF = false;
                    }
                    case 'p' -> {
                        pF = true;
                        printMember(memberId);
                        aF = false; dF = false;
                    }
                    case 'd' -> {
                        dF = true;
                        aF = false; pF = false;
                    }
                    case '1' -> memberId = 0;
                    case '2' -> memberId = 1;
                    case '3' -> memberId = 2;
                    case '4' -> memberId = 3;
                    case '5' -> memberId = 4;
                    default -> {
                        memberId = -1;
                        System.err.println(ERROR);
                    }
                }
                continue;
            }
            if (aF) {
                for (Member m : members) {
                    append(m, line);
                }
            }
            if (dF) delete(memberId, line);
            if (pF) print(memberId, line);
        }
    }

    void delete(int memberId, String line) {
        Member m = members[memberId];
        int i = search(m, line);
        if (i != -1) {
            m.count[i]--;
            if (m.count[i] == 0) {
                m.hashTable[i] = "#";
                m.content--;
            }
            if ((double) m.content / m.hashTable.length <= 0.3) {
                resize(m, false);
            }
        }
    }

    int search(Member m, String line) {
        int size = m.hashTable.length;
        int j = 0;
        int i;
        do {
            i = (hashValue(line, size) + j) % size;
            if (Objects.equals(m.hashTable[i], line)) return i;
            j++;
        } while (m.hashTable[i] != null && j != size);
        return -1;
    }

    void print(int memberId, String line) {
        if (memberId > -1 && memberId < 5) {
            int i = search(members[memberId], line);
            int count = i == -1 ? 0 : members[memberId].count[i];
            System.out.println("\t" + line + " " + i + " " + count);
        }
    }

    int append(Member m, String line) {
        int size = m.hashTable.length;
        int j = 0;
        int i;
        int id = search(m, line);
        if (id != -1) {
            m.count[id]++;
            return -1;
        }
        do {
            i = (hashValue(line, size) + j) % size;
            if (m.hashTable[i] == null || Objects.equals(m.hashTable[i], "#")) {
                m.hashTable[i] = line;
                m.count[i]++;
                if (!isResize) {
                    m.content++;
                    if ((double) m.content / size >= 0.7) resize(m, true);
                }
                break;
            } else j++;
        } while (j != size);
        return i;
    }

    int hashValue(String line, int size) {
        int value = 0;
        int pPow = 1;
        for (int i = 0; i < line.length(); i++) {
            int charCode = line.charAt(i) == ' ' ? 31 : line.charAt(i) - 96;
            value = (value + charCode * pPow) % size;
            pPow = (pPow * 32) % size;
        }
        return value;
    }

    int newLength(int size, boolean isIncrease) {
        int length;
        if (isIncrease) {
            length = size * 2;
        } else {
            length = size % 2 == 0 ? size / 2 : size;
        }
        return length;
    }

    void resize(Member m, boolean isIncrease) {
        isResize = true;
        int newSize = newLength(m.hashTable.length, isIncrease);
        if (newSize != m.hashTable.length) {
            String[] temp = m.hashTable;
            m.hashTable = new String[newSize];
            int[] tempCount = m.count;
            m.count = new int[newSize];
            for (int j = 0; j < temp.length; j++) {
                if (temp[j] != null && !Objects.equals(temp[j], "#")) {
                    int i = append(m, temp[j]);
                    m.count[i] = tempCount[j];
                }
            }
        }
        isResize = false;
    }

    void printMember(int memberId) {
        if (!(memberId > -1 && memberId < 5)) {
            System.err.println(ERROR);
            return;
        }
        Member m = members[memberId];
        System.out.println(m.name);
        System.out.println("\t" + m.hashTable.length + " " + m.content);
    }

    public static void main(String[] args) throws IOException {
        Hash hash = new Hash();
        hash.parse();
    }
}