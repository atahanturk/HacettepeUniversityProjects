import java.io.*;
import java.util.Arrays;
import java.util.Random;




public class Main {

    public static void main(String[] args) throws IOException {
        if(args.length != 1){
            System.out.println("You should enter 1 argument!");
        }
        String fileName = args[0];
        int[] inputLength = {500, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 250000};

        double[][] yAxisRandomSort = new double[3][10];
        yAxisRandomSort[0] = new double[] {0,0,2,7,30,108,398,1567,6279,23972}; // Selection Sort[0]
        yAxisRandomSort[1] = new double[] {0,0,0,0,0,1,3,7,19,33}; //Quick Sort[1]
        yAxisRandomSort[2] = new double[] {0,0,1,1,4,5,6,11,21,48}; //Bucket Sort[1]
        double[][] yAxisSortedSort = new double[3][10];
        yAxisSortedSort[0] = new double[] {0,0,1,3,15,39,137,529,2101,8448};
        yAxisSortedSort[1] = new double[] {0,0,2,9,31,98,364,1491,5969,20286};
        yAxisSortedSort[2] = new double[] {0,0,0,0,0,0,1,1,2,5};
        double[][] yAxisReversedSort = new double[3][10];
        yAxisReversedSort[0] = new double[] {0,1,4,18,77,315,1236,4879,19692,75170};
        yAxisReversedSort[1] = new double[] {1,0,1,5,24,105,426,1720,7122,26533};
        yAxisReversedSort[2] = new double[] {0,0,0,0,0,0,1,2,3,10};
        double[][] yAxisSearch = new double [3][10];
        yAxisSearch[0] = new double[]{1754,589,722,865,1649,3249,5680,11498,21914,36133}; //Linear Search on Random Data
        yAxisSearch[1] = new double[]{3059,1221,709,1116,1900,3687,6871,14263,26792,58837}; //Linear Search on Sorted Data
        yAxisSearch[2] = new double[]{1629,851,473,410,1020,1220,1629,1969,2215,2574}; //Binary Search on Sorted Data

        ShowChart.showChart("Sorting with Random Data", yAxisRandomSort, "Time in milliseconds",
                "sorting");
        ShowChart.showChart("Sorting with Sorted Data", yAxisSortedSort, "Time in milliseconds",
                "sorting");
        ShowChart.showChart("Sorting with Reversed Data", yAxisReversedSort, "Time in milliseconds",
                "sorting");
        ShowChart.showChart("Searching with Data", yAxisSearch, "Time in nanoseconds",
                "searching");



        for(int rows : inputLength){
            int totalTime = 0;
            for(int i=0; i<10; i++){
                int[] flowDuration = FilePrepative.excelToArray(fileName,rows);
                //BucketSort.bucketSort(flowDuration); //For sorted array
                //ArrayReverser.reverseArray(flowDuration); // For reversed array
                long startTime = System.currentTimeMillis();
                SelectionSort.selection(flowDuration);
                long endTime = System.currentTimeMillis();
                totalTime += endTime - startTime;
            }
            long averageTime = totalTime/10;
            System.out.println(rows + " data average selection sort time is: " + averageTime);

        }

        for(int rows : inputLength){
            int totalTime = 0;

            for(int i=0; i<10; i++){
                int[] flowDuration = FilePrepative.excelToArray(fileName,rows);
                //BucketSort.bucketSort(flowDuration); //For sorted array
                //ArrayReverser.reverseArray(flowDuration); //For reversed
                long startTime = System.currentTimeMillis();
                QuickSort.quickSort(flowDuration);
                long endTime = System.currentTimeMillis();
                totalTime += endTime - startTime;
            }
            long averageTime = totalTime/10;
            System.out.println(rows + " data average quick sort time is: " + averageTime);
        }

        for(int rows : inputLength){
            int totalTime = 0;

            for(int i=0; i<10; i++){
                int[] flowDuration = FilePrepative.excelToArray("TrafficFlowDataset.csv", rows);
                //BucketSort.bucketSort(flowDuration); //For sorted array
                //ArrayReverser.reverseArray(flowDuration); //For reversed array
                long startTime = System.currentTimeMillis();
                BucketSort.bucketSort(flowDuration);
                long endTime = System.currentTimeMillis();
                totalTime += endTime - startTime;
            }
            long averageTime = totalTime/10;
            System.out.println(rows + " data average bucket sort time is: " + averageTime);
        }

        for(int rows: inputLength){
            int totalTime = 0;
            for(int i=0; i<1000; i++) {
                int[] flowDuration = FilePrepative.excelToArray(fileName,rows);
                int searchElement = RandomPicker.randomPicker(flowDuration);
                BucketSort.bucketSort(flowDuration); //For sorted array
                long startTime = System.nanoTime();
                LinearSearch.linearSearch(flowDuration, searchElement);
                long endTime = System.nanoTime();
                totalTime += endTime - startTime;
            }
            long averageTime = totalTime/1000;
            System.out.println(rows + " data average linear search time is: " + averageTime);

        }

        for(int rows : inputLength){
            int totalTime = 0;
            for(int i=0; i<1000; i++){
                int[] flowDuration = FilePrepative.excelToArray(fileName,rows);
                int searchElement = RandomPicker.randomPicker(flowDuration);
                BucketSort.bucketSort(flowDuration); //For sorted array
                long startTime = System.nanoTime();
                BinarySearch.binarySearch(flowDuration, searchElement);
                long endTime = System.nanoTime();
                totalTime += endTime - startTime;

            }
            long averageTime = totalTime/1000;
            System.out.println(rows + " data average binary search time is: " + averageTime);

        }
    }


}
