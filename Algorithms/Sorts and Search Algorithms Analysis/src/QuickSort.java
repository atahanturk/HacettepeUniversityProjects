public class QuickSort {

    public static void quickSort(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return;
        }
        int[] stack = new int[arr.length];
        int top = -1;
        stack[++top] = 0;
        stack[++top] = arr.length - 1;
        while (top >= 0) {
            int end = stack[top--];
            int start = stack[top--];
            int pivot = partition(arr, start, end);
            if (pivot - 1 > start) {
                stack[++top] = start;
                stack[++top] = pivot - 1;
            }
            if (pivot + 1 < end) {
                stack[++top] = pivot + 1;
                stack[++top] = end;
            }
        }
    }

    public static int partition(int[] arr, int start, int end) {
        int pivot = arr[end];
        int i = start - 1;
        for (int j = start; j < end; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, end);
        return i + 1;
    }

    public static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
