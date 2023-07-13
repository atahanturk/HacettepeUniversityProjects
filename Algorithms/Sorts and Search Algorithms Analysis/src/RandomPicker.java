import java.util.Random;

public class RandomPicker {

    public static int randomPicker(int[] arr){
        Random rand = new Random();
        int randomIndex = rand.nextInt(arr.length);
        return arr[randomIndex];
    }
}
