public class BinarySearch {

    public static int binarySearch(int[] arr, int x) {
        int low = 0;
        int high = arr.length - 1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (arr[mid] < x) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        if (arr[low] == x) {
            return low;
        } else if (arr[high] == x) {
            return high;
        }
        return -1;
    }
}
