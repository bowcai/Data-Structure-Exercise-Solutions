import java.util.Comparator;

public class MergeSortedLists {
    public static void main(String[] args) {
        Integer[] aInput = { 1,3,5,6,7,8,9,14,15,17,18,19,40 };
        Integer[] bInput = { 2,4,6,8,10,12,14,16,18,22,25,27,40 };

        SeqList<Integer> a = new SeqList<>(aInput);
        SeqList<Integer> b = new SeqList<>(bInput);

        SeqList<Integer> c = a.unionList(b);
        c.showList();
    }
}

class SeqList<E> {
    @SuppressWarnings("unchecked")
    public E[] elem = (E[])new Object[MAX_SIZE];
    private Comparator<E> comparator = null;

    public int last;
    public final static int MAX_SIZE = 100;

    public SeqList() {
        emptyList();
    }

    public SeqList(final E[] inArray) {
        buildList(inArray);
    }

    public SeqList(Comparator<E> comparator) {
        this();
        this.comparator = comparator;
    }

    public SeqList(final E[] inArray, Comparator<E> comparator) {
        this(inArray);
        this.comparator = comparator;
    }

    public void buildList(final E[] inArray) {
        int n = Math.min(inArray.length, MAX_SIZE);
        System.arraycopy(inArray, 0, elem, 0, n);
        last = n - 1;
    }

    public void emptyList() {
        last = -1;
    }

    public void showList() {
        for (int i = 0; i <= last; i++) {
            System.out.print(elem[i] + ", ");
        }
        System.out.println();
    }

    public void appendList(E x) {
        last++;
        elem[last] = x;
    }

    @SuppressWarnings("unchecked")
    private int compareElem(E x, E y) {
        if (comparator != null) {
            return comparator.compare(x, y);
        }
        else {
            return ((Comparable<? super E>) x).compareTo(y);
        }
    }

    public SeqList<E> unionList(SeqList<E> l2) {
        SeqList<E> rslt = new SeqList<>();

        int i = 0, j = 0;
        while (i <= last && j <= l2.last) {
            int compareResult = compareElem(elem[i], l2.elem[j]);
            if (compareResult < 0) {
                rslt.appendList(elem[i]);
                i++;
            }
            else if (compareResult > 0) {
                rslt.appendList(l2.elem[j]);
                j++;
            }
            else {
                rslt.appendList(elem[i]);
                i++;
                j++;
            }
        }

        if (i > last) {
            for (;j <= l2.last;j++) {
                rslt.appendList(l2.elem[j]);
            }
        }
        else {
            for (;i <= last;i++) {
                rslt.appendList(elem[i]);
            }
        }

        return rslt;
    }
}
