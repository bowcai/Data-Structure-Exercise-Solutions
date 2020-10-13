public class MagicSquare {
    int[][] matrix;

    // Use Siamese method to generate odd-order magic square
    public MagicSquare(int m) {
        if (m % 2 == 0) {
            throw new IllegalArgumentException(
                "The function can only handle odd-order magic square.");
        }

        matrix = new int[m][m];

        int i = 0, j = (m - 1) / 2;
        int i_next, j_next;

        for (int k = 1; k <= m*m; k++) {
            matrix[i][j] = k;

            i_next = i - 1 >= 0 ? i - 1 : m - 1;
            j_next = j + 1 < m ? j + 1 : 0;

            if (matrix[i_next][j_next] == 0) {
                i = i_next;
                j = j_next;
            }
            else {
                i = i + 1 < m ? i + 1 : 0;
            }
        }
    }

    public void showMatrix() {
        for(int[] mati: matrix) {
            for(int matij: mati) {
                System.out.print(matij + "\t");
            }
            System.out.println();
        }
    }
}

class TestMagicSquare {
    public static void main(String[] args) {
        int m = 15;
        new MagicSquare(m).showMatrix();
    }
}
