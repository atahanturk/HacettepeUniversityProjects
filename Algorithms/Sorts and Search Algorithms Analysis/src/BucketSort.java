import java.util.*;

public class BucketSort {
    public static void bucketSort(int[] arr) {
        int n = arr.length;
        int numOfBuckets = (int) Math.ceil(Math.sqrt(n));
        int max = Arrays.stream(arr).max().getAsInt();

        List<Integer>[] buckets = new List[numOfBuckets];
        for (int i = 0; i < numOfBuckets; i++) {
            buckets[i] = new ArrayList<Integer>();
        }
        for (int k : arr) {
            int bucketIndex = (int) ((k * 1.0 / max) * (numOfBuckets - 1));
            buckets[bucketIndex].add(k);
        }
        for (int i = 0; i < numOfBuckets; i++) {
            Collections.sort(buckets[i]);
        }
        int index = 0;
        for (int i = 0; i < numOfBuckets; i++) {
            for (int j = 0; j < buckets[i].size(); j++) {
                arr[index++] = buckets[i].get(j);
            }
        }
    }
}
