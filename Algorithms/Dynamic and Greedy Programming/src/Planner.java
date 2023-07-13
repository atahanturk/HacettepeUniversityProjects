import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class Planner {

    public final Task[] taskArray;
    public final Integer[] compatibility;
    public final Double[] maxWeight;
    public final ArrayList<Task> planDynamic;
    public final ArrayList<Task> planGreedy;

    public Planner(Task[] taskArray) {

        // Should be instantiated with an Task array
        // All the properties of this class should be initialized here

        this.taskArray = taskArray;
        this.compatibility = new Integer[taskArray.length];
        maxWeight = new Double[taskArray.length];
        this.planDynamic = new ArrayList<>();
        this.planGreedy = new ArrayList<>();


    }


    /**
     * @param index of the {@link Task}
     * @return Returns the index of the last compatible {@link Task},
     * returns -1 if there are no compatible {@link Task}s.
     */
    public int binarySearch(int index) {
        // YOUR CODE HERE
        int low = 0;
        int high = index ;

        while (high >= low){
            int mid = (low + high) / 2;
            LocalTime mid_finish = LocalTime.parse(taskArray[mid].getFinishTime());
            LocalTime index_start = LocalTime.parse(taskArray[index].getStartTime());

            if (mid_finish.isBefore(index_start) || mid_finish.equals(index_start)){
                if (mid == high || LocalTime.parse(taskArray[mid + 1].getFinishTime()).isAfter(index_start)) {
                    return mid;
                } else if(LocalTime.parse(taskArray[mid+1].getFinishTime()).equals(index_start) && LocalTime.parse(taskArray[mid+1].getFinishTime()).equals(index_start) != LocalTime.parse(taskArray[mid+2].getFinishTime()).equals(index_start)) {

                    return mid+1;
                }
                low = mid + 1;
            } else{
                high = mid - 1;
            }
        }
        return -1;
    }


    /**
     * {@link #compatibility} must be filled after calling this method
     */
    public void calculateCompatibility() {
        // YOUR CODE HERE

        for (int i=0; i<taskArray.length; i++){
            this.compatibility[i] = binarySearch(i);
        }
    }


    /**
     * Uses {@link #taskArray} property
     * This function is for generating a plan using the dynamic programming approach.
     * @return Returns a list of planned tasks.
     */
    public ArrayList<Task> planDynamic() {
        // YOUR CODE HERE
        calculateCompatibility();
        System.out.println("Calculating the dynamic solution");
        System.out.println("--------------------------------");
        calculateMaxWeight(taskArray.length-1);
        solveDynamic(taskArray.length-1);
        Collections.reverse(planDynamic);
        System.out.println("");
        System.out.println("Dynamic Schedule");
        System.out.println("----------------");
        for(int j = 0; j < planDynamic.size(); j++){
            System.out.println("At " + planDynamic.get(j).getStartTime() + ", " + planDynamic.get(j).getName() + ".");
        }
        return planDynamic;
    }

    /**
     * {@link #planDynamic} must be filled after calling this method
     */
    public void solveDynamic(int i) {
            if (i > 0) {
                System.out.println("Called solveDynamic(" + i + ")");
                if (maxWeight[i] > maxWeight[i - 1]) {
                    planDynamic.add(taskArray[i]);
                    solveDynamic(compatibility[i]);
                } else {
                    solveDynamic(i - 1);
                }
            }
            if (i == 0){

                if(LocalTime.parse(taskArray[0].getFinishTime()).isBefore(LocalTime.parse(planDynamic.get(planDynamic.size()-1).getStartTime())) ||
                LocalTime.parse(taskArray[0].getFinishTime()).equals(LocalTime.parse(planDynamic.get(planDynamic.size()-1).getStartTime()))){
                    System.out.println("Called solveDynamic(0)");
                    planDynamic.add(taskArray[0]);
                }
            }

    }

    /**
     * {@link #maxWeight} must be filled after calling this method
     */
    /* This function calculates maximum weights and prints out whether it has been called before or not  */
    public Double calculateMaxWeight(int i) {
        // YOUR CODE HERE

        if (i<0){
            System.out.println("Called max(-1)");
            return 0.0;
        }

        if (maxWeight[i] == null){
            maxWeight[i] = 0.0;
        }
        System.out.println("Called max(" + i + ")");
        maxWeight[i] = Math.max(taskArray[i].getWeight() + calculateMaxWeight(compatibility[i]), calculateMaxWeight(i - 1));
        if (maxWeight[i] != null && maxWeight[i] != 0.0){
            return maxWeight[i];
        }

        if (compatibility[i] != -1){

            maxWeight[i] += taskArray[i].getWeight() + calculateMaxWeight(compatibility[i]);

        } else{
            calculateMaxWeight(i - 1);
        }
        return maxWeight[i];


    }

    /**
     * {@link #planGreedy} must be filled after calling this method
     * Uses {@link #taskArray} property
     *
     * @return Returns a list of scheduled assignments
     */

    /*
     * This function is for generating a plan using the greedy approach.
     * */
    public ArrayList<Task> planGreedy() {
        // YOUR CODE HERE
        planGreedy.add(taskArray[0]);
        System.out.println("Greedy Schedule");
        System.out.println("--------------");
        System.out.println("At " + taskArray[0].getStartTime() + ", " + taskArray[0].getName() + ".");
        for (int i=1; i < taskArray.length; i++){

            if (LocalTime.parse(taskArray[i].getStartTime()).isAfter(LocalTime.parse(planGreedy.get(planGreedy.size()-1).getFinishTime()))){
                planGreedy.add(taskArray[i]);
                System.out.println("At " + taskArray[i].getStartTime() + ", " + taskArray[i].getName() + ".");

            }else if (LocalTime.parse(taskArray[i].getStartTime()).equals(LocalTime.parse(planGreedy.get(planGreedy.size()-1).getFinishTime()))){
                planGreedy.add(taskArray[i]);
                System.out.println("At " + taskArray[i].getStartTime() + ", " + taskArray[i].getName() + ".");
            }

        }
        return planGreedy;
    }
}
