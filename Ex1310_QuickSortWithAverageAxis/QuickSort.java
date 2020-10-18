public class QuickSort {
    public static void main(String[] args) {
        int[] array = { 32,59,21,12,45,89
                ,63,34,26,7,6,18,24,45 };

        System.out.println("Before sorting:");
        for (int i: array) {
            System.out.print(i + " ");
        }
        System.out.println();

        quickSort(array);

        System.out.println("After sorting:");
        for (int i: array) {
            System.out.print(i + " ");
        }
        System.out.println();
    }

    public static int average(int[] array, int low, int high) {
        int avg = 0;
        for (int i = low; i <= high; i++) {
            avg += array[i];
        }
        avg /= high - low + 1;

        return avg;
    }
    public static int Partition(int[] array, int low, int high) {
        int avg = average(array, low, high);

        while (array[high] >= avg) {
            high--;
        }

        if (low == high) {
            return low;
        }

        array[0] = array[high];
        while (low < high) {
            while (low < high && array[low] <= avg) {
                low++;
            }

            if (low == high) {
                break;
            }

            array[high--] = array[low];

            while (low < high && array[high] >= avg) {
                high--;
            }

            if (low == high) {
                break;
            }

            array[low] = array[high];
            low++;
        }

        array[low] = array[0];
        return low;
    }

    public static void quickSortPass(int[] array, int s, int t) {
        if (s < t - 1) {
            int pivotLoc = Partition(array, s, t);
            quickSortPass(array, s, pivotLoc);
            quickSortPass(array, pivotLoc + 1, t);
        }
        else if (s == t - 1) {
            if (array[s] > array[t]) {
                int temp = array[s];
                array[t] = array[s];
                array[t] = temp;
            }
        }
    }

    public static void quickSort(int[] array) {
        if (array == null) {
            throw new NullPointerException();
        }
        int s = 0;
        int t = array.length - 1;
        
        int[] arrayCopy = new int[t - s + 2];
        System.arraycopy(array, s, arrayCopy, 1, t - s + 1);

        quickSortPass(arrayCopy, s + 1, t + 1);
        System.arraycopy(arrayCopy, 1, array, s, t - s + 1);
    }
}
